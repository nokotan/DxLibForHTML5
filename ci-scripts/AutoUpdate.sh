#!/bin/bash

LANG="ja_JP.SJIS"

DxLibVersion=$(./FetchDxLibVersion.js)
OriginalBranch=original
DevelopBranch=develop

#
# Support Functions
#

function git_init_user() {
    git config --global user.name "DxLib Update Bot"
    git config --global user.mail "kamenokonokotan@gmail.com"
}

function download_and_unzip_dxlib() {
    local DxLibMakeFileVersion=$(echo ${DxLibVersion} | sed "s/\./_/")
    local DxLibMakeUrl="https://dxlib.xsrv.jp/DxLib/DxLibMake${DxLibMakeFileVersion}.zip"

    curl --output DxLibMake.zip ${DxLibMakeUrl}
    unzip DxLibMake.zip
}

function create_commit_of_common_part() {
    git switch ${OriginalBranch} --force
    git switch -c work_on_original

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
}

function apply_to_develop_branch() {
    git switch ${DevelopBranch} --force
    git cherry-pick $1
}

function update_original_branch() {
    git switch ${OriginalBranch} --force

    cp DxLibMake/* ..
    find .. -maxdepth 1 -type f | xargs -I{} git stage {}
    git commit -m "[Bot] Update to ${DxLibVersion} (Platform-Independent)"
}



#
# Functions in Main Logic
#

function do_init() {
    git_init_user
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
    echo ${Commit_CommonPart}

    apply_to_develop_branch ${Commit_CommonPart}

    update_original_branch
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
