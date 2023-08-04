#!/bin/bash

# Creates a git repository in the current directory and publishes it to https://github.com

folder=$(basename $(pwd))

echo $folder

curl -u $GITHUB_USER:$GITHUB_TOKEN https://api.github.com/user/repos -d "{\"name\":\"$folder\"}"

git init 

echo "# $folder" > README.md

git add .

git commit -m "__init_repo__"

git remote add origin https://github.com/$GITHUB_USER/$folder.git

git push -u origin master
