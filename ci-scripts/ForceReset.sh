#!/bin/bash

git cherry-pick --quit
git switch original
git reset --hard c536b41b0c836a30160013ee27bc0ef39eb8a774
git switch develop
git reset --hard ef96d5d
git branch -D work_on_original
git branch | grep update | xargs -I{} git branch -D {}
