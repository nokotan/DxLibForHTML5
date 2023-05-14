#!/bin/bash

source ./Util.sh

function create_patch_commit_of_ios_part() {
    info "### create_patch_commit_of_ios_part"

    git switch ${WorkingBranch} --force

    # Commit1: cherry-pick preparation
    node ./CopyFromiOS.js

    if [ $? -ne 0 ]; then
        err_exit "CopyFromiOS.js failed!"
    fi


    git stage ../HTML5/*
    git commit -m "[Bot] Update iOS Part before ${DxLibVersion}"

    # Commit2: cherry-picked commit
    cp DxLibMake/iOS/* ../iOS
    node ./CopyFromiOS.js

    if [ $? -ne 0 ]; then
        err_exit "CopyFromiOS.js failed!"
    fi


    find ../HTML5 -maxdepth 1 -type f | xargs -I{} git stage {}
    git commit -m "[Bot] Create Patch of ${DxLibVersion} (iOS)"

    info "### create_patch_commit_of_ios_part done"
}

function update_original_branch_of_ios_part() {
    info "### update_original_branch_of_ios_part"

    git switch ${OriginalBranch} --force

    cp DxLibMake/iOS/* ../iOS
    find ../iOS -maxdepth 1 -type f | xargs -I{} git stage {}
    git commit -m "[Bot] Update to ${DxLibVersion} (iOS)"

    info "### update_original_branch_of_ios_part done"
}

create_patch_commit_of_ios_part
CommitID_iOSPart=$(git log --format="%H" -n 1)
apply_to_develop_branch ${CommitID_iOSPart}
update_original_branch_of_ios_part
