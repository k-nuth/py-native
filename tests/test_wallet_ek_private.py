# Copyright (c) 2016-present Knuth Project developers.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

"""Tests for the wallet_ek_private binding (BIP38 encrypted private key)."""

import pytest

import kth_native as nat


# Reference BIP38 encrypted private key from BIP38 spec test vectors —
# corresponds to the passphrase "TestingOneTwoThree" with no EC
# multiplication. 58 ASCII chars, base58 round-trip safe.
EK_ENCODED = "6PRVWUbkzzsbcVac2qwfssoUJAN1Xhrg6bNk8J7Nzm5H7kxEbn2Nh2ZoGg"


def test_default_construct_is_invalid():
    ek = nat.wallet_ek_private_construct_default()
    assert nat.wallet_ek_private_valid(ek) is False


def test_from_encoded_roundtrip():
    ek = nat.wallet_ek_private_construct_from_encoded(EK_ENCODED)
    assert nat.wallet_ek_private_valid(ek) is True
    assert nat.wallet_ek_private_encoded(ek) == EK_ENCODED


def test_copy_preserves_state():
    a = nat.wallet_ek_private_construct_from_encoded(EK_ENCODED)
    b = nat.wallet_ek_private_copy(a)
    assert nat.wallet_ek_private_equals(a, b) is True
    assert nat.wallet_ek_private_encoded(b) == EK_ENCODED


def test_invalid_encoded_returns_invalid_handle():
    ek = nat.wallet_ek_private_construct_from_encoded("not-a-bip38-key")
    assert nat.wallet_ek_private_valid(ek) is False
