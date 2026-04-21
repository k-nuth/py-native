# Copyright (c) 2016-present Knuth Project developers.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

"""Tests for wallet_wallet_data bindings.

`wallet_data` is the in-memory representation of a Knuth wallet blob —
encrypted seed + mnemonics + xpub. The only public constructor is
`create(password, normalized_passphrase)`, which spins up a fresh
random wallet; the destructor and the simple getter / copy surface
are what we cover here.
"""

import pytest

import kth_native as nat


PASSWORD = 'correct horse battery staple'  # noqa: S105 - test fixture, not a real secret
# `normalized_passphrase` is the BIP-39 normalized passphrase — empty
# string is a common default when the user doesn't supply one.
PASSPHRASE = ''


@pytest.fixture
def wallet_data():
    """Yield a freshly-created `wallet_data` handle and guarantee the
    native handle is released even if an assertion mid-test raises.
    Lifecycle-sensitive tests benefit from deterministic cleanup so a
    leaked handle from one case doesn't perturb the next."""
    wd = nat.wallet_wallet_data_create(PASSWORD, PASSPHRASE)
    try:
        yield wd
    finally:
        nat.wallet_wallet_data_destruct(wd)


def test_create_produces_wallet_data_handle(wallet_data):
    assert wallet_data is not None


def test_encrypted_seed_is_non_empty_bytes(wallet_data):
    seed = nat.wallet_wallet_data_encrypted_seed(wallet_data)
    assert isinstance(seed, bytes)
    assert len(seed) > 0


def test_xpub_is_valid_hd_public(wallet_data):
    xpub = nat.wallet_wallet_data_xpub(wallet_data)
    assert xpub is not None
    assert nat.wallet_hd_public_valid(xpub) is True


def test_copy_preserves_encrypted_seed(wallet_data):
    dup = nat.wallet_wallet_data_copy(wallet_data)
    try:
        assert (
            nat.wallet_wallet_data_encrypted_seed(wallet_data)
            == nat.wallet_wallet_data_encrypted_seed(dup)
        )
    finally:
        nat.wallet_wallet_data_destruct(dup)


def test_mnemonics_accessor_is_callable(wallet_data):
    # `mnemonics` returns a capsule that wraps the string_list. We can't
    # iterate it without a string_list binding, but a successful call
    # (doesn't raise, returns non-None) means the cross-group capsule
    # reference resolved — one of the five generator bugs the 0.80.0
    # regen exposed.
    mn = nat.wallet_wallet_data_mnemonics(wallet_data)
    assert mn is not None
