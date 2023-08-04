#!/usr/bin/env python3.8 

from web3 import Web3
from web3.middleware import geth_poa
from w3_utils import get_keys
import argparse


def main():
    chain = {
        'polygon': 'https://polygon-bor.publicnode.com'
    }

    parser = argparse.ArgumentParser(description='deploys smart contract to an EVM compatible chain')

    parser.add_argument('keys',     help='name of the key couple located in __scrt_dir__')
    parser.add_argument('chain',    help='chain to deploy smart contract')
    parser.add_argument('bytecode', help='path to bytecode of the contract')
    parser.add_argument('abi',      help='path to abi of the contract')

    args = parser.parse_args()

    PRIVATE, PUBLIC = get_keys(args.keys)
        
    try:
        provider = chain[args.chain]
    except KeyError:
        raise SystemExit('chain not available')

    W3 = Web3(Web3.HTTPProvider(provider))
    W3.middleware_onion.inject(geth_poa.geth_poa_middleware, layer=0)

    with open(args.bytecode, 'r') as f:
        BYTECODE = f.read()

    with open(args.abi, 'r') as f:
        ABI = f.read()

    contract = W3.eth.contract(abi=ABI, bytecode=BYTECODE)

    tx = contract.constructor().build_transaction({
        'from'     : PUBLIC,
        'gasPrice' : W3.eth.gas_price,
        'nonce'    : W3.eth.get_transaction_count(PUBLIC)
    })

    gas = W3.eth.estimate_gas(tx)

    tx['gas'] = gas

    sign    = W3.eth.account.sign_transaction(tx, private_key=PRIVATE)
    send    = W3.eth.send_raw_transaction(sign.rawTransaction)
    print('__tx_hash__', W3.to_hex(send))
    receipt = W3.eth.wait_for_transaction_receipt(send)

    print(receipt)

if __name__ == '__main__':
    main()
