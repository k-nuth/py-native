# Copyright (c) 2016-present Knuth Project developers.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

"""Tests for chain_utxo + chain_utxo_list bindings."""

import kth_native as nat


HEIGHT = 812_345
AMOUNT = 100_000_000  # 1 BCH in satoshis


def _make_output_point():
    prev_hash = bytes(range(32))
    return nat.chain_output_point_construct_from_hash_index(prev_hash, 7)


def test_utxo_default_construct_and_destruct():
    u = nat.chain_utxo_construct_default()
    nat.chain_utxo_destruct(u)


def test_utxo_height_round_trip():
    u = nat.chain_utxo_construct_default()
    nat.chain_utxo_set_height(u, HEIGHT)
    assert nat.chain_utxo_height(u) == HEIGHT


def test_utxo_amount_round_trip():
    u = nat.chain_utxo_construct_default()
    nat.chain_utxo_set_amount(u, AMOUNT)
    assert nat.chain_utxo_amount(u) == AMOUNT


def test_utxo_point_round_trip():
    u = nat.chain_utxo_construct_default()
    op = _make_output_point()
    nat.chain_utxo_set_point(u, op)
    stored = nat.chain_utxo_point(u)
    assert stored is not None
    assert nat.chain_output_point_equals(stored, op) is True


def test_utxo_copy_is_independent_value():
    u = nat.chain_utxo_construct_default()
    nat.chain_utxo_set_amount(u, AMOUNT)
    dup = nat.chain_utxo_copy(u)
    assert nat.chain_utxo_amount(dup) == AMOUNT
    assert nat.chain_utxo_equals(u, dup) is True
    # Mutate the duplicate: a faulty `copy` that returned an alias
    # to the same native object would make the mutation visible on
    # the original. With a real deep copy the two handles drift
    # apart as independent values.
    nat.chain_utxo_set_amount(dup, AMOUNT + 1)
    assert nat.chain_utxo_amount(u) == AMOUNT
    assert nat.chain_utxo_amount(dup) == AMOUNT + 1
    assert nat.chain_utxo_equals(u, dup) is False


def test_utxo_equals_detects_mismatch():
    a = nat.chain_utxo_construct_default()
    b = nat.chain_utxo_construct_default()
    nat.chain_utxo_set_height(a, HEIGHT)
    nat.chain_utxo_set_height(b, HEIGHT + 1)
    assert nat.chain_utxo_equals(a, b) is False


# ─── UtxoList ───────────────────────────────────────────────────

def test_utxo_list_default_construct_is_empty():
    lst = nat.chain_utxo_list_construct_default()
    assert nat.chain_utxo_list_count(lst) == 0
    nat.chain_utxo_list_destruct(lst)


def test_utxo_list_push_back_and_nth():
    lst = nat.chain_utxo_list_construct_default()
    u = nat.chain_utxo_construct_default()
    nat.chain_utxo_set_amount(u, AMOUNT)
    nat.chain_utxo_list_push_back(lst, u)
    assert nat.chain_utxo_list_count(lst) == 1
    got = nat.chain_utxo_list_nth(lst, 0)
    assert nat.chain_utxo_amount(got) == AMOUNT


def test_utxo_list_erase_shrinks_count():
    lst = nat.chain_utxo_list_construct_default()
    nat.chain_utxo_list_push_back(lst, nat.chain_utxo_construct_default())
    nat.chain_utxo_list_push_back(lst, nat.chain_utxo_construct_default())
    nat.chain_utxo_list_erase(lst, 0)
    assert nat.chain_utxo_list_count(lst) == 1
