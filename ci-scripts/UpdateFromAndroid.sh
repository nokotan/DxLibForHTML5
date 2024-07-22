#!/bin/bash

source ./Util.sh

function create_patch_commit_of_android_part() {
    info "### create_patch_commit_of_android_part"

    git switch ${WorkingBranch} --force
    mkdir ../src/HTML5 || true

    # Commit1: cherry-pick preparation
    node ./CopyFromAndroid.js

    if [ $? -ne 0 ]; then
        err_exit "CopyFromAndroid.js failed!"
    fi

    git stage ../src/HTML5/*
    git commit -m "[Bot] Update Android Part before ${DxLibVersion}"


    # Commit2: cherry-picked commit
    cp DxLibMake/Android/* ../src/Android
    node ./CopyFromAndroid.js

    if [ $? -ne 0 ]; then
        err_exit "CopyFromAndroid.js failed!"
    fi


    find ../src/HTML5 -maxdepth 1 -type f | xargs -I{} git stage {}
    git commit -m "[Bot] Create Patch of ${DxLibVersion} (Android)"

    info "### create_patch_commit_of_android_part done"
}

function update_original_branch_of_android_part() {
    info "### update_original_branch_of_android_part"

    git switch ${OriginalBranch} --force

    cp DxLibMake/Android/* ../src/Android
    find ../src/Android -maxdepth 1 -type f | xargs -I{} git stage {}
    git commit -m "[Bot] Update to ${DxLibVersion} (Android)"

    info "### update_original_branch_of_android_part done"
}

create_patch_commit_of_android_part
CommitID_AndroidPart=$(git log --format="%H" -n 1)
apply_to_develop_branch ${CommitID_AndroidPart}
update_original_branch_of_android_part
