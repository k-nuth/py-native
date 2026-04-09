# Copyright (c) 2016-present Knuth Project developers.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

"""Tests for the chain_output binding."""

import pytest

import kth_native as nat


VALUE = 50000

SCRIPT_BODY = bytes((0x01, 0x6a))


def make_output():
    """Build an output with a given value and a minimal script via setters."""
    out = nat.chain_output_construct_default()
    nat.chain_output_set_value(out, VALUE)
    s = nat.chain_script_construct_from_data(SCRIPT_BODY, True)
    nat.chain_output_set_script(out, s)
    return out


def test_default_construct_is_invalid():
    out = nat.chain_output_construct_default()
    assert nat.chain_output_is_valid(out) is False


def test_value_setter_roundtrip():
    out = nat.chain_output_construct_default()
    nat.chain_output_set_value(out, VALUE)
    assert nat.chain_output_value(out) == VALUE


def test_script_setter_roundtrip():
    out = nat.chain_output_construct_default()
    s = nat.chain_script_construct_from_data(SCRIPT_BODY, True)
    nat.chain_output_set_script(out, s)
    # The returned view must be a valid Script capsule.
    view = nat.chain_output_script(out)
    assert nat.chain_script_empty(view) is False


def test_to_data_from_data_roundtrip():
    original = make_output()
    raw = nat.chain_output_to_data(original, True)
    assert isinstance(raw, bytes)
    parsed = nat.chain_output_construct_from_data(raw, True)
    assert nat.chain_output_equals(original, parsed) is True


def test_copy_preserves_fields():
    original = make_output()
    copy = nat.chain_output_copy(original)
    assert nat.chain_output_equals(original, copy) is True
    assert nat.chain_output_value(copy) == VALUE
