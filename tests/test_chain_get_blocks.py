# Copyright (c) 2016-present Knuth Project developers.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

"""Tests for chain_get_blocks + chain_get_headers bindings.

`get_blocks` and `get_headers` share an identical layout (a list of
start hashes + a stop hash). The regen exposes them through separate
ClassConfigs but the surface is literally symmetric, so we exercise
them with the same fixtures.
"""

import kth_native as nat


PROTOCOL_VERSION = 70015

STOP_HASH = bytes(range(32))


# ─── get_blocks ──────────────────────────────────────────────────────

def test_get_blocks_default_construct_and_destruct():
    gb = nat.chain_get_blocks_construct_default()
    nat.chain_get_blocks_destruct(gb)


def test_get_blocks_stop_hash_round_trip():
    gb = nat.chain_get_blocks_construct_default()
    nat.chain_get_blocks_set_stop_hash(gb, STOP_HASH)
    assert nat.chain_get_blocks_stop_hash(gb) == STOP_HASH


def test_get_blocks_copy_preserves_stop_hash():
    gb = nat.chain_get_blocks_construct_default()
    nat.chain_get_blocks_set_stop_hash(gb, STOP_HASH)
    dup = nat.chain_get_blocks_copy(gb)
    assert nat.chain_get_blocks_stop_hash(dup) == STOP_HASH
    assert nat.chain_get_blocks_equals(gb, dup) is True


def test_get_blocks_serialized_round_trips_through_from_data():
    gb = nat.chain_get_blocks_construct_default()
    nat.chain_get_blocks_set_stop_hash(gb, STOP_HASH)
    wire = nat.chain_get_blocks_to_data(gb, PROTOCOL_VERSION)
    assert len(wire) == nat.chain_get_blocks_serialized_size(gb, PROTOCOL_VERSION)
    restored = nat.chain_get_blocks_construct_from_data(wire, PROTOCOL_VERSION)
    assert nat.chain_get_blocks_equals(gb, restored) is True


def test_get_blocks_reset_clears_state():
    gb = nat.chain_get_blocks_construct_default()
    nat.chain_get_blocks_set_stop_hash(gb, STOP_HASH)
    nat.chain_get_blocks_reset(gb)
    assert nat.chain_get_blocks_stop_hash(gb) == bytes(32)


# ─── get_headers ─────────────────────────────────────────────────────

def test_get_headers_default_construct_and_destruct():
    gh = nat.chain_get_headers_construct_default()
    nat.chain_get_headers_destruct(gh)


def test_get_headers_stop_hash_round_trip():
    gh = nat.chain_get_headers_construct_default()
    nat.chain_get_headers_set_stop_hash(gh, STOP_HASH)
    assert nat.chain_get_headers_stop_hash(gh) == STOP_HASH


def test_get_headers_serialized_round_trips_through_from_data():
    gh = nat.chain_get_headers_construct_default()
    nat.chain_get_headers_set_stop_hash(gh, STOP_HASH)
    wire = nat.chain_get_headers_to_data(gh, PROTOCOL_VERSION)
    assert len(wire) == nat.chain_get_headers_serialized_size(gh, PROTOCOL_VERSION)
    restored = nat.chain_get_headers_construct_from_data(wire, PROTOCOL_VERSION)
    assert nat.chain_get_headers_equals(gh, restored) is True
