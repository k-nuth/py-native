# Copyright (c) 2016-present Knuth Project developers.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

"""Tests for wallet_hd_private + wallet_hd_public bindings (BIP32)."""

import kth_native as nat


# BIP32 test vector 1 master seed (16 bytes).
SEED = bytes.fromhex('000102030405060708090a0b0c0d0e0f')

# 64-bit bundle of the xprv / xpub version bytes. Mainnet mainnet by
# default (0x0488ADE4 / 0x0488B21E packed). The C++ helper derives both
# halves from the single `prefixes` argument.
BIP32_MAINNET_PREFIXES = nat.wallet_hd_private_to_prefix(0x0488ADE4)


def test_hd_private_default_construct_is_invalid():
    priv = nat.wallet_hd_private_construct_default()
    assert nat.wallet_hd_private_valid(priv) is False


def test_hd_private_from_seed_produces_valid_master_key():
    priv = nat.wallet_hd_private_construct_from_seed_prefixes(
        SEED, BIP32_MAINNET_PREFIXES,
    )
    assert priv is not None
    assert nat.wallet_hd_private_valid(priv) is True
    assert len(nat.wallet_hd_private_secret(priv)) == 32
    assert len(nat.wallet_hd_private_chain_code(priv)) == 32


def test_hd_private_encoded_round_trips_through_from_encoded():
    priv = nat.wallet_hd_private_construct_from_seed_prefixes(
        SEED, BIP32_MAINNET_PREFIXES,
    )
    encoded = nat.wallet_hd_private_encoded(priv)
    assert encoded is not None
    restored = nat.wallet_hd_private_construct_from_encoded_prefixes(
        encoded, BIP32_MAINNET_PREFIXES,
    )
    assert restored is not None
    assert nat.wallet_hd_private_equals(priv, restored) is True


def test_hd_private_derive_private_produces_child():
    priv = nat.wallet_hd_private_construct_from_seed_prefixes(
        SEED, BIP32_MAINNET_PREFIXES,
    )
    child = nat.wallet_hd_private_derive_private(priv, 0)
    assert child is not None
    assert nat.wallet_hd_private_valid(child) is True
    # Child must have a different secret than its parent.
    assert nat.wallet_hd_private_secret(child) != nat.wallet_hd_private_secret(priv)


def test_hd_private_to_public_produces_matching_hd_public():
    priv = nat.wallet_hd_private_construct_from_seed_prefixes(
        SEED, BIP32_MAINNET_PREFIXES,
    )
    pub = nat.wallet_hd_private_to_public(priv)
    assert pub is not None
    assert nat.wallet_hd_public_valid(pub) is True
    # Chain codes must match across the private / public pair.
    assert (
        nat.wallet_hd_public_chain_code(pub)
        == nat.wallet_hd_private_chain_code(priv)
    )


# ─── HdPublic ────────────────────────────────────────────────────────

def test_hd_public_default_construct_is_invalid():
    pub = nat.wallet_hd_public_construct_default()
    assert nat.wallet_hd_public_valid(pub) is False


def test_hd_public_derive_public_produces_child():
    priv = nat.wallet_hd_private_construct_from_seed_prefixes(
        SEED, BIP32_MAINNET_PREFIXES,
    )
    pub = nat.wallet_hd_private_to_public(priv)
    child = nat.wallet_hd_public_derive_public(pub, 0)
    assert child is not None
    assert nat.wallet_hd_public_valid(child) is True


def test_hd_public_copy_preserves_equality():
    priv = nat.wallet_hd_private_construct_from_seed_prefixes(
        SEED, BIP32_MAINNET_PREFIXES,
    )
    pub = nat.wallet_hd_private_to_public(priv)
    dup = nat.wallet_hd_public_copy(pub)
    assert nat.wallet_hd_public_equals(pub, dup) is True
