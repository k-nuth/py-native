# Copyright (c) 2016-present Knuth Project developers.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

"""Tests for the chain_output_point binding."""

import pytest

import kth_native as nat


HASH = bytes((
    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
    0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10,
    0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
    0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20,
))

INDEX = 7


def test_default_construct_is_invalid():
    op = nat.chain_output_point_construct_default()
    assert nat.chain_output_point_is_valid(op) is False


def test_field_constructor_preserves_fields():
    op = nat.chain_output_point_construct_from_hash_index(HASH, INDEX)
    assert nat.chain_output_point_is_valid(op) is True
    assert nat.chain_output_point_hash(op) == HASH
    assert nat.chain_output_point_index(op) == INDEX


def test_to_data_from_data_roundtrip():
    original = nat.chain_output_point_construct_from_hash_index(HASH, INDEX)
    raw = nat.chain_output_point_to_data(original, True)
    assert isinstance(raw, bytes)
    parsed = nat.chain_output_point_construct_from_data(raw, True)
    assert nat.chain_output_point_equals(original, parsed) is True


def test_hash_setter_roundtrip():
    op = nat.chain_output_point_construct_default()
    nat.chain_output_point_set_hash(op, HASH)
    assert nat.chain_output_point_hash(op) == HASH


def test_index_setter_roundtrip():
    op = nat.chain_output_point_construct_default()
    nat.chain_output_point_set_index(op, INDEX)
    assert nat.chain_output_point_index(op) == INDEX


def test_copy_preserves_fields():
    original = nat.chain_output_point_construct_from_hash_index(HASH, INDEX)
    copy = nat.chain_output_point_copy(original)
    assert nat.chain_output_point_equals(original, copy) is True
    assert nat.chain_output_point_hash(copy) == HASH
    assert nat.chain_output_point_index(copy) == INDEX


def test_satoshi_fixed_size_is_36():
    assert nat.chain_output_point_satoshi_fixed_size() == 36


def test_construct_with_wrong_hash_size_raises():
    with pytest.raises(ValueError):
        nat.chain_output_point_construct_from_hash_index(b'\x00' * 31, INDEX)


def test_construct_from_point_preserves_fields():
    """output_point(point) copy-constructs from a point — verify it
    accepts a Point capsule, not some other type."""
    p = nat.chain_point_construct(HASH, INDEX)
    op = nat.chain_output_point_construct_from_point(p)
    assert nat.chain_output_point_is_valid(op) is True
    assert nat.chain_output_point_hash(op) == HASH
    assert nat.chain_output_point_index(op) == INDEX
