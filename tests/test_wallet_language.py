# Copyright (c) 2016-present Knuth Project developers.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

"""Tests for the wallet_language namespace-module binding.

Each factory (`en`, `es`, `ja`, `it`, `fr`, `cs`, `ru`, `uk`,
`zh_Hans`, `zh_Hant`) returns an opaque-handle capsule wrapping
the static BIP39 wordlist. `all()` returns a list capsule of all
ten wordlists.
"""

import pytest

import kth_native as nat


LANGUAGE_FACTORIES = [
    nat.wallet_language_en,
    nat.wallet_language_es,
    nat.wallet_language_ja,
    nat.wallet_language_it,
    nat.wallet_language_fr,
    nat.wallet_language_cs,
    nat.wallet_language_ru,
    nat.wallet_language_uk,
    nat.wallet_language_zh_Hans,
    nat.wallet_language_zh_Hant,
]


@pytest.mark.parametrize("factory", LANGUAGE_FACTORIES)
def test_language_factory_returns_handle(factory):
    handle = factory()
    assert handle is not None


def test_all_returns_a_list_handle():
    lst = nat.wallet_language_all()
    assert lst is not None
