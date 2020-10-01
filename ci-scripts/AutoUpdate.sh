#!/bin/bash

LANG="ja_JP.SJIS"

DxLibVersion=$(./FetchDxLibVersion.js)
OriginalBranch=original
DevelopBranch=develop

WorkingBranch=work_on_original

#
# Support Functions
#

function git_init_user() {
    git config --global user.name "DxLib Update Bot"
    git config --global user.mail "kamenokonokotan@gmail.com"
}

function download_and_unzip_dxlib() {
    echo "### download_and_unzip_dxlib"

    local DxLibMakeFileVersion=$(echo ${DxLibVersion} | sed "s/\./_/")
    local DxLibMakeUrl="https://dxlib.xsrv.jp/DxLib/DxLibMake${DxLibMakeFileVersion}.zip"

    curl --output DxLibMake.zip ${DxLibMakeUrl}
    unzip DxLibMake.zip

    echo "### download_and_unzip_dxlib done"
}


function create_commit_of_common_part() {
    echo "### create_commit_of_common_part"

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

    echo "### create_commit_of_common_part done"
}

function apply_to_develop_branch() {
    git switch ${DevelopBranch} --force
    git cherry-pick $1
}

function update_original_branch_of_common_part() {
    echo "### update_original_branch_of_common_part"

    git switch ${OriginalBranch} --force

    cp DxLibMake/* ..
    find .. -maxdepth 1 -type f | xargs -I{} git stage {}
    git commit -m "[Bot] Update to ${DxLibVersion} (Platform-Independent)"

    echo "### update_original_branch_of_common_part done"
}


function create_commit_of_android_part() {
    echo "### create_commit_of_android_part"

    git switch ${WorkingBranch} --force
    mkdir ../HTML5 || true

    # Commit1: cherry-pick preparation
    ./CopyFromAndroid.js

    git stage ../HTML5/*
    git commit -m "[Bot] Update Android Part before ${DxLibVersion}"

    # Commit2: cherry-picked commit
    cp DxLibMake/Android/* ../Android
    ./CopyFromAndroid.js

    find ../HTML5 -maxdepth 1 -type f | xargs -I{} git stage {}
    git commit -m "[Bot] Create Patch of ${DxLibVersion} (Android)"

    echo "### create_commit_of_android_part done"
}

function create_commit_of_ios_part() {
    echo "### create_commit_of_ios_part"

    git switch ${WorkingBranch} --force

    # Commit1: cherry-pick preparation
    ./CopyFromiOS.js

    git stage ../HTML5/*
    git commit -m "[Bot] Update iOS Part before ${DxLibVersion}"

    # Commit2: cherry-picked commit
    cp DxLibMake/iOS/* ../iOS
    ./CopyFromiOS.js

    find ../HTML5 -maxdepth 1 -type f | xargs -I{} git stage {}
    git commit -m "[Bot] Create Patch of ${DxLibVersion} (iOS)"

    echo "### create_commit_of_ios_part done"
}


function update_original_branch_of_platform_dependent_part() {
    echo "### update_original_branch_of_platform_dependent_part"

    git switch ${OriginalBranch} --force

    cp DxLibMake/Android/* ../Android
    find ../Android -maxdepth 1 -type f | xargs -I{} git stage {}
    git commit -m "[Bot] Update to ${DxLibVersion} (Android)"

    cp DxLibMake/iOS/* ../iOS
    find ../iOS -maxdepth 1 -type f | xargs -I{} git stage {}
    git commit -m "[Bot] Update to ${DxLibVersion} (iOS)"

    echo "### update_original_branch_of_platform_dependent_part done"
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

    git switch ${OriginalBranch} --force
    git switch -c ${WorkingBranch}
}

function check_update_required() {
    local GitHubVersion=$(./FetchLatestTag.js)

    echo "DxLibVersion: ${DxLibVersion}, GitHubVersion: ${GitHubVersion}"

    if [ ${DxLibVersion} == ${GitHubVersion} ]; then
        echo "No need to update. Exit."
        return 1
    fi

    return 0
}

function do_update() {
    download_and_unzip_dxlib

    create_commit_of_common_part
    local Commit_CommonPart=$(git log --format="%H" -n 1)
    apply_to_develop_branch ${Commit_CommonPart}
    update_original_branch_of_common_part

    create_commit_of_android_part
    local Commit_AndroidPart=$(git log --format="%H" -n 1)
    apply_to_develop_branch ${Commit_AndroidPart}
    
    create_commit_of_ios_part
    local Commit_iOSPart=$(git log --format="%H" -n 1)
    apply_to_develop_branch ${Commit_iOSPart}

    update_original_branch_of_platform_dependent_part
}

function post_update() {
    git push https://${GITHUB_TOKEN}@github.com/${TRAVIS_REPO_SLUG}.git original
    git push https://${GITHUB_TOKEN}@github.com/${TRAVIS_REPO_SLUG}.git develop
}



#
# Main Logic
#

do_init

if check_update_required; then
    do_update
    post_update
fi
