# Copyright (c) 2016-present Knuth Project developers.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

"""Tests for the chain_header binding.

These mirror the C-API test suite for the same class: same fixtures,
same coverage, same assertions. Anything that exists as a
KTH_PRECONDITION death test on the C side becomes a Python-level
exception test here, since Python catches malformed inputs at the
ValueError / TypeError boundary before they ever reach abort().

We do not bother with try/finally cleanup of header handles. The test
process exits in milliseconds and the OS reclaims any leaked memory;
adding finally blocks would just add noise and risk masking the
original assertion failure if the destruct itself raised.
"""

import time

import pytest

import kth_native as nat


# ─────────────────────────────────────────────────────────────────────
# Fixtures
# ─────────────────────────────────────────────────────────────────────

VERSION = 10
TIMESTAMP = 531234
BITS = 6523454
NONCE = 68644

PREV_HASH = bytes((
    0x6f, 0xe2, 0x8c, 0x0a, 0xb6, 0xf1, 0xb3, 0x72,
    0xc1, 0xa6, 0xa2, 0x46, 0xae, 0x63, 0xf7, 0x4f,
    0x93, 0x1e, 0x83, 0x65, 0xe1, 0x5a, 0x08, 0x9c,
    0x68, 0xd6, 0x19, 0x00, 0x00, 0x00, 0x00, 0x00,
))

MERKLE = bytes((
    0x3b, 0xa3, 0xed, 0xfd, 0x7a, 0x7b, 0x12, 0xb2,
    0x7a, 0xc7, 0x2c, 0x3e, 0x67, 0x76, 0x8f, 0x61,
    0x7f, 0xc8, 0x1b, 0xc3, 0x88, 0x8a, 0x51, 0x32,
    0x3a, 0x9f, 0xb8, 0xaa, 0x4b, 0x1e, 0x5e, 0x4a,
))

ZERO_HASH = bytes(32)


# ─────────────────────────────────────────────────────────────────────
# Constructors
# ─────────────────────────────────────────────────────────────────────

def test_default_construct_is_invalid():
    h = nat.chain_header_construct_default()
    assert nat.chain_header_is_valid(h) is False


def test_field_constructor_preserves_all_fields():
    h = nat.chain_header_construct(
        VERSION, PREV_HASH, MERKLE, TIMESTAMP, BITS, NONCE,
    )
    assert nat.chain_header_is_valid(h) is True
    assert nat.chain_header_version(h) == VERSION
    assert nat.chain_header_timestamp(h) == TIMESTAMP
    assert nat.chain_header_bits(h) == BITS
    assert nat.chain_header_nonce(h) == NONCE
    assert nat.chain_header_previous_block_hash(h) == PREV_HASH
    assert nat.chain_header_merkle(h) == MERKLE


def test_field_constructor_accepts_kwargs():
    """METH_VARARGS | METH_KEYWORDS lets users pass arguments by name."""
    h = nat.chain_header_construct(
        version=VERSION,
        previous_block_hash=PREV_HASH,
        merkle=MERKLE,
        timestamp=TIMESTAMP,
        bits=BITS,
        nonce=NONCE,
    )
    assert nat.chain_header_version(h) == VERSION
    assert nat.chain_header_nonce(h) == NONCE


# ─────────────────────────────────────────────────────────────────────
# from_data / to_data round-trip
# ─────────────────────────────────────────────────────────────────────

def test_from_data_insufficient_bytes_fails():
    with pytest.raises(RuntimeError):
        nat.chain_header_construct_from_data(b"\x00" * 10, True)


def test_to_data_from_data_roundtrip():
    expected = nat.chain_header_construct(
        VERSION, PREV_HASH, MERKLE, TIMESTAMP, BITS, NONCE,
    )
    raw = nat.chain_header_to_data(expected, True)
    assert isinstance(raw, bytes)
    assert len(raw) == 80

    parsed = nat.chain_header_construct_from_data(raw, True)
    assert nat.chain_header_is_valid(parsed) is True
    assert nat.chain_header_equals(expected, parsed) is True
    assert nat.chain_header_version(parsed) == VERSION
    assert nat.chain_header_timestamp(parsed) == TIMESTAMP


def test_from_data_empty_buffer_fails_gracefully():
    """`(b'', True)` is the Python analogue of `(NULL, 0)` on the C side:
    the C-API allows the empty input but the parser still has to fail —
    cleanly via the error code → exception path, never via abort()."""
    with pytest.raises(RuntimeError):
        nat.chain_header_construct_from_data(b"", True)


# ─────────────────────────────────────────────────────────────────────
# Getters / setters
# ─────────────────────────────────────────────────────────────────────

def test_version_setter_roundtrip():
    h = nat.chain_header_construct_default()
    assert nat.chain_header_version(h) != 4521
    nat.chain_header_set_version(h, 4521)
    assert nat.chain_header_version(h) == 4521


def test_previous_block_hash_setter_roundtrip():
    h = nat.chain_header_construct_default()
    assert nat.chain_header_previous_block_hash(h) == ZERO_HASH
    nat.chain_header_set_previous_block_hash(h, PREV_HASH)
    assert nat.chain_header_previous_block_hash(h) == PREV_HASH


def test_merkle_setter_roundtrip():
    h = nat.chain_header_construct_default()
    assert nat.chain_header_merkle(h) == ZERO_HASH
    nat.chain_header_set_merkle(h, MERKLE)
    assert nat.chain_header_merkle(h) == MERKLE


def test_timestamp_setter_roundtrip():
    h = nat.chain_header_construct_default()
    assert nat.chain_header_timestamp(h) != 4521
    nat.chain_header_set_timestamp(h, 4521)
    assert nat.chain_header_timestamp(h) == 4521


def test_bits_setter_roundtrip():
    h = nat.chain_header_construct_default()
    assert nat.chain_header_bits(h) != 4521
    nat.chain_header_set_bits(h, 4521)
    assert nat.chain_header_bits(h) == 4521


def test_nonce_setter_roundtrip():
    h = nat.chain_header_construct_default()
    assert nat.chain_header_nonce(h) != 4521
    nat.chain_header_set_nonce(h, 4521)
    assert nat.chain_header_nonce(h) == 4521


# ─────────────────────────────────────────────────────────────────────
# Predicates
# ─────────────────────────────────────────────────────────────────────

def test_is_valid_timestamp_now_is_true():
    h = nat.chain_header_construct_default()
    nat.chain_header_set_timestamp(h, int(time.time()))
    assert nat.chain_header_is_valid_timestamp(h) is True


def test_is_valid_timestamp_three_hours_in_future_is_false():
    h = nat.chain_header_construct_default()
    nat.chain_header_set_timestamp(h, int(time.time()) + 3 * 60 * 60)
    assert nat.chain_header_is_valid_timestamp(h) is False


def test_is_valid_proof_of_work_bits_exceed_max_is_false():
    """Any `bits` value above the proof-of-work limit must fail PoW."""
    h = nat.chain_header_construct_default()
    nat.chain_header_set_bits(h, 0xFFFFFFFF)
    assert nat.chain_header_is_valid_proof_of_work(h, True) is False


# ─────────────────────────────────────────────────────────────────────
# Copy / equals
# ─────────────────────────────────────────────────────────────────────

def test_copy_preserves_all_fields():
    original = nat.chain_header_construct(
        VERSION, PREV_HASH, MERKLE, TIMESTAMP, BITS, NONCE,
    )
    copy = nat.chain_header_copy(original)
    assert nat.chain_header_is_valid(copy) is True
    assert nat.chain_header_equals(original, copy) is True
    assert nat.chain_header_version(copy) == VERSION
    assert nat.chain_header_timestamp(copy) == TIMESTAMP
    assert nat.chain_header_bits(copy) == BITS
    assert nat.chain_header_nonce(copy) == NONCE


def test_equals_duplicates():
    a = nat.chain_header_construct(
        VERSION, PREV_HASH, MERKLE, TIMESTAMP, BITS, NONCE,
    )
    b = nat.chain_header_construct(
        VERSION, PREV_HASH, MERKLE, TIMESTAMP, BITS, NONCE,
    )
    c = nat.chain_header_construct_default()
    assert nat.chain_header_equals(a, b) is True
    assert nat.chain_header_equals(a, c) is False


# ─────────────────────────────────────────────────────────────────────
# Static utilities
# ─────────────────────────────────────────────────────────────────────

def test_satoshi_fixed_size_is_80():
    assert nat.chain_header_satoshi_fixed_size() == 80


# ─────────────────────────────────────────────────────────────────────
# Input validation (Python equivalents of the C-API death tests)
# ─────────────────────────────────────────────────────────────────────
#
# On the C side these become KTH_PRECONDITION → abort(), tested via fork.
# On the Python side, the wrapper catches malformed inputs at the
# PyCapsule / size-check boundary and raises a clean exception.

def test_set_previous_block_hash_wrong_size_raises():
    h = nat.chain_header_construct_default()
    with pytest.raises(ValueError, match="32-byte"):
        nat.chain_header_set_previous_block_hash(h, b"too short")


def test_set_merkle_wrong_size_raises():
    h = nat.chain_header_construct_default()
    with pytest.raises(ValueError, match="32-byte"):
        nat.chain_header_set_merkle(h, b"too short")


def test_construct_with_wrong_hash_size_raises():
    with pytest.raises(ValueError, match="32-byte"):
        nat.chain_header_construct(
            VERSION, b"too short", MERKLE, TIMESTAMP, BITS, NONCE,
        )


def test_passing_non_capsule_to_getter_raises():
    """A wrong-type capsule must produce a clean ValueError instead of
    segfaulting through PyCapsule_GetPointer with NULL name."""
    with pytest.raises((ValueError, TypeError)):
        # `chain_header_version` is a function, not a capsule. Calling
        # is_valid on it must reject the input via the capsule name check.
        nat.chain_header_is_valid(nat.chain_header_version)
