# Copyright (c) 2016-2022 Knuth Project developers.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

import os
import signal
import sys
import time
import kth_native as bn


def signal_handler(signal, frame):
    # signal.signal(signal.SIGINT, signal_handler)
    # signal.signal(signal.SIGTERM, signal_handler)
    print('You pressed Ctrl-C')
    # bn.destruct(executor)
    sys.exit(0)

# # ------------------------------------------------------
# # Main Real
# # ------------------------------------------------------
signal.signal(signal.SIGINT, signal_handler)
signal.signal(signal.SIGTERM, signal_handler)


executor = bn.construct("/home/fernando/execution_tests/btc_mainnet.cfg", sys.stdout, sys.stderr)

res = bn.initchain(executor)
print(res)

res = bn.run_wait(executor)
print(res)

chain = bn.get_chain(executor)


def block_handler(e, blk, height):
    print("height: ")
    print(height)

    tx_count = bn.block_transaction_count(blk)
    print("tx_count: ")
    print(tx_count)

    tx_0 = bn.block_transaction_nth(blk, 0)
    locktime = bn.transaction_locktime(tx_0)

    print("locktime: ")
    print(locktime)



bn.chain_fetch_block_by_height(chain, 0, block_handler)


while True:
    time.sleep(30)

bn.destruct(executor)