#!/bin/bash

source ./Util.sh

function create_patch_commit_of_common_part() {
    info "### create_patch_commit_of_common_part"

    git switch ${WorkingBranch} --force

    # Original header file does not have DXLIBAPI macro,
    # but we need header file with DXLIBAPI macro.
    # Single commit with adding DXLIBAPI macro and original source difference
    # will be problematic, so we create separate commits.

    # Commit1: cherry-pick preparation
    # Adding DXLIBAPI
    sed -i.tmp -e "s/extern/extern DXLIBAPI/" ../src/DxLib.h
    rm ../src/DxLib.h.tmp

    git stage ../src/DxLib.h
    git commit -m "[Bot] Update DxLib.h before ${DxLibVersion}"

    # Commit2: cherry-picked commit
    # Original source difference
    cp DxLibMake/* ../src
    sed -i.tmp -e "s/extern/extern DXLIBAPI/" ../src/DxLib.h
    rm ../src/DxLib.h.tmp

    find ../src -maxdepth 1 -type f | xargs -I{} git stage {}
    git commit -m "[Bot] Create Patch of ${DxLibVersion} (Platform-Independent)"

    info "### create_patch_commit_of_common_part done"
}

function update_original_branch_of_common_part() {
    info "### update_original_branch_of_common_part"

    git switch ${OriginalBranch} --force

    cp DxLibMake/* ../src
    find ../src -maxdepth 1 -type f | xargs -I{} git stage {}
    git commit -m "[Bot] Update to ${DxLibVersion} (Platform-Independent)"

    info "### update_original_branch_of_common_part done"
}

create_patch_commit_of_common_part
CommitID_CommonPart=$(git log --format="%H" -n 1)
apply_to_develop_branch ${CommitID_CommonPart}
update_original_branch_of_common_part
