# Copyright (c) 2016-present Knuth Project developers.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

"""Tests for wallet_ec_private bindings."""

import kth_native as nat


# Known secp256k1 secret (32 bytes, < curve order).
SECRET = bytes.fromhex(
    '18e14a7b6a307f426a94f8114701e7c8e774e7f9a47e2c2035db29a206321725'
)

WIF_VERSION_MAINNET = 0x80  # WIF version byte for Bitcoin mainnet.
P2KH_VERSION_MAINNET = 0x00
COMPRESSED = True


def test_default_construct_is_invalid():
    # Returns None because the default ctor reports invalid; the
    # regen's `leak_if_valid` translates that to a Python None.
    priv = nat.wallet_ec_private_construct_default()
    # If we got a handle, valid() must be false; if we got None, fine.
    if priv is not None:
        assert nat.wallet_ec_private_valid(priv) is False


def test_construct_from_secret_produces_valid_key():
    priv = nat.wallet_ec_private_construct_from_secret_version_compress(
        SECRET, WIF_VERSION_MAINNET, COMPRESSED,
    )
    assert priv is not None
    assert nat.wallet_ec_private_valid(priv) is True
    assert nat.wallet_ec_private_secret(priv) == SECRET


def test_copy_preserves_equality():
    priv = nat.wallet_ec_private_construct_from_secret_version_compress(
        SECRET, WIF_VERSION_MAINNET, COMPRESSED,
    )
    dup = nat.wallet_ec_private_copy(priv)
    assert nat.wallet_ec_private_equals(priv, dup) is True


def test_encoded_returns_non_empty_wif_string():
    priv = nat.wallet_ec_private_construct_from_secret_version_compress(
        SECRET, WIF_VERSION_MAINNET, COMPRESSED,
    )
    wif = nat.wallet_ec_private_encoded(priv)
    assert wif is not None
    assert isinstance(wif, str) and len(wif) > 0


def test_wif_round_trip_reconstructs_same_secret():
    priv = nat.wallet_ec_private_construct_from_secret_version_compress(
        SECRET, WIF_VERSION_MAINNET, COMPRESSED,
    )
    wif = nat.wallet_ec_private_encoded(priv)
    restored = nat.wallet_ec_private_construct_from_wif_version(wif, WIF_VERSION_MAINNET)
    assert restored is not None
    assert nat.wallet_ec_private_secret(restored) == SECRET
