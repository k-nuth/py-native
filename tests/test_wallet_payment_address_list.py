# Copyright (c) 2016-present Knuth Project developers.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

"""Tests for wallet_payment_address_list bindings.

Exposed under the `wallet_` prefix — matches the C-API
`kth_wallet_payment_address_list_*` surface, the capsule
`KTH_PY_CAPSULE_WALLET_PAYMENT_ADDRESS_LIST`, and the element
class which lives under `wallet_payment_address_*`. Earlier
revisions of the generator emitted this list under `chain_*`
because the list-method-table template hard-coded the prefix;
the fix flowed the namespace from `_ns_path(cfg)` so wallet-
scoped lists stay wallet-scoped end to end.
"""

import kth_native as nat


# Known P2PKH legacy (base58check) address. The exact value doesn't
# matter — we just need a valid encoded form to stash in the list.
LEGACY_ADDRESS = '1BvBMSEYstWetqTFn5Au4m4GFg7xJaNVN2'


def _make_address():
    # The generic factory is `wallet_payment_address_construct_from_address`.
    return nat.wallet_payment_address_construct_from_address(LEGACY_ADDRESS)


def test_payment_address_list_default_construct_is_empty():
    lst = nat.wallet_payment_address_list_construct_default()
    assert nat.wallet_payment_address_list_count(lst) == 0
    nat.wallet_payment_address_list_destruct(lst)


def test_payment_address_list_push_back_and_nth():
    lst = nat.wallet_payment_address_list_construct_default()
    addr = _make_address()
    nat.wallet_payment_address_list_push_back(lst, addr)
    assert nat.wallet_payment_address_list_count(lst) == 1
    got = nat.wallet_payment_address_list_nth(lst, 0)
    assert got is not None
    # Round-trip the encoded legacy form through the nth-returned handle.
    assert nat.wallet_payment_address_encoded_legacy(got) == LEGACY_ADDRESS


def test_payment_address_list_erase_shrinks_count():
    lst = nat.wallet_payment_address_list_construct_default()
    nat.wallet_payment_address_list_push_back(lst, _make_address())
    nat.wallet_payment_address_list_push_back(lst, _make_address())
    nat.wallet_payment_address_list_erase(lst, 0)
    assert nat.wallet_payment_address_list_count(lst) == 1
