# Copyright (c) 2016-present Knuth Project developers.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

"""Minimal example: start a Knuth node, fetch the genesis block, print info.

Modern equivalent of the historic `bn.construct` / `bn.initchain` /
`bn.run_wait` / `bn.get_chain` flow. Those entry points were removed
years ago; the current C-API uses `node_construct` +
`node_init_run_and_wait_for_signal` + `node_chain`.
"""

from __future__ import annotations

import signal
import time
from types import FrameType

import kth_native as bn

# Networks: 0=mainnet, 1=testnet, 3=testnet4, 4=scalenet, 5=chipnet.
MAINNET = 0
# StartModules: 1=just chain (no p2p), 2=full node.
JUST_CHAIN = 1

# Set by the signal handler so the main loop can break out cleanly
# and let the `finally` block run cleanup. Calling sys.exit() from
# inside the handler would skip the cleanup entirely.
_stop_requested = False


def signal_handler(signum: int, frame: FrameType | None) -> None:
    global _stop_requested
    print("You pressed Ctrl-C")
    _stop_requested = True


def block_handler(err: int, blk: object, height: int) -> None:
    if err != 0:
        print(f"fetch error: {err}")
        return

    print(f"height: {height}")

    tx_count = bn.block_transaction_count(blk)
    print(f"tx_count: {tx_count}")

    tx_0 = bn.block_transaction_nth(blk, 0)
    locktime = bn.chain_transaction_locktime(tx_0)
    print(f"locktime: {locktime}")


def main() -> None:
    signal.signal(signal.SIGINT, signal_handler)
    signal.signal(signal.SIGTERM, signal_handler)

    # Build a default mainnet settings struct. To load settings from a
    # config file instead, use `config_settings_get_from_file(path)`.
    setts = bn.config_settings_default(MAINNET)

    node = bn.node_construct(setts, True)
    bn.node_init_run_and_wait_for_signal(
        node, JUST_CHAIN, lambda err: print(f"node start: {err}")
    )

    # Give the node a moment to settle.
    time.sleep(1)

    chain = bn.node_chain(node)
    bn.chain_fetch_block_by_height(chain, 0, block_handler)

    try:
        while not _stop_requested:
            time.sleep(1)
    finally:
        bn.node_signal_stop(node)
        bn.node_destruct(node)


if __name__ == "__main__":
    main()
