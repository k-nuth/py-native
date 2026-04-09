# Copyright (c) 2016-present Knuth Project developers.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

"""Tests for the chain_block binding."""

import pytest

import kth_native as nat


def make_block():
    return nat.chain_block_genesis_mainnet()


def test_default_construct_is_invalid():
    b = nat.chain_block_construct_default()
    assert nat.chain_block_is_valid(b) is False


def test_genesis_mainnet_is_valid():
    b = make_block()
    assert nat.chain_block_is_valid(b) is True


def test_to_data_from_data_roundtrip():
    original = make_block()
    raw = nat.chain_block_to_data_simple(original)
    assert isinstance(raw, bytes)
    parsed = nat.chain_block_construct_from_data(raw, True)
    assert nat.chain_block_is_valid(parsed) is True
    assert nat.chain_block_equals(original, parsed) is True


def test_header_returns_borrowed_view():
    b = make_block()
    hdr = nat.chain_block_header(b)
    # Must be a real Header capsule, not the Block's.
    assert nat.chain_header_version(hdr) > 0


def test_transactions_returns_borrowed_view():
    b = make_block()
    txs = nat.chain_block_transactions(b)
    # Genesis block has exactly 1 transaction.
    assert nat.chain_transaction_list_count(txs) == 1


def test_hash_is_stable_across_calls():
    b = make_block()
    a = nat.chain_block_hash(b)
    bb = nat.chain_block_hash(b)
    assert a == bb


def test_serialized_size_matches_to_data_length():
    b = make_block()
    raw = nat.chain_block_to_data_simple(b)
    assert nat.chain_block_serialized_size(b) == len(raw)


def test_genesis_has_valid_merkle_root():
    b = make_block()
    assert nat.chain_block_is_valid_merkle_root(b) is True


def test_copy_preserves_fields():
    original = make_block()
    copy = nat.chain_block_copy(original)
    assert nat.chain_block_equals(original, copy) is True


def test_equals_identical_is_true_different_is_false():
    a = make_block()
    b = make_block()
    c = nat.chain_block_construct_default()
    assert nat.chain_block_equals(a, b) is True
    assert nat.chain_block_equals(a, c) is False


def test_capsule_destructor_released_on_gc():
    """Creating and dropping a block without calling destruct explicitly
    must not leak. The capsule destructor is supposed to free the
    underlying handle when the Python object is garbage-collected.
    We cannot observe the native free directly, but we can at least
    confirm the flow doesn't crash and the GC runs cleanly."""
    import gc
    for _ in range(100):
        _ = nat.chain_block_genesis_mainnet()  # dropped immediately
    gc.collect()
    # If the destructor was wired correctly the loop above didn't leak
    # and GC didn't explode. If the destructor was NULL and the handle
    # was leaked, this test still passes (can't catch leaks without
    # valgrind), but at least it exercises the GC path.


def test_header_borrowed_view_survives_block_use():
    """chain_block_header returns a borrowed view. The capsule must NOT
    carry a destructor for the header, otherwise freeing it would
    double-free through the block. If the wiring is wrong, any access
    to the header after the block is collected explodes."""
    blk = make_block()
    hdr = nat.chain_block_header(blk)
    assert nat.chain_header_version(hdr) > 0
    # The header is a borrowed view — the block still owns it. We don't
    # destruct it here; the test passes if the block's own lifetime
    # wasn't corrupted by any destructor misconfiguration on the header
    # capsule.
