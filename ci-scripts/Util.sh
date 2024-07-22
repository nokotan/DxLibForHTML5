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

function apply_to_develop_branch() {
    info "### apply_to_develop_branch"

    git switch ${DevelopBranch} --force
    git cherry-pick --allow-empty $1

    if [ $? -ne 0 ]; then
        warn "conflict detected. need to merge manually."
        git add ../src
        git cherry-pick --continue

        if [ $? -ne 0 ]; then
            err_exit "Git cherry-pick failed!"
        fi
    fi

    info "### apply_to_develop_branch done"
}
