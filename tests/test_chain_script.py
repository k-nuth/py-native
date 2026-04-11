# Copyright (c) 2016-present Knuth Project developers.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

"""Tests for the chain_script binding."""

import pytest

import kth_native as nat


# Trivial OP_RETURN script: one byte (0x6a). Wire layout: a 1-byte
# length prefix (0x01), then the OP_RETURN opcode. Mirrors the C-API
# script test fixture.
PREFIXED_BODY = bytes((0x01, 0x6a))
RAW_BODY = bytes((0x6a,))


def test_default_construct_is_empty():
    s = nat.chain_script_construct_default()
    assert nat.chain_script_empty(s) is True
    assert nat.chain_script_size(s) == 0


def test_from_data_prefixed_roundtrip():
    s = nat.chain_script_construct_from_data(PREFIXED_BODY, True)
    assert nat.chain_script_empty(s) is False
    assert nat.chain_script_size(s) == 1  # one operation


def test_from_data_raw_roundtrip():
    s = nat.chain_script_construct_from_encoded_prefix(RAW_BODY, False)
    assert nat.chain_script_empty(s) is False


def test_clear_empties_script():
    s = nat.chain_script_construct_from_data(PREFIXED_BODY, True)
    assert nat.chain_script_empty(s) is False
    nat.chain_script_clear(s)
    assert nat.chain_script_empty(s) is True


def test_copy_preserves_equality():
    original = nat.chain_script_construct_from_data(PREFIXED_BODY, True)
    copy = nat.chain_script_copy(original)
    assert nat.chain_script_equals(original, copy) is True
    assert nat.chain_script_size(copy) == nat.chain_script_size(original)


def test_equals_different_scripts():
    a = nat.chain_script_construct_from_data(PREFIXED_BODY, True)
    b = nat.chain_script_construct_default()
    assert nat.chain_script_equals(a, b) is False


def test_from_string_empty_mnemonic():
    s = nat.chain_script_construct_default()
    assert nat.chain_script_from_string(s, "") is True
    assert nat.chain_script_empty(s) is True


def test_is_enabled_bit_test():
    flags = 0x05  # bits 0 and 2 set
    assert nat.chain_script_is_enabled(flags, 0x01) is True
    assert nat.chain_script_is_enabled(flags, 0x04) is True
    assert nat.chain_script_is_enabled(flags, 0x02) is False
