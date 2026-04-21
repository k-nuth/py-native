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

import kth_native as nat


PASSWORD = 'correct horse battery staple'
# `normalized_passphrase` is the BIP-39 normalized passphrase — empty
# string is a common default when the user doesn't supply one.
PASSPHRASE = ''


def test_create_produces_wallet_data_handle():
    wd = nat.wallet_wallet_data_create(PASSWORD, PASSPHRASE)
    assert wd is not None
    nat.wallet_wallet_data_destruct(wd)


def test_encrypted_seed_is_non_empty_bytes():
    wd = nat.wallet_wallet_data_create(PASSWORD, PASSPHRASE)
    seed = nat.wallet_wallet_data_encrypted_seed(wd)
    assert isinstance(seed, bytes)
    assert len(seed) > 0


def test_xpub_is_valid_hd_public():
    wd = nat.wallet_wallet_data_create(PASSWORD, PASSPHRASE)
    xpub = nat.wallet_wallet_data_xpub(wd)
    assert xpub is not None
    assert nat.wallet_hd_public_valid(xpub) is True


def test_copy_preserves_encrypted_seed():
    wd = nat.wallet_wallet_data_create(PASSWORD, PASSPHRASE)
    dup = nat.wallet_wallet_data_copy(wd)
    assert (
        nat.wallet_wallet_data_encrypted_seed(wd)
        == nat.wallet_wallet_data_encrypted_seed(dup)
    )


def test_mnemonics_accessor_is_callable():
    # `mnemonics` returns a capsule that wraps the string_list. We can't
    # iterate it without a string_list binding, but a successful call
    # (doesn't raise, returns non-None) means the cross-group capsule
    # reference resolved — one of the five generator bugs the 0.80.0
    # regen exposed.
    wd = nat.wallet_wallet_data_create(PASSWORD, PASSPHRASE)
    mn = nat.wallet_wallet_data_mnemonics(wd)
    assert mn is not None
