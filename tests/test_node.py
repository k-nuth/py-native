# Copyright (c) 2016-2022 Knuth Project developers.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

import kth_native as nat
import time

node_launch_err = None
def node_launch_handler(err):
    global node_launch_err
    node_launch_err = err
    print("handler result: ")
    print(err)

last_height = None
def chain_fetch_last_height_handler(err, h):
    global last_height
    last_height = h

def test_retrieves_the_right_chain_height():
    # global last_height
    mainnet = 0
    justChain = 1

    setts = nat.config_settings_default(mainnet)
    setts.database.db_max_size = 2 * 1024 * 1024;     # 2MiB

    node_ = nat.node_construct(setts, True);

#     const res = await node_.launch(primitives.StartModules.justChain);
#     expect(res).toBe(0);
#     await fillBlocks(node_.chain);

    nat.node_init_run_and_wait_for_signal(node_, justChain, lambda err: node_launch_handler(err))

    # await sleep(1000);
    time.sleep(1)

    chain = nat.node_get_chain(node_)
    nat.chain_fetch_last_height(chain, lambda err, h: chain_fetch_last_height_handler(err, h))

    assert last_height == 0

    nat.node_signal_stop(node_)
    nat.node_destruct(node_)
