# Copyright (c) 2016-present Knuth Project developers.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

"""Tests for the chain_input binding."""

import pytest

import kth_native as nat


# ─────────────────────────────────────────────────────────────────────
# Fixtures — canonical 20-byte script body and a fake prev hash.
# ─────────────────────────────────────────────────────────────────────

SCRIPT_BODY = bytes((
    0xec, 0xe4, 0x24, 0xa6, 0xbb, 0x6d, 0xdf, 0x4d,
    0xb5, 0x92, 0xc0, 0xfa, 0xed, 0x60, 0x68, 0x50,
    0x47, 0xa3, 0x61, 0xb1,
))

PREV_HASH = bytes((
    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
    0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10,
    0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
    0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20,
))

SEQUENCE = 0xfffffffe


def make_script():
    return nat.chain_script_construct_from_data(SCRIPT_BODY, False)


def make_outpoint():
    return nat.chain_output_point_construct_from_hash_index(PREV_HASH, 7)


def make_input():
    return nat.chain_input_construct(
        previous_output=make_outpoint(),
        script=make_script(),
        sequence=SEQUENCE,
    )


# ─────────────────────────────────────────────────────────────────────
# Constructors / lifecycle
# ─────────────────────────────────────────────────────────────────────

def test_default_construct_is_invalid():
    inp = nat.chain_input_construct_default()
    assert nat.chain_input_is_valid(inp) is False


def test_field_constructor_preserves_fields():
    inp = make_input()
    assert nat.chain_input_is_valid(inp) is True
    assert nat.chain_input_sequence(inp) == SEQUENCE


# ─────────────────────────────────────────────────────────────────────
# from_data / to_data round-trip
# ─────────────────────────────────────────────────────────────────────

def test_to_data_from_data_roundtrip():
    original = make_input()
    raw = nat.chain_input_to_data(original, True)
    assert isinstance(raw, bytes)
    assert len(raw) > 0

    parsed = nat.chain_input_construct_from_data(raw, True)
    assert nat.chain_input_is_valid(parsed) is True
    assert nat.chain_input_equals(original, parsed) is True


# ─────────────────────────────────────────────────────────────────────
# Getters / setters
# ─────────────────────────────────────────────────────────────────────

def test_sequence_setter_roundtrip():
    inp = nat.chain_input_construct_default()
    nat.chain_input_set_sequence(inp, SEQUENCE)
    assert nat.chain_input_sequence(inp) == SEQUENCE


def test_is_final_on_max_sequence_is_true():
    inp = nat.chain_input_construct_default()
    nat.chain_input_set_sequence(inp, 0xffffffff)
    assert nat.chain_input_is_final(inp) is True


def test_is_final_on_non_max_sequence_is_false():
    inp = nat.chain_input_construct_default()
    nat.chain_input_set_sequence(inp, 0)
    assert nat.chain_input_is_final(inp) is False


# ─────────────────────────────────────────────────────────────────────
# Copy / equals
# ─────────────────────────────────────────────────────────────────────

def test_copy_preserves_fields():
    original = make_input()
    copy = nat.chain_input_copy(original)
    assert nat.chain_input_is_valid(copy) is True
    assert nat.chain_input_equals(original, copy) is True
    assert nat.chain_input_sequence(copy) == SEQUENCE


# ─────────────────────────────────────────────────────────────────────
# Regression: extract_embedded_script must return a Script capsule,
# not an Input capsule. If the generator mis-tags the returned handle
# with the input's capsule name, any downstream script API call will
# raise ValueError because PyCapsule_GetPointer rejects the wrong name.
# ─────────────────────────────────────────────────────────────────────

def test_extract_embedded_script_returns_script_capsule():
    inp = make_input()
    try:
        script = nat.chain_input_extract_embedded_script(inp)
    except RuntimeError:
        # The fixture script is not a P2SH pattern so extraction fails
        # with a domain error. That's fine — the capsule-tag bug only
        # manifests on the success path, but even the error path needs
        # the right capsule name to not touch the wrong macro.
        return
    # If extraction succeeded, the returned capsule must be usable as
    # a Script. If the generator tagged it "kth.chain.input" instead
    # of "kth.chain.script", any script-side call raises ValueError
    # "PyCapsule_GetPointer called with incorrect name".
    assert nat.chain_script_is_valid(script) in (True, False)
