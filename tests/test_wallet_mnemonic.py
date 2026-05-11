# Copyright (c) 2016-present Knuth Project developers.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

"""Tests for the wallet_mnemonic namespace-module binding (BIP39)."""

import pytest

import kth_native as nat


# BIP39 spec vector: entropy "00000000000000000000000000000000"
# → "abandon abandon ... abandon about" (12 words).
ENTROPY_16 = bytes(16)  # all zeros
EXPECTED_12 = ("abandon " * 11 + "about").strip()


def test_create_mnemonic_with_english_wordlist():
    lexicon = nat.wallet_language_en()
    words = nat.wallet_mnemonic_create_mnemonic(ENTROPY_16, lexicon)
    assert words == EXPECTED_12


def test_validate_known_good_mnemonic_against_dictionary():
    lexicon = nat.wallet_language_en()
    assert nat.wallet_mnemonic_validate_mnemonic_dictionary(
        EXPECTED_12, lexicon) is True


def test_validate_garbage_mnemonic_returns_false():
    lexicon = nat.wallet_language_en()
    assert nat.wallet_mnemonic_validate_mnemonic_dictionary(
        "not really a mnemonic phrase here", lexicon) is False
