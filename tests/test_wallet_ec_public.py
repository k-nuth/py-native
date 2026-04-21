# Copyright (c) 2016-present Knuth Project developers.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

"""Tests for wallet_ec_public bindings."""

import kth_native as nat


# BIP-0178-style vector: secp256k1 point with known base16 encoding.
# 33-byte compressed form of `0250863AD64A87AE8A2FE83C1AF1A8403CB53F53E486D8511DAD8A04887E5B2352`.
COMPRESSED_HEX = '0250863ad64a87ae8a2fe83c1af1a8403cb53f53e486d8511dad8a04887e5b2352'
COMPRESSED_POINT = bytes.fromhex(COMPRESSED_HEX)

P2KH_VERSION_MAINNET = 0x00


def test_default_construct_is_invalid():
    pub = nat.wallet_ec_public_construct_default()
    assert nat.wallet_ec_public_valid(pub) is False


def test_construct_from_base16_round_trips():
    pub = nat.wallet_ec_public_construct_from_base16(COMPRESSED_HEX)
    assert nat.wallet_ec_public_valid(pub) is True
    assert nat.wallet_ec_public_compressed(pub) is True
    assert nat.wallet_ec_public_encoded(pub) == COMPRESSED_HEX


def test_construct_from_compressed_point_preserves_bytes():
    pub = nat.wallet_ec_public_construct_from_compressed_point_compress(
        COMPRESSED_POINT, True,
    )
    assert nat.wallet_ec_public_valid(pub) is True
    assert nat.wallet_ec_public_point(pub) == COMPRESSED_POINT


def test_copy_self_equals():
    pub = nat.wallet_ec_public_construct_from_base16(COMPRESSED_HEX)
    dup = nat.wallet_ec_public_copy(pub)
    assert nat.wallet_ec_public_equals(pub, dup) is True


def test_to_uncompressed_is_65_bytes():
    pub = nat.wallet_ec_public_construct_from_base16(COMPRESSED_HEX)
    unc = nat.wallet_ec_public_to_uncompressed(pub)
    assert isinstance(unc, bytes)
    assert len(unc) == 65
    assert unc[0] == 0x04  # uncompressed sentinel


def test_to_payment_address_derives_p2kh():
    pub = nat.wallet_ec_public_construct_from_base16(COMPRESSED_HEX)
    addr = nat.wallet_ec_public_to_payment_address(pub, P2KH_VERSION_MAINNET)
    assert addr is not None
