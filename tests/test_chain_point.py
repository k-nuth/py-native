# Copyright (c) 2016-present Knuth Project developers.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

"""Tests for the chain_point binding."""

import pytest

import kth_native as nat


HASH = bytes((
    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
    0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10,
    0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
    0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20,
))

INDEX = 42


def test_default_construct_is_invalid():
    p = nat.chain_point_construct_default()
    assert nat.chain_point_is_valid(p) is False


def test_field_constructor_preserves_fields():
    p = nat.chain_point_construct(HASH, INDEX)
    assert nat.chain_point_is_valid(p) is True
    assert nat.chain_point_hash(p) == HASH
    assert nat.chain_point_index(p) == INDEX


def test_to_data_from_data_roundtrip():
    original = nat.chain_point_construct(HASH, INDEX)
    raw = nat.chain_point_to_data(original, True)
    assert isinstance(raw, bytes)
    assert len(raw) > 0

    parsed = nat.chain_point_construct_from_data(raw, True)
    assert nat.chain_point_is_valid(parsed) is True
    assert nat.chain_point_equals(original, parsed) is True


def test_hash_setter_roundtrip():
    p = nat.chain_point_construct_default()
    nat.chain_point_set_hash(p, HASH)
    assert nat.chain_point_hash(p) == HASH


def test_index_setter_roundtrip():
    p = nat.chain_point_construct_default()
    nat.chain_point_set_index(p, INDEX)
    assert nat.chain_point_index(p) == INDEX


def test_copy_preserves_fields():
    original = nat.chain_point_construct(HASH, INDEX)
    copy = nat.chain_point_copy(original)
    assert nat.chain_point_is_valid(copy) is True
    assert nat.chain_point_equals(original, copy) is True
    assert nat.chain_point_hash(copy) == HASH
    assert nat.chain_point_index(copy) == INDEX


def test_equals_identical_is_true_different_is_false():
    a = nat.chain_point_construct(HASH, INDEX)
    b = nat.chain_point_construct(HASH, INDEX)
    c = nat.chain_point_construct_default()
    assert nat.chain_point_equals(a, b) is True
    assert nat.chain_point_equals(a, c) is False


def test_satoshi_fixed_size_is_36():
    # 32-byte hash + 4-byte index
    assert nat.chain_point_satoshi_fixed_size() == 36


def test_construct_with_wrong_hash_size_raises():
    with pytest.raises(ValueError):
        nat.chain_point_construct(b'\x00' * 31, INDEX)


def test_set_hash_wrong_size_raises():
    p = nat.chain_point_construct_default()
    with pytest.raises(ValueError):
        nat.chain_point_set_hash(p, b'\x00' * 31)
