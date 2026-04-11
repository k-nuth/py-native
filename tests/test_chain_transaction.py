# Copyright (c) 2016-present Knuth Project developers.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

"""Tests for the chain_transaction binding."""

import pytest

import kth_native as nat


VERSION = 2
LOCKTIME = 0

PREV_HASH = bytes((
    0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7,
    0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf,
    0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xb7,
    0xb8, 0xb9, 0xba, 0xbb, 0xbc, 0xbd, 0xbe, 0xbf,
))

SCRIPT_BODY = bytes((0x01, 0x6a))


def make_script():
    return nat.chain_script_construct_from_data(SCRIPT_BODY, True)


def make_inputs():
    lst = nat.chain_input_list_construct_default()
    op = nat.chain_output_point_construct_from_hash_index(PREV_HASH, 0)
    s = make_script()
    inp = nat.chain_input_construct(
        previous_output=op,
        script=s,
        sequence=0xffffffff,
    )
    nat.chain_input_list_push_back(list=lst, elem=inp)
    return lst


def make_outputs():
    lst = nat.chain_output_list_construct_default()
    out = nat.chain_output_construct_default()
    nat.chain_output_set_value(out, 50000)
    nat.chain_output_set_script(out, make_script())
    nat.chain_output_list_push_back(list=lst, elem=out)
    return lst


def make_tx():
    return nat.chain_transaction_construct_from_version_locktime_inputs_outputs(
        version=VERSION,
        locktime=LOCKTIME,
        inputs=make_inputs(),
        outputs=make_outputs(),
    )


def test_default_construct_is_invalid():
    tx = nat.chain_transaction_construct_default()
    assert nat.chain_transaction_is_valid(tx) is False


def test_field_constructor_preserves_fields():
    tx = make_tx()
    assert nat.chain_transaction_is_valid(tx) is True
    assert nat.chain_transaction_version(tx) == VERSION
    assert nat.chain_transaction_locktime(tx) == LOCKTIME


def test_to_data_from_data_roundtrip():
    original = make_tx()
    raw = nat.chain_transaction_to_data(original, True)
    assert isinstance(raw, bytes)
    parsed = nat.chain_transaction_construct_from_data(raw, True)
    assert nat.chain_transaction_is_valid(parsed) is True
    assert nat.chain_transaction_equals(original, parsed) is True


def test_version_setter_roundtrip():
    tx = nat.chain_transaction_construct_default()
    nat.chain_transaction_set_version(tx, VERSION)
    assert nat.chain_transaction_version(tx) == VERSION


def test_locktime_setter_roundtrip():
    tx = nat.chain_transaction_construct_default()
    nat.chain_transaction_set_locktime(tx, 12345)
    assert nat.chain_transaction_locktime(tx) == 12345


def test_default_is_not_coinbase():
    tx = nat.chain_transaction_construct_default()
    assert nat.chain_transaction_is_coinbase(tx) is False


def test_hash_is_stable_across_calls():
    tx = make_tx()
    a = nat.chain_transaction_hash(tx)
    b = nat.chain_transaction_hash(tx)
    assert a == b


def test_copy_preserves_fields():
    original = make_tx()
    copy = nat.chain_transaction_copy(original)
    assert nat.chain_transaction_equals(original, copy) is True
    assert nat.chain_transaction_version(copy) == VERSION
    assert nat.chain_transaction_locktime(copy) == LOCKTIME


def test_equals_identical_is_true_different_is_false():
    a = nat.chain_transaction_construct_default()
    b = nat.chain_transaction_construct_default()
    c = make_tx()
    assert nat.chain_transaction_equals(a, b) is True
    assert nat.chain_transaction_equals(a, c) is False
