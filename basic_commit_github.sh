#!/bin/bash

# Basic commit to an already published repo on https://github.com


function help() {
	echo -e "Description: basic commit to an already published repo on https://github.com\nUsage:\n   -m -> commit message. required, requires an argument\nInfo: author -> ElPettego https://github.com/ElPettego | year -> 2023 | license -> MIT"
}

message=""

while getopts 'm:' flag; do
	case "${flag}" in
		m) message="$OPTARG" ;;
		*) help
		   exit 1;;
	esac
done


folder=$(basename $(pwd))

git add . > /dev/null 2>&1

git commit -m "$message" > /dev/null 2>&1

git push -u origin master << EOF > /dev/null 2>&1
$GITHUB_USER
$GITHUB_TOKEN
EOF

echo https://github.com/$GITHUB_USER/$folder
