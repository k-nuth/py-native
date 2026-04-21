# Copyright (c) 2016-present Knuth Project developers.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

"""Tests for chain_prefilled_transaction + list bindings."""

import kth_native as nat


PROTOCOL_VERSION = 70015

INDEX = 42


def _make_transaction():
    return nat.chain_transaction_construct_default()


def test_prefilled_transaction_default_construct_and_destruct():
    pt = nat.chain_prefilled_transaction_construct_default()
    nat.chain_prefilled_transaction_destruct(pt)


def test_prefilled_transaction_index_round_trip():
    pt = nat.chain_prefilled_transaction_construct_default()
    nat.chain_prefilled_transaction_set_index(pt, INDEX)
    assert nat.chain_prefilled_transaction_index(pt) == INDEX


def test_prefilled_transaction_transaction_round_trip():
    pt = nat.chain_prefilled_transaction_construct_default()
    tx = _make_transaction()
    nat.chain_prefilled_transaction_set_transaction(pt, tx)
    got = nat.chain_prefilled_transaction_transaction(pt)
    assert got is not None
    # Confirm the setter/getter pair actually round-trips the value —
    # not just that *something* non-null came back. Uses the native
    # transaction-equality predicate so we exercise the C-API rather
    # than Python identity.
    assert nat.chain_transaction_equals(tx, got) is True


def test_prefilled_transaction_copy_preserves_index():
    pt = nat.chain_prefilled_transaction_construct_default()
    nat.chain_prefilled_transaction_set_index(pt, INDEX)
    dup = nat.chain_prefilled_transaction_copy(pt)
    assert nat.chain_prefilled_transaction_index(dup) == INDEX
    assert nat.chain_prefilled_transaction_equals(pt, dup) is True


def test_prefilled_transaction_equals_detects_index_mismatch():
    a = nat.chain_prefilled_transaction_construct_default()
    b = nat.chain_prefilled_transaction_construct_default()
    nat.chain_prefilled_transaction_set_index(a, INDEX)
    nat.chain_prefilled_transaction_set_index(b, INDEX + 1)
    assert nat.chain_prefilled_transaction_equals(a, b) is False


def test_prefilled_transaction_wire_round_trip():
    """`to_data(version)` → `construct_from_data(version)` round-trips
    the full payload. Mirrors the same round-trip we exercise on the
    other wire-format message classes (`get_blocks`, `get_headers`,
    ...) so a regression in the serializer on either side fails
    visibly."""
    pt = nat.chain_prefilled_transaction_construct_default()
    nat.chain_prefilled_transaction_set_index(pt, INDEX)
    nat.chain_prefilled_transaction_set_transaction(pt, _make_transaction())
    wire = nat.chain_prefilled_transaction_to_data(pt, PROTOCOL_VERSION)
    assert len(wire) == nat.chain_prefilled_transaction_serialized_size(pt, PROTOCOL_VERSION)
    restored = nat.chain_prefilled_transaction_construct_from_data(wire, PROTOCOL_VERSION)
    assert nat.chain_prefilled_transaction_equals(pt, restored) is True


# ─── PrefilledTransactionList ────────────────────────────────────────

def test_prefilled_transaction_list_default_construct_is_empty():
    lst = nat.chain_prefilled_transaction_list_construct_default()
    assert nat.chain_prefilled_transaction_list_count(lst) == 0
    nat.chain_prefilled_transaction_list_destruct(lst)


def test_prefilled_transaction_list_push_back_and_nth():
    lst = nat.chain_prefilled_transaction_list_construct_default()
    pt = nat.chain_prefilled_transaction_construct_default()
    nat.chain_prefilled_transaction_set_index(pt, INDEX)
    nat.chain_prefilled_transaction_list_push_back(lst, pt)
    assert nat.chain_prefilled_transaction_list_count(lst) == 1
    got = nat.chain_prefilled_transaction_list_nth(lst, 0)
    assert nat.chain_prefilled_transaction_index(got) == INDEX
