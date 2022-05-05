# Copyright (c) 2016-2022 Knuth Project developers.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

import kth_native

def hash_to_str(hash):
    return bytes(reversed(hash)).hex()

def print_authority(authority):
    print(f'ip: {authority.ip}, port: {authority.port}')
    # {"ip", T_OBJECT_EX, offsetof(Authority, ip), 0, "ip"},
    # {"port", T_UINT, offsetof(Authority, port), 0, "port"},

def print_endpoint(endpoint):
    print(f'scheme: {endpoint.scheme}, host: {endpoint.host}, port: {endpoint.port}')

    # {"scheme", T_OBJECT_EX, offsetof(Endpoint, scheme), 0, "scheme"},
    # {"host", T_OBJECT_EX, offsetof(Endpoint, host), 0, "host"},
    # {"port", T_UINT, offsetof(Endpoint, port), 0, "port"},

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

# --------------------------------------------------------------------------------------------------------

# ns = kth_native.config_node_settings_default(0)
# print_node_settings(ns)

# ds = kth_native.config_database_settings_default(0)
# print_database_settings(ds)

# bs = kth_native.config_blockchain_settings_default(0)
# print_blockchain_settings(bs)

# ns = kth_native.config_network_settings_default(0)
# print_network_settings(ns)


# --------------------------------------------------------------------------------------------------------


# setts = kth_native.config_settings_default(0)
# print_node_settings(setts.node)
# print_database_settings(setts.database)
# print_blockchain_settings(setts.chain)
# print_network_settings(setts.network)

# --------------------------------------------------------------------------------------------------------

# res = kth_native.config_settings_get_from_file("/Users/fernando/dev/kth/py-native/examples/example.cfg")
res = kth_native.config_settings_get_from_file("/Users/fernando/dev/kth/py-native/examples/example-fail.cfg")
if not res[0]:
    raise Exception("error loading cfg file")

setts = res[1]
print_node_settings(setts.node)
print_database_settings(setts.database)
print_blockchain_settings(setts.chain)
print_network_settings(setts.network)








# ---------------------------------------------------------------------





# c = kth_native.Custom()
# print(c.first)
# print(c.last)
# print(c.number)
# # print(c.something)
