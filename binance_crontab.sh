#!/bin/bash

dir="/tmp/crypto_prices"
mylist=($(awk '{print}' ~/.templates/.market_cryptos.txt))

for value in ${mylist[@]}; do
    binance_klines.sh -i 5m -s $value | jq -r .[-1][4] > $dir/$value.txt
done; 
