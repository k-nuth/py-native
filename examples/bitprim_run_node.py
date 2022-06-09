# Copyright (c) 2016-2022 Knuth Project developers.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

import bitprim
import bitprim_native
import os
import signal
import sys
import time

# import numpy as np

# # ------------------------------------------------------
# # mnemonics_to_seed example
# # ------------------------------------------------------
# # https://github.com/libbitcoin/libbitcoin-explorer/wiki/bx-mnemonic-to-seed

# mnemonics = ['rival', 'hurdle', 'address', 'inspire', 'tenant', 'almost', 'turkey', 'safe', 'asset', 'step', 'lab', 'boy']
# w = bitprim.Wallet()
# seed = w.mnemonics_to_seed(mnemonics)
# print(seed)


# ------------------------------------------------------
#
# ------------------------------------------------------
def signal_handler(signal, frame):
    # signal.signal(signal.SIGINT, signal_handler)
    # signal.signal(signal.SIGTERM, signal_handler)
    print('You pressed Ctrl-C')
    sys.exit(0)

def history_fetch_handler(e, l):
    count = l.count()
    print('history_fetch_handler count: {0:d}'.format(count))

    for n in range(count):
        h = l.nth(n)
        # print(h)
        print(h.point_kind)
        print(h.height)
        print(h.value_or_spend)

        # print(h.point)
        print(h.point.hash)
        print(h.point.is_valid)
        print(h.point.index)
        print(h.point.get_checksum)

def block_header_handler(e, header):

    hash = header.previous_block_hash
    hash_hex = ''.join('{:02x}'.format(x) for x in hash[::-1])
    # print(hash)
    print(hash_hex)

def last_height_fetch_handler(e, h):
    if (e == 0):
        print('Last Height is: {0:d}'.format(h))

    hash_str = "00000000839a8e6886ab5951d76f411475428afc90947ee320161bbf18eb6048"
    hash = bytearray.fromhex(hash_str)
    hash = hash[::-1]
    t = buffer(hash)

    if h >= 1:
        execut.chain.fetch_block_header_by_height(1, block_header_handler)


    # if h >= 262421:
    # 	e.fetch_history('1MLVpZC2CTFHheox8SCEnAbW5NBdewRTdR', 0, 0, history_fetch_handler) # Juan







# # ------------------------------------------------------
# # Main Real
# # ------------------------------------------------------
signal.signal(signal.SIGINT, signal_handler)
signal.signal(signal.SIGTERM, signal_handler)

with bitprim.Executor("/home/fernando/execution_tests/btc_mainnet.cfg", sys.stdout, sys.stderr) as execut:
# with bitprim.Executor("/home/fernando/execution_tests/btc_mainnet.cfg") as execut:

    res = execut.init_chain()
    print(res)

    # ------------

    res = execut.init_chain()
    print(res)

    res = execut.run_wait()
    print(res)

    while True:
        execut.chain.fetch_last_height(last_height_fetch_handler)
    #     # e.chain.fetch_history('1A1zP1eP5QGefi2DMPTfTL5SLmv7DivfNa', 0, 0, history_fetch_handler) # Satoshi
    #     # e.chain.fetch_history('1MLVpZC2CTFHheox8SCEnAbW5NBdewRTdR', 0, 0, history_fetch_handler) # Juan
        time.sleep(30)


