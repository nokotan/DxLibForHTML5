#!/bin/bash

LANG="ja_JP.SJIS"

DxLibVersion=$(./FetchDxLibVersion.js)
OriginalBranch=original
DevelopBranch="update_to_${DxLibVersion}"

WorkingBranch=work_on_original

# 
# Colors
# 

NOCOLOR='\033[0m'
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'



#
# Utility Functions
#

function info() {
    printf "${GREEN}${1}${NOCOLOR}\n"
}

function warn() {
    printf "${YELLOW}${1}${NOCOLOR}\n"
}

# [no-return]
function err_exit() {
    printf "${RED}${1}${NOCOLOR}\n"
    exit 1
} 



#
# Support Functions
#

function git_init_user() {
    git config --global user.name "DxLib Update Bot"
    git config --global user.mail "kamenokonokotan@gmail.com"
}

function download_and_unzip_dxlib() {
    info "### download_and_unzip_dxlib"

    local DxLibMakeFileVersion=$(echo ${DxLibVersion} | sed "s/\./_/")
    local DxLibMakeUrl="https://dxlib.xsrv.jp/DxLib/DxLibMake${DxLibMakeFileVersion}.zip"

    curl --output DxLibMake.zip ${DxLibMakeUrl}

    if [ $? -ne 0 ]; then
        err_exit "Downloading ${DxLibMakeUrl} failed!"
    fi

    unzip DxLibMake.zip || true
    
    info "### download_and_unzip_dxlib done"
}


function create_patch_commit_of_common_part() {
    info "### create_patch_commit_of_common_part"

    git switch ${WorkingBranch} --force

    # Commit1: cherry-pick preparation
    sed -i .tmp "s/extern/extern DXLIBAPI/" ../DxLib.h
    rm ../DxLib.h.tmp

    git stage ../DxLib.h
    git commit -m "[Bot] Update DxLib.h before ${DxLibVersion}"

    # Commit2: cherry-picked commit
    cp DxLibMake/* ..
    sed -i .tmp "s/extern/extern DXLIBAPI/" ../DxLib.h
    rm ../DxLib.h.tmp

    find .. -maxdepth 1 -type f | xargs -I{} git stage {}
    git commit -m "[Bot] Create Patch of ${DxLibVersion} (Platform-Independent)"

    info "### create_patch_commit_of_common_part done"
}

function apply_to_develop_branch() {
    info "### apply_to_develop_branch"

    git switch ${DevelopBranch} --force
    git cherry-pick $1

    if [ $? -ne 0 ]; then
        err_exit "Git cherry-pick failed!"
    fi

    info "### apply_to_develop_branch done"
}

function update_original_branch_of_common_part() {
    info "### update_original_branch_of_common_part"

    git switch ${OriginalBranch} --force

    cp DxLibMake/* ..
    find .. -maxdepth 1 -type f | xargs -I{} git stage {}
    git commit -m "[Bot] Update to ${DxLibVersion} (Platform-Independent)"

    info "### update_original_branch_of_common_part done"
}


function create_patch_commit_of_android_part() {
    info "### create_patch_commit_of_android_part"

    git switch ${WorkingBranch} --force
    mkdir ../HTML5 || true

    # Commit1: cherry-pick preparation
    ./CopyFromAndroid.js

    if [ $? -ne 0 ]; then
        err_exit "CopyFromAndroid.js failed!"
    fi

    git stage ../HTML5/*
    git commit -m "[Bot] Update Android Part before ${DxLibVersion}"


    # Commit2: cherry-picked commit
    cp DxLibMake/Android/* ../Android
    ./CopyFromAndroid.js

    if [ $? -ne 0 ]; then
        err_exit "CopyFromAndroid.js failed!"
    fi


    find ../HTML5 -maxdepth 1 -type f | xargs -I{} git stage {}
    git commit -m "[Bot] Create Patch of ${DxLibVersion} (Android)"

    info "### create_patch_commit_of_android_part done"
}

function create_patch_commit_of_ios_part() {
    info "### create_patch_commit_of_ios_part"

    git switch ${WorkingBranch} --force

    # Commit1: cherry-pick preparation
    ./CopyFromiOS.js

    if [ $? -ne 0 ]; then
        err_exit "CopyFromiOS.js failed!"
    fi


    git stage ../HTML5/*
    git commit -m "[Bot] Update iOS Part before ${DxLibVersion}"

    # Commit2: cherry-picked commit
    cp DxLibMake/iOS/* ../iOS
    ./CopyFromiOS.js

    if [ $? -ne 0 ]; then
        err_exit "CopyFromiOS.js failed!"
    fi


    find ../HTML5 -maxdepth 1 -type f | xargs -I{} git stage {}
    git commit -m "[Bot] Create Patch of ${DxLibVersion} (iOS)"

    info "### create_patch_commit_of_ios_part done"
}


function update_original_branch_of_platform_dependent_part() {
    info "### update_original_branch_of_platform_dependent_part"

    git switch ${OriginalBranch} --force

    cp DxLibMake/Android/* ../Android
    find ../Android -maxdepth 1 -type f | xargs -I{} git stage {}
    git commit -m "[Bot] Update to ${DxLibVersion} (Android)"

    cp DxLibMake/iOS/* ../iOS
    find ../iOS -maxdepth 1 -type f | xargs -I{} git stage {}
    git commit -m "[Bot] Update to ${DxLibVersion} (iOS)"

    info "### update_original_branch_of_platform_dependent_part done"
}

function create_pull_request() {
    curl \
        -X POST \
        -H "Authorization: token ${GITHUB_TOKEN}" \
        -H "Content-Type: application/json" \
        -d "{
                \"title\":\"update to ${DxLibVersion}\",
                \"head\":\"${DevelopBranch}\",
                \"base\":\"develop\",
                \"body\":\"automated update to ${DxLibVersion}\"
            }" \
        https://api.github.com/repos/nokotan/DxLibForHTML5/pulls
}



#
# Functions in Main Logic
#

function do_init() {
    git_init_user

    chmod +x CopyFromAndroid.js
    chmod +x CopyFromiOS.js
    chmod +x FetchDxLibVersion.js
    chmod +x FetchLatestTag.js

    git fetch

    git switch ${OriginalBranch} --force
    git switch -c ${WorkingBranch}

    git switch develop --force
    git switch -c ${DevelopBranch}
}

function check_update_required() {
    local GitHubVersion=$(./FetchLatestTag.js)

    if [ $? -ne 0 ]; then
        err_exit "FetchLatestTag.js failed!"
    fi

    warn "DxLibVersion: ${DxLibVersion}, GitHubVersion: ${GitHubVersion}"

    if [ ${DxLibVersion} == ${GitHubVersion} ]; then
        warn "No need to update. Exit."
        return 1
    fi

    return 0
}

function do_update() {
    download_and_unzip_dxlib

    create_patch_commit_of_common_part
    local CommitID_CommonPart=$(git log --format="%H" -n 1)
    apply_to_develop_branch ${CommitID_CommonPart}
    update_original_branch_of_common_part

    create_patch_commit_of_android_part
    local CommitID_AndroidPart=$(git log --format="%H" -n 1)
    apply_to_develop_branch ${CommitID_AndroidPart}
    
    create_patch_commit_of_ios_part
    local CommitID_iOSPart=$(git log --format="%H" -n 1)
    apply_to_develop_branch ${CommitID_iOSPart}

    update_original_branch_of_platform_dependent_part
}

function post_update() {
    git push https://${GITHUB_TOKEN}@github.com/${TRAVIS_REPO_SLUG}.git ${OriginalBranch}
    git push -u https://${GITHUB_TOKEN}@github.com/${TRAVIS_REPO_SLUG}.git ${DevelopBranch}

    create_pull_request
}



#
# Main Logic
#

do_init

if check_update_required; then
    do_update
    post_update
fi
