# Copyright (c) 2016-present Knuth Project developers.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

"""Tests for the vm_big_number binding."""

import pytest

import kth_native as nat


def test_default_is_zero():
    n = nat.vm_big_number_construct_default()
    assert nat.vm_big_number_is_zero(n) is True
    assert nat.vm_big_number_sign(n) == 0


def test_from_value_positive():
    n = nat.vm_big_number_construct_from_value(42)
    assert nat.vm_big_number_is_zero(n) is False
    assert nat.vm_big_number_is_nonzero(n) is True
    assert nat.vm_big_number_is_negative(n) is False
    assert nat.vm_big_number_sign(n) == 1
    assert nat.vm_big_number_to_string(n) == "42"


def test_from_value_negative():
    n = nat.vm_big_number_construct_from_value(-7)
    assert nat.vm_big_number_is_negative(n) is True
    assert nat.vm_big_number_sign(n) == -1
    assert nat.vm_big_number_to_string(n) == "-7"


def test_from_decimal_str_large_value():
    # 2^100 — far beyond int64 range.
    big = nat.vm_big_number_construct_from_decimal_str(
        "1267650600228229401496703205376")
    assert nat.vm_big_number_is_negative(big) is False
    assert nat.vm_big_number_to_string(big) == "1267650600228229401496703205376"


def test_from_hex_roundtrip():
    n = nat.vm_big_number_from_hex("ff")
    assert nat.vm_big_number_to_hex(n) == "ff"


def test_to_int32_saturating_clamps():
    big = nat.vm_big_number_construct_from_decimal_str(
        "999999999999999999")
    # Saturates at INT32_MAX (2147483647).
    assert nat.vm_big_number_to_int32_saturating(big) == 2147483647


def test_copy_preserves_value():
    a = nat.vm_big_number_construct_from_value(12345)
    b = nat.vm_big_number_copy(a)
    assert nat.vm_big_number_to_string(b) == "12345"
