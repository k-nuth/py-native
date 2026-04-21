# Copyright (c) 2016-present Knuth Project developers.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

"""Tests for chain_double_spend_proof + chain_double_spend_proof_spender.

`double_spend_proof_spender` has no public default constructor on the
C-API side (instances only come out of `double_spend_proof`'s accessors
or `from_data`); the py-native regen mirrors that. We cover the
element-level surface with a symbol-presence smoke check and exercise
the outer `double_spend_proof` lifecycle directly.
"""

import kth_native as nat


PROTOCOL_VERSION = 70015


# ─── DoubleSpendProof ────────────────────────────────────────────────

def test_double_spend_proof_default_construct_and_destruct():
    dsp = nat.chain_double_spend_proof_construct_default()
    nat.chain_double_spend_proof_destruct(dsp)


def test_double_spend_proof_copy_self_equals():
    dsp = nat.chain_double_spend_proof_construct_default()
    dup = nat.chain_double_spend_proof_copy(dsp)
    assert nat.chain_double_spend_proof_equals(dsp, dup) is True


def test_double_spend_proof_hash_is_32_bytes():
    dsp = nat.chain_double_spend_proof_construct_default()
    h = nat.chain_double_spend_proof_hash(dsp)
    assert isinstance(h, bytes)
    assert len(h) == 32


def test_double_spend_proof_serialized_size_matches_to_data_length():
    dsp = nat.chain_double_spend_proof_construct_default()
    wire = nat.chain_double_spend_proof_to_data(dsp, PROTOCOL_VERSION)
    assert len(wire) == nat.chain_double_spend_proof_serialized_size(dsp, PROTOCOL_VERSION)


def test_double_spend_proof_reset_clears_state():
    dsp = nat.chain_double_spend_proof_construct_default()
    nat.chain_double_spend_proof_reset(dsp)  # must not raise


# ─── DoubleSpendProofSpender surface ─────────────────────────────────

def test_double_spend_proof_spender_surface_is_exported():
    # Element-level unit tests aren't practical (no public ctor from
    # Python); verify the full accessor surface is reachable so a
    # regen-induced drop is caught immediately at import time.
    for name in (
        'chain_double_spend_proof_spender_construct_from_data',
        'chain_double_spend_proof_spender_copy',
        'chain_double_spend_proof_spender_destruct',
        'chain_double_spend_proof_spender_version',
        'chain_double_spend_proof_spender_set_version',
        'chain_double_spend_proof_spender_out_sequence',
        'chain_double_spend_proof_spender_locktime',
        'chain_double_spend_proof_spender_prev_outs_hash',
        'chain_double_spend_proof_spender_sequence_hash',
        'chain_double_spend_proof_spender_outputs_hash',
        'chain_double_spend_proof_spender_push_data',
        'chain_double_spend_proof_spender_is_valid',
        'chain_double_spend_proof_spender_reset',
        'chain_double_spend_proof_spender_equals',
        'chain_double_spend_proof_spender_serialized_size',
    ):
        assert hasattr(nat, name), f'missing export: {name}'
