# Copyright (c) 2016-present Knuth Project developers.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

"""Tests for the wallet_cashaddr namespace-module binding.

The namespace exposes two free functions: `encode` and `decode`.
`decode` returns a `(prefix, payload)` tuple via the Python backend's
`pair<string, data_chunk>` shape — added alongside the rest of the
0.83 sync.
"""

import pytest

import kth_native as nat


# Reference vector lifted from `src/c-api/test/wallet/cashaddr.cpp`
# — a known-good mainnet P2KH cashaddr + its decoded payload.
ADDR = "bitcoincash:qpm2qsznhks23z7629mms6s4cwef74vcwvy22gdx6a"
PREFIX = "bitcoincash"


def test_encode_round_trip_through_decode():
    decoded = nat.wallet_cashaddr_decode(ADDR, PREFIX)
    assert decoded is not None
    prefix, payload = decoded
    assert prefix == PREFIX
    assert isinstance(payload, bytes)
    assert len(payload) > 0

    re_encoded = nat.wallet_cashaddr_encode(prefix, payload)
    assert re_encoded == ADDR


def test_decode_uppercase_address():
    # CashAddr accepts all-uppercase as the same address.
    decoded = nat.wallet_cashaddr_decode(ADDR.upper(), PREFIX)
    assert decoded is not None
    prefix, payload = decoded
    assert prefix == PREFIX
    assert len(payload) > 0


def test_decode_invalid_returns_none():
    # A garbage string has no valid cashaddr decoding.
    assert nat.wallet_cashaddr_decode("not-an-address", PREFIX) is None


def test_decode_wrong_prefix_returns_none():
    # Same address, wrong expected prefix.
    assert nat.wallet_cashaddr_decode(ADDR, "bchtest") is None
