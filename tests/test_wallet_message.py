# Copyright (c) 2016-present Knuth Project developers.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

"""Tests for the wallet_message namespace-module binding (BIP137)."""

import pytest

import kth_native as nat


def test_hash_message_produces_32_bytes():
    h = nat.wallet_message_hash_message(b"hello world")
    assert isinstance(h, bytes)
    assert len(h) == 32


def test_hash_message_is_deterministic():
    a = nat.wallet_message_hash_message(b"the same input")
    b = nat.wallet_message_hash_message(b"the same input")
    assert a == b


def test_hash_message_distinguishes_inputs():
    a = nat.wallet_message_hash_message(b"x")
    b = nat.wallet_message_hash_message(b"y")
    assert a != b


# `recovery_id_to_magic` / `magic_to_recovery_id` are bindable but
# their out-pointer params are mis-modelled by the Python backend
# today (declared as scalar inputs rather than out-params); revisit
# once the generator gains an out-pointer scalar shape for the
# Python target.
