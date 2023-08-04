#!/bin/bash

# Creates a git repository and publishes it to https://github.com

if [ $# -lt 1 ]; then
	echo "Usage: $0 <folder_path>"
	exit 1
fi

folder=$1

if [ "$folder" == "." ]; then 
	folder=$(basename $(pwd))
fi

echo $folder

curl -u $GITHUB_USER:$GITHUB_TOKEN https://api.github.com/user/repos -d '{"name":"$folder"}'
