 # 
 # Copyright (c) 2017 Bitprim developers (see AUTHORS)
 # 
 # This file is part of Bitprim.
 # 
 # This program is free software: you can redistribute it and/or modify
 # it under the terms of the GNU Affero General Public License as published by
 # the Free Software Foundation, either version 3 of the License, or
 # (at your option) any later version.
 # 
 # This program is distributed in the hope that it will be useful,
 # but WITHOUT ANY WARRANTY; without even the implied warranty of
 # MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 # GNU Affero General Public License for more details.
 # 
 # You should have received a copy of the GNU Affero General Public License
 # along with this program.  If not, see <http://www.gnu.org/licenses/>.
 # 
 
import os
import signal
import sys
import time
import bitprim_native as bn


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