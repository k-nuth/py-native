# Copyright (c) 2016-present Knuth Project developers.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

"""Tests for the wallet_bitcoin_uri binding (BIP21 URI parser / builder)."""

import pytest

import kth_native as nat


URI = "bitcoin:1NS17iag9jJgTHD1VXjvLCEnZuQ3rJDE9L?amount=0.0001&label=Foo"


def test_default_construct_is_invalid():
    uri = nat.wallet_bitcoin_uri_construct_default()
    assert nat.wallet_bitcoin_uri_valid(uri) is False


def test_construct_from_string_parses_amount_and_label():
    uri = nat.wallet_bitcoin_uri_construct(URI, True)
    assert nat.wallet_bitcoin_uri_valid(uri) is True
    # `amount` returns satoshis as an int — 0.0001 BTC = 10000 sat.
    assert nat.wallet_bitcoin_uri_amount(uri) == 10000
    assert nat.wallet_bitcoin_uri_label(uri) == "Foo"


def test_set_label_round_trips():
    uri = nat.wallet_bitcoin_uri_construct_default()
    nat.wallet_bitcoin_uri_set_label(uri, "Bar")
    assert nat.wallet_bitcoin_uri_label(uri) == "Bar"


def test_encoded_round_trip():
    a = nat.wallet_bitcoin_uri_construct(URI, True)
    b = nat.wallet_bitcoin_uri_construct(nat.wallet_bitcoin_uri_encoded(a), True)
    assert nat.wallet_bitcoin_uri_equals(a, b) is True


def test_invalid_uri_returns_invalid_handle():
    uri = nat.wallet_bitcoin_uri_construct("not-a-uri", True)
    assert nat.wallet_bitcoin_uri_valid(uri) is False
