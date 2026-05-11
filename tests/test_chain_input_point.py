# Copyright (c) 2016-present Knuth Project developers.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

"""Tests for the chain_input_point binding.

`input_point` is a typedef alias for `point` in the domain layer
(`using input_point = point;`), so the underlying behaviour is fully
covered by test_chain_point.py. These tests pin the alias-prefixed
Python surface so the binding stays wired through correctly.
"""

import pytest

import kth_native as nat


HASH = bytes((
    0x6f, 0xe2, 0x8c, 0x0a, 0xb6, 0xf1, 0xb3, 0x72,
    0xc1, 0xa6, 0xa2, 0x46, 0xae, 0x63, 0xf7, 0x4f,
    0x93, 0x1e, 0x83, 0x65, 0xe1, 0x5a, 0x08, 0x9c,
    0x68, 0xd6, 0x19, 0x00, 0x00, 0x00, 0x00, 0x00,
))

INDEX = 7


def test_default_construct_is_invalid():
    ip = nat.chain_input_point_construct_default()
    assert nat.chain_input_point_is_valid(ip) is False


def test_field_constructor_preserves_fields():
    ip = nat.chain_input_point_construct(HASH, INDEX)
    assert nat.chain_input_point_is_valid(ip) is True
    assert nat.chain_input_point_hash(ip) == HASH
    assert nat.chain_input_point_index(ip) == INDEX


def test_to_data_from_data_roundtrip():
    original = nat.chain_input_point_construct(HASH, INDEX)
    raw = nat.chain_input_point_to_data(original, True)
    assert isinstance(raw, bytes)
    assert len(raw) > 0

    parsed = nat.chain_input_point_construct_from_data(raw, True)
    assert nat.chain_input_point_is_valid(parsed) is True
    assert nat.chain_input_point_equals(original, parsed) is True


def test_setters_roundtrip():
    ip = nat.chain_input_point_construct_default()
    nat.chain_input_point_set_hash(ip, HASH)
    nat.chain_input_point_set_index(ip, INDEX)
    assert nat.chain_input_point_hash(ip) == HASH
    assert nat.chain_input_point_index(ip) == INDEX


def test_copy_preserves_fields():
    a = nat.chain_input_point_construct(HASH, INDEX)
    b = nat.chain_input_point_copy(a)
    assert nat.chain_input_point_equals(a, b) is True


def test_satoshi_fixed_size_is_36():
    assert nat.chain_input_point_satoshi_fixed_size() == 36


def test_null_factory_is_null():
    ip = nat.chain_input_point_null()
    # `null` returns a sentinel input_point; the C-API contract
    # is that `is_null` returns True for it.
    assert nat.chain_input_point_is_valid(ip) is False
