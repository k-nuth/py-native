# Copyright (c) 2016-present Knuth Project developers.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

"""Tests for chain_token_data bindings (CHIP-2022-02 Cashtokens).

`token_data` is the PMv2 variant: fungible-only, non-fungible, or
both. Instances are constructed through the three `make_*` factories
— no public default constructor. Covers each factory path + the
round-trip through `to_data` / `construct_from_data`.
"""

import kth_native as nat


ID_BYTES = bytes(range(32))

FUNGIBLE_AMOUNT = 1_000_000

# NFT capabilities: 0 = none (immutable), 1 = mutable, 2 = minting.
CAPABILITY_MUTABLE = 1

COMMITMENT = bytes([0xba, 0xad, 0xf0, 0x0d])


# ─── Factories ───────────────────────────────────────────────────────

def test_make_fungible_produces_valid_token_data():
    td = nat.chain_token_data_make_fungible(ID_BYTES, FUNGIBLE_AMOUNT)
    assert td is not None
    assert nat.chain_token_data_is_valid(td) is True
    assert nat.chain_token_data_get_amount(td) == FUNGIBLE_AMOUNT
    assert nat.chain_token_data_has_nft(td) is False
    assert nat.chain_token_data_is_fungible_only(td) is True


def test_make_non_fungible_sets_capability_and_commitment():
    td = nat.chain_token_data_make_non_fungible(
        ID_BYTES, CAPABILITY_MUTABLE, COMMITMENT,
    )
    assert td is not None
    assert nat.chain_token_data_is_valid(td) is True
    assert nat.chain_token_data_has_nft(td) is True
    assert nat.chain_token_data_get_nft_capability(td) == CAPABILITY_MUTABLE
    assert nat.chain_token_data_get_nft_commitment(td) == COMMITMENT
    assert nat.chain_token_data_is_mutable_nft(td) is True
    assert nat.chain_token_data_is_immutable_nft(td) is False


def test_make_both_sets_amount_and_nft():
    td = nat.chain_token_data_make_both(
        ID_BYTES, FUNGIBLE_AMOUNT, CAPABILITY_MUTABLE, COMMITMENT,
    )
    assert td is not None
    assert nat.chain_token_data_is_valid(td) is True
    assert nat.chain_token_data_get_amount(td) == FUNGIBLE_AMOUNT
    assert nat.chain_token_data_has_nft(td) is True
    assert nat.chain_token_data_get_nft_commitment(td) == COMMITMENT


def test_id_round_trip():
    td = nat.chain_token_data_make_fungible(ID_BYTES, FUNGIBLE_AMOUNT)
    assert nat.chain_token_data_id(td) == ID_BYTES


def test_copy_preserves_equality():
    td = nat.chain_token_data_make_fungible(ID_BYTES, FUNGIBLE_AMOUNT)
    dup = nat.chain_token_data_copy(td)
    assert nat.chain_token_data_equals(td, dup) is True


def test_equals_detects_amount_mismatch():
    a = nat.chain_token_data_make_fungible(ID_BYTES, FUNGIBLE_AMOUNT)
    b = nat.chain_token_data_make_fungible(ID_BYTES, FUNGIBLE_AMOUNT + 1)
    assert nat.chain_token_data_equals(a, b) is False


def test_to_data_and_from_data_round_trip():
    td = nat.chain_token_data_make_both(
        ID_BYTES, FUNGIBLE_AMOUNT, CAPABILITY_MUTABLE, COMMITMENT,
    )
    wire = nat.chain_token_data_to_data(td)
    assert len(wire) == nat.chain_token_data_serialized_size(td)
    restored = nat.chain_token_data_construct_from_data(wire)
    assert nat.chain_token_data_equals(td, restored) is True
