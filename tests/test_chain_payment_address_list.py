# Copyright (c) 2016-present Knuth Project developers.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

"""Tests for chain_payment_address_list bindings.

The list is emitted under the `chain_` prefix (matches the C-API
`kth_chain_payment_address_list_*` surface) even though the element
class lives under `wallet_payment_address_*`; that asymmetry comes
from the `api_group` override on `PaymentAddressListConfig` and is
kept intentional so the list name matches the list handle type
(`kth_payment_address_list_*_t`) that other `chain_*` async callbacks
hand out.
"""

import kth_native as nat


# Known P2PKH cashaddr payload. The exact value doesn't matter; we
# just need a valid address to stash in the list.
LEGACY_ADDRESS = '1BvBMSEYstWetqTFn5Au4m4GFg7xJaNVN2'


def _make_address():
    # The generic factory is `wallet_payment_address_construct_from_address`.
    return nat.wallet_payment_address_construct_from_address(LEGACY_ADDRESS)


def test_payment_address_list_default_construct_is_empty():
    lst = nat.chain_payment_address_list_construct_default()
    assert nat.chain_payment_address_list_count(lst) == 0
    nat.chain_payment_address_list_destruct(lst)


def test_payment_address_list_push_back_and_nth():
    lst = nat.chain_payment_address_list_construct_default()
    addr = _make_address()
    nat.chain_payment_address_list_push_back(lst, addr)
    assert nat.chain_payment_address_list_count(lst) == 1
    got = nat.chain_payment_address_list_nth(lst, 0)
    assert got is not None
    # Round-trip the encoded legacy form through the nth-returned handle.
    assert nat.wallet_payment_address_encoded_legacy(got) == LEGACY_ADDRESS


def test_payment_address_list_erase_shrinks_count():
    lst = nat.chain_payment_address_list_construct_default()
    nat.chain_payment_address_list_push_back(lst, _make_address())
    nat.chain_payment_address_list_push_back(lst, _make_address())
    nat.chain_payment_address_list_erase(lst, 0)
    assert nat.chain_payment_address_list_count(lst) == 1
