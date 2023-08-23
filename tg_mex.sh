#!/bin/bash

# Shell script to send a telegram message using curl.

function help() {
	printf "Description: sends a message through telegram api.\nUsage:\n   -m -> message. required, requires an argument\n   -c -> chat id. required, requires an argument\n   -b -> bot token. required, requires an argument\n   -v -> verbosity. optional, default 1 (outputs response from telegram), requires an argument. verbosity 0 -> no output. verbosity 1 -> yes output\nInfo: author -> ElPettego https://github.com/ElPettego | year -> 2023 | license -> MIT\n"
}

message=""
bot=""
chat=""
verbosity=1

while getopts 'm:c:b:v:' flag; do
	case "${flag}" in
		m) message="$OPTARG" ;;
        b) bot="$OPTARG" ;;
        c) chat="$OPTARG" ;;
        v) verbosity="$OPTARG";;

		*) help
		   exit 1;;
	esac
done

if [ $verbosity -eq 0 ]; then
    curl https://api.telegram.org/bot$bot/sendMessage?chat_id=$chat\&text=$message > /dev/null 2>&1
fi

if [ $verbosity -eq 1 ]; then
    curl https://api.telegram.org/bot$bot/sendMessage?chat_id=$chat\&text=$message
    wait
    echo
fi