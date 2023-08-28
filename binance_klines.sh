#!/bin/bash

function help() {
    echo "interact with binance api"
}

interval=''
symbol=''

while getopts 'i:s:' flag; do
	case "${flag}" in
		i) interval="$OPTARG" ;;
        s) symbol="$OPTARG" ;;
		*) help
		   exit 1;;
	esac
done

curl -s https://api.binance.com/api/v3/klines?interval=$interval\&symbol=$symbol 