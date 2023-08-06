#!/bin/bash

# Creates a git repository in the current directory and publishes it to https://github.com

function help() {
	printf "Description: creates a git repository in the current directory and publishes it to https://github.com\nUsage:\n   -d -> description for the repository. optional, requires an argument\n   -p -> sets the repo to public (default is private). optional, no argument\n   -g -> adds .gitignore (default is not added). optional, no argumentInfo: author -> ElPettego https://github.com/ElPettego | year -> 2023 | license -> MIT\n"
}

description=''
public=0
gitignore=0

while getopts 'd:pg' flag; do
	case "${flag}" in
		d) description="${OPTARG}" ;;
		g) gitignore=1 ;;
		p) public=1 ;; 
		*) help
		   exit 1;;
	esac
done

folder=$(basename $(pwd))

echo $folder

curl -u $GITHUB_USER:$GITHUB_TOKEN https://api.github.com/user/repos -d '{"name":"'"$folder"'", "private": true, "description": ""}' > /dev/null 2>&1

git init 

echo "# $folder" > README.md

cp ~/.templates/.gitignore .gitignore

git add .

git commit -m "__init_repo__"

git remote add origin https://github.com/$GITHUB_USER/$folder.git

git push -u origin master << EOF > /dev/null 2>&1
$GITHUB_USER
$GITHUB_TOKEN
EOF
