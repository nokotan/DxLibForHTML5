#!/bin/bash

export DxLibVersion=$(node ./FetchDxLibVersion.mjs)
export OriginalBranch=original
export DevelopBranch="update_to_${DxLibVersion}"

export WorkingBranch=work_on_original

source ./Util.sh

#
# Support Functions
#

function git_init_user() {
    git config user.name "DxLib Update Bot"
    git config user.email "kamenokonokotan@gmail.com"
}

function download_and_unzip_dxlib() {
    info "### download_and_unzip_dxlib"

    local DxLibMakeFileVersion=$(echo ${DxLibVersion} | sed "s/\./_/")
    local DxLibMakeUrl="https://dxlib.xsrv.jp/DxLib/DxLibMake${DxLibMakeFileVersion}.zip"

    curl --output DxLibMake.zip ${DxLibMakeUrl}

    if [ $? -ne 0 ]; then
        err_exit "Downloading ${DxLibMakeUrl} failed!"
    fi

    rm -r DxLibMake || true
    unzip -O sjis DxLibMake.zip
    
    info "### download_and_unzip_dxlib done"
}

#
# Functions in Main Logic
#

function do_init() {
    git_init_user

    git switch original
    git switch develop
    git branch -c ${OriginalBranch} ${WorkingBranch} 
    git branch -c develop ${DevelopBranch}
}

function check_update_required() {
    local GitHubVersion=$(bash ./FetchLatestTag.sh)

    if [ $? -ne 0 ]; then
        err_exit "FetchLatestTag.sh failed!"
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

    source ./UpdateFromCommon.sh
    source ./UpdateFromAndroid.sh
    source ./UpdateFromiOS.sh
}

function post_update() {
    git push origin ${OriginalBranch}
    git push -u origin ${DevelopBranch}
}



#
# Main Logic
#

if check_update_required; then
    do_init
    do_update
    post_update
fi
