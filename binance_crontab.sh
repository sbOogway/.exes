#!/bin/bash

dir="/tmp/crypto_prices"
mylist=($(awk '{print}' ~/.templates/.market_cryptos.txt))

mkdir $dir

while true
do 
    for value in ${mylist[@]}; do
        binance_klines.sh -i 1d -s $value | jq -r '.[-1][4], .[-1][1]' | sed '1s/$/,/' | tr -d '\n' > $dir/$value.txt 
    done;

    sleep 30

    echo "loop done" 

done

