# Copyright (c) 2016-2022 Knuth Project developers.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http:#www.opensource.org/licenses/mit-license.php.

import kth_native

import asyncio
import signal
import sys
import time


def hash_to_str(hash):
    return bytes(reversed(hash)).hex()

def print_authority(authority):
    print(f'ip: {authority.ip}, port: {authority.port}')

def print_endpoint(endpoint):
    print(f'scheme: {endpoint.scheme}, host: {endpoint.host}, port: {endpoint.port}')

def print_node_settings(ns):
    print(ns.sync_peers)
    print(ns.sync_timeout_seconds)
    print(ns.block_latency_seconds)
    print(ns.refresh_transactions)
    print(ns.compact_blocks_high_bandwidth)
    print(ns.ds_proofs_enabled)

def print_database_settings(ds):
    print(ds.directory)
    print(ds.flush_writes)
    print(ds.file_growth_rate)
    print(ds.index_start_height)

    print(ds.reorg_pool_limit)
    print(ds.db_max_size)

    print(ds.safe_mode)
    print(ds.cache_capacity)

def print_blockchain_settings(bs):
    print(bs.cores)
    print(bs.priority)
    print(bs.byte_fee_satoshis)
    print(bs.sigop_fee_satoshis)
    print(bs.minimum_output_satoshis)
    print(bs.notify_limit_hours)
    print(bs.reorganization_limit)

    for c in bs.checkpoints:
        print( hash_to_str(c.hash) )
        print(c.height)

    print(bs.fix_checkpoints)
    print(bs.allow_collisions)
    print(bs.easy_blocks)
    print(bs.retarget)
    print(bs.bip16)
    print(bs.bip30)
    print(bs.bip34)
    print(bs.bip66)
    print(bs.bip65)
    print(bs.bip90)
    print(bs.bip68)
    print(bs.bip112)
    print(bs.bip113)
    print(bs.bch_uahf)
    print(bs.bch_daa_cw144)
    print(bs.bch_pythagoras)
    print(bs.bch_euclid)
    print(bs.bch_pisano)
    print(bs.bch_mersenne)
    print(bs.bch_fermat)
    print(bs.bch_euler)
    print(bs.gauss_activation_time)
    print(bs.descartes_activation_time)
    print(bs.asert_half_life)

def print_network_settings(ns):
    print(ns.threads)
    print(ns.protocol_maximum)
    print(ns.protocol_minimum)
    print(ns.services)
    print(ns.invalid_services)
    print(ns.relay_transactions)
    print(ns.validate_checksum)
    print(ns.identifier)
    print(ns.inbound_port)
    print(ns.inbound_connections)
    print(ns.outbound_connections)
    print(ns.manual_attempt_limit)
    print(ns.connect_batch_size)
    print(ns.connect_timeout_seconds)
    print(ns.channel_handshake_seconds)
    print(ns.channel_heartbeat_minutes)
    print(ns.channel_inactivity_minutes)
    print(ns.channel_expiration_minutes)
    print(ns.channel_germination_seconds)
    print(ns.host_pool_capacity)
    print(ns.hosts_file)

    print_authority(ns.self)

    print(ns.blacklist)

    for blacked in ns.blacklist:
        print_authority(blacked)

    for peer in ns.peers:
        print_endpoint(peer)

    for seed in ns.seeds:
        print_endpoint(seed)

    print(ns.debug_file)
    print(ns.error_file)
    print(ns.archive_directory)

    print(ns.rotation_size)
    print(ns.minimum_free_space)
    print(ns.maximum_archive_size)
    print(ns.maximum_archive_files)

    print_authority(ns.statistics_server)

    print(ns.verbose)
    print(ns.use_ipv6)

    print(ns.user_agent_blacklist)

stop_ = False
def signal_handler(signal, frame):
    print('You pressed Ctrl-C')
    global stop_
    stop_ = True

def handler(e):
    print(f'node run lambda: {e}')

# async def node_init_run_and_wait_for_signal_async(node, mods):
#     future = asyncio.Future()
#     loop = asyncio.get_event_loop()

#     def callback(*args):
#         loop.call_soon_threadsafe(future.set_result, args)

#     kth_native.node_init_run_and_wait_for_signal(node, mods, callback)
#     callback_args = await future
#     return callback_args[0]

async def async_exec(f, ret, *args):
    future = asyncio.Future()
    loop = asyncio.get_event_loop()

    def callback(*args):
        loop.call_soon_threadsafe(future.set_result, args)

    f(*args, callback)
    callback_args = await future
    # return callback_args[0]
    return callback_args[ret]

async def node_init_run_and_wait_for_signal_async(node, mods):
    return await async_exec(kth_native.node_init_run_and_wait_for_signal, 0, node, mods)

async def chain_fetch_last_height_async(chain):
    return await async_exec(kth_native.chain_fetch_last_height, 1, chain)

async def chain_fetch_block_by_height_async(chain, h):
    return await async_exec(kth_native.chain_fetch_block_by_height, 1, chain, h)


async def main():
    signal.signal(signal.SIGINT, signal_handler)
    signal.signal(signal.SIGTERM, signal_handler)

    setts = kth_native.config_settings_default(0)
    node = kth_native.node_construct(setts, False)

    e = await node_init_run_and_wait_for_signal_async(node, 0)
    print(f'node run lambda: {e}')

    chain = kth_native.node_get_chain(node)

    # print("before sleep")
    global stop_
    while not stop_:
        # print("sleeping...")
        # print(stop_)
        h = await chain_fetch_last_height_async(chain)
        print(f'Height:    {h}')
        b = await chain_fetch_block_by_height_async(chain, h)
        print(f'Block:     {b}')

        tx_list = kth_native.chain_block_transactions(b)
        print(f'Tx List:   {tx_list}')

        tx_list_n = kth_native.chain_transaction_list_count(tx_list)
        print(f'Tx List N: {tx_list_n}')

        time.sleep(1)
    print("after sleep")

    kth_native.node_signal_stop(node);
    kth_native.node_destruct(node);

routine = main()
asyncio.run(routine)
