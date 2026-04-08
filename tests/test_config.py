# Copyright (c) 2016-present Knuth Project developers.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

import kth_native


def hash_to_hex(hash_bytes):
    return "".join(f"{x:02x}" for x in hash_bytes[::-1])


# kth_db_mode_t enum (from kth/capi/primitives.h)
DB_MODE_PRUNED = 0
DB_MODE_NORMAL = 1
DB_MODE_FULL_INDEXED = 2

# Hard-fork activation timestamps (kth/0.78.0). Update when the C-API moves
# the next-fork goalposts.
LEIBNIZ_ACTIVATION_TIME = 1778846400  # 2026-May-15 12:00 UTC
CANTOR_ACTIVATION_TIME = 1810382400   # 2027-May-15 12:00 UTC


def _assert_common_chain_defaults(c):
    """Fields whose default is the same across all networks."""
    assert c.cores == 0
    assert c.priority
    assert 0.1 <= c.byte_fee_satoshis <= 0.11
    assert c.sigop_fee_satoshis == 100.0
    assert c.minimum_output_satoshis == 500
    assert c.notify_limit_hours == 24
    assert c.reorganization_limit == 256
    assert c.fix_checkpoints
    assert c.allow_collisions
    assert c.retarget
    # BIPs — all active by default on every network we ship.
    for bip in (
        "bip16", "bip30", "bip34", "bip66", "bip65",
        "bip90", "bip68", "bip112", "bip113",
    ):
        assert getattr(c, bip), bip
    # BCH hard-forks already activated on every network we ship.
    for fork in (
        "bch_uahf", "bch_daa_cw144", "bch_pythagoras", "bch_euclid",
        "bch_pisano", "bch_mersenne", "bch_fermat", "bch_euler",
        "bch_gauss", "bch_descartes", "bch_lobachevski", "bch_galois",
    ):
        assert getattr(c, fork), fork
    # Future hard-forks: timestamps only, flags don't exist yet.
    assert c.leibniz_activation_time == LEIBNIZ_ACTIVATION_TIME
    assert c.cantor_activation_time == CANTOR_ACTIVATION_TIME


def _assert_common_database_defaults(d):
    assert d.directory == "blockchain"
    assert d.db_mode == DB_MODE_NORMAL
    assert d.reorg_pool_limit == 100
    assert d.safe_mode
    assert d.cache_capacity == 0


def _assert_common_network_defaults(n):
    assert n.threads == 0
    assert n.protocol_maximum == 70015
    assert n.protocol_minimum == 31402
    assert n.services == 1
    assert n.invalid_services == 0
    assert n.relay_transactions
    assert not n.validate_checksum
    assert n.inbound_connections == 0
    assert n.outbound_connections == 8
    assert n.manual_attempt_limit == 0
    assert n.connect_batch_size == 5
    assert n.connect_timeout_seconds == 5
    assert n.channel_handshake_seconds == 6000
    assert n.channel_heartbeat_minutes == 5
    assert n.channel_inactivity_minutes == 10
    assert n.channel_expiration_minutes == 60
    assert n.channel_germination_seconds == 30
    assert n.host_pool_capacity == 1000
    assert n.hosts_file == "hosts.cache"
    assert n.self.port == 0
    assert len(n.blacklist) == 0
    assert len(n.peers) == 0
    assert n.debug_file == "debug.log"
    assert n.error_file == "error.log"
    assert n.archive_directory == "archive"
    assert n.rotation_size == 0
    assert n.minimum_free_space == 0
    assert n.maximum_archive_size == 0
    assert n.maximum_archive_files == 0
    assert n.statistics_server.port == 0
    assert not n.verbose
    assert n.use_ipv6
    assert list(n.user_agent_blacklist) == ["/Bitcoin SV:"]


def _assert_common_node_defaults(node):
    assert node.sync_peers == 0
    assert node.sync_timeout_seconds == 5
    assert node.block_latency_seconds == 60
    assert node.refresh_transactions
    assert node.compact_blocks_high_bandwidth


def test_default_mainnet_settings():
    setts = kth_native.config_settings_default(0)  # mainnet

    _assert_common_chain_defaults(setts.chain)
    assert not setts.chain.easy_blocks
    assert setts.chain.asert_half_life == 2 * 24 * 60 * 60  # two days
    # The genesis checkpoint is fixed forever.
    assert setts.chain.checkpoints[0].height == 0
    assert (
        hash_to_hex(setts.chain.checkpoints[0].hash)
        == "000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f"
    )
    # Sanity bound rather than exact count: new checkpoints are added every
    # so often, hardcoding the exact number creates churn.
    assert len(setts.chain.checkpoints) >= 64

    _assert_common_database_defaults(setts.database)
    assert setts.database.db_max_size == 400 * 1024 * 1024 * 1024  # 400 GiB

    _assert_common_network_defaults(setts.network)
    assert setts.network.identifier == 3908297187
    assert setts.network.inbound_port == 8333
    assert len(setts.network.seeds) >= 6
    assert setts.network.seeds[0].scheme == ""
    assert setts.network.seeds[0].host == "seed.flowee.cash"
    assert setts.network.seeds[0].port == 8333

    _assert_common_node_defaults(setts.node)


def test_default_testnet4_settings():
    setts = kth_native.config_settings_default(3)  # testnet4

    _assert_common_chain_defaults(setts.chain)
    assert setts.chain.easy_blocks
    assert setts.chain.asert_half_life == 60 * 60  # one hour
    assert setts.chain.checkpoints[0].height == 0
    assert (
        hash_to_hex(setts.chain.checkpoints[0].hash)
        == "000000001dd410c49a788668ce26751718cc797474d3152a5fc073dd44fd9f7b"
    )
    assert len(setts.chain.checkpoints) >= 18

    _assert_common_database_defaults(setts.database)
    assert setts.database.db_max_size == 20 * 1024 * 1024 * 1024  # 20 GiB

    _assert_common_network_defaults(setts.network)
    assert setts.network.identifier == 2950346722
    assert setts.network.inbound_port == 28333
    assert len(setts.network.seeds) >= 3

    _assert_common_node_defaults(setts.node)
