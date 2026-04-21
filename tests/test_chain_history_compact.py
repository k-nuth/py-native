# Copyright (c) 2016-present Knuth Project developers.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

"""Tests for chain_history_compact + chain_history_compact_list bindings.

`history_compact` has no public constructor (neither on the C++ side
nor in the C-API / py-native surface) — instances only ever arrive
through the async `chain::fetch_history` callback path that materialises
a `history_compact_list`. That makes element-level unit tests
impractical without a running chain; we cover the list lifecycle and
smoke-check symbol presence for the element-side accessors so a
missing export is caught at import time.
"""

import kth_native as nat


def test_history_compact_list_default_construct_is_empty():
    lst = nat.chain_history_compact_list_construct_default()
    assert nat.chain_history_compact_list_count(lst) == 0
    nat.chain_history_compact_list_destruct(lst)


def test_history_compact_element_surface_is_exported():
    # Symbol-presence smoke: the accessors we'd call on an element
    # coming out of `fetch_history` must exist on the module. This
    # catches regressions where a regen silently drops a function.
    for name in (
        'chain_history_compact_destruct',
        'chain_history_compact_copy',
        'chain_history_compact_kind',
        'chain_history_compact_set_kind',
        'chain_history_compact_point',
        'chain_history_compact_set_point',
        'chain_history_compact_height',
        'chain_history_compact_set_height',
        'chain_history_compact_value_or_previous_checksum',
        'chain_history_compact_set_value_or_previous_checksum',
    ):
        assert hasattr(nat, name), f'missing export: {name}'
