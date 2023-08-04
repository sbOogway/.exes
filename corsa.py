#!/usr/bin/env python3.8

from web3 import Web3
from web3.middleware import geth_poa
import argparse
from w3_utils import get_keys, get_contract_info, get_contract_abi, handle_tx

def main():
    actions  = ['front', 'back', 'withdraw']
    networks = {
        'polygon' : 'https://polygon-bor.publicnode.com',
        'binance' : ''
    }

    parser = argparse.ArgumentParser(description='interact with correreDavanti smart contract')

    parser.add_argument('action',     help=f'action to exec on smart contract: {actions}', choices=actions)
    parser.add_argument('network',    help='network to exec the tx')
    parser.add_argument('keys',       help='keys couple to exec transaction')
    parser.add_argument('--nonce',    '-n',  type=int,   default=-1,     help='nonce for the tx')
    parser.add_argument('--address1', '-a1', type=str,   default='0x',   help='address of the token1 to buy/sell')
    parser.add_argument('--address2', '-a2', type=str,   default='0x',   help='address of the token2 to buy/sell')
    parser.add_argument('--amount',   '-q',  type=float, default=0.0001, help='amount of the token to buy in eth')
    parser.add_argument('--gasprice', '-g',  type=int,   default=-1,     help='gas price for the tx')
    
    args = parser.parse_args()
    
    if args.action != 'withdraw':
        assert args.address1 != '0x' and args.address2 != '0x', 'need to specify address 1 and 2'

    PRIVATE, PUBLIC = get_keys(args.keys)
    CORRERE_ADDRESS, CORRERE_OWNER = get_contract_info('correreDavanti', args.network)

    assert PUBLIC == CORRERE_OWNER, 'keys do not match with contract owner'

    abi = get_contract_abi('correreDavanti')

    try:
        provider = networks[args.network]
    except KeyError:
        raise SystemExit('network not available')

    W3 = Web3(Web3.HTTPProvider(provider))
    W3.middleware_onion.inject(geth_poa.geth_poa_middleware, layer=0)

    if args.gasprice == -1:
        args.gasprice = W3.eth.gas_price 
    
    if args.nonce    == -1:
        args.nonce    = W3.eth.get_transaction_count(PUBLIC) 
    
    contract = W3.eth.contract(W3.to_checksum_address(CORRERE_ADDRESS), abi=abi)

    if args.action == 'withdraw':
        tx = contract.functions.withdraw().build_transaction({
            'from'     : PUBLIC,
            'gasPrice' : args.gasprice,
            'nonce'    : args.nonce,
        })
        handle_tx(W3, tx, PRIVATE)

    if args.action == 'front':
        tx = contract.functions.front(W3.to_wei(args.amount, 'ether'), W3.to_checksum_address(args.address1), W3.to_checksum_address(args.address2)).build_transaction({
            'from'     : PUBLIC,
            'gasPrice' : args.gasprice,
            'nonce'    : args.nonce,
        })
        handle_tx(W3, tx, PRIVATE)

    if args.action == 'back':
        tx = contract.functions.back(W3.to_checksum_address(args.address1), W3.to_checksum_address(args.address2)).build_transaction({
            'from'     : PUBLIC,
            'gasPrice' : args.gasprice,
            'nonce'    : args.nonce,
        })
        handle_tx(W3, tx, PRIVATE)   


if __name__ == '__main__':
    main()
