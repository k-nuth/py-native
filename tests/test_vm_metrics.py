# Copyright (c) 2016-present Knuth Project developers.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

"""Tests for the vm_metrics binding.

`metrics` is the VM's script-execution accounting object: op-cost,
sig-check, and hash-digest-iteration tallies plus the limit
predicates. The invariants mirror the C-API tests
(`src/c-api/test/vm/metrics.cpp`) and the domain-level tests
(`src/domain/test/machine/metrics.cpp`).
"""

import kth_native as nat


TWO_PUSH_BYTES = bytes((0x51, 0x51))

# Reproduced from `script_limits.hpp` so the assertions below spell
# out the expected values.
HASH_ITER_FACTOR_CONSENSUS = 64      # non-standard
HASH_ITER_FACTOR_STANDARD = 192      # 64 * 3
SIG_CHECK_COST_FACTOR = 26_000       # may2025::sig_check_cost_factor

# Anchor for script_limits computations at n=100 scriptSig bytes:
#   op_cost_limit   = (n + 41) * 800         = 112'800
#   hash_iters_limit (non-std, factor 7) = 493
#   hash_iters_limit (standard,  factor 1) = 70
SCRIPT_SIG_SIZE = 100

# Script flag bit exposed in kth/0.82.0 capi (`kth_script_flags_bch_vm_limits_standard`).
# Mirrored here because the Python binding doesn't re-export flag
# constants — we just hand-roll the bit.
SCRIPT_FLAGS_BCH_VM_LIMITS_STANDARD = 1 << 57


def _fresh_metrics():
    # metrics has no explicit constructor binding. Obtain an owned
    # handle by copying the borrowed view from a default program —
    # matches the C-API fixture pattern.
    script = nat.chain_script_construct_from_data(TWO_PUSH_BYTES, False)
    program = nat.vm_program_construct_from_script(script)
    borrowed = nat.vm_program_get_metrics(program)
    owned = nat.vm_metrics_copy(borrowed)
    return owned


# ─── Default state ────────────────────────────────────────────────

def test_default_metrics_counters_are_zero():
    m = _fresh_metrics()
    assert nat.vm_metrics_sig_checks(m) == 0
    assert nat.vm_metrics_op_cost(m) == 0
    assert nat.vm_metrics_hash_digest_iterations(m) == 0
    assert nat.vm_metrics_has_valid_script_limits(m) is False


def test_without_script_limits_is_over_predicates_are_false():
    # Before `set_*_script_limits` is called, the limit predicates
    # must short-circuit on the absent `script_limits_`. Otherwise a
    # caller that forgot to initialise limits would silently
    # over-report limit violations based on an uninitialised ceiling.
    m = _fresh_metrics()
    nat.vm_metrics_add_op_cost(m, 1_000_000_000)
    nat.vm_metrics_add_hash_iterations(m, 1 << 20, True)
    assert nat.vm_metrics_is_over_op_cost_limit_simple(m) is False
    assert nat.vm_metrics_is_over_op_cost_limit(m, 0) is False
    assert nat.vm_metrics_is_over_hash_iters_limit(m) is False


# ─── Counter accumulation ─────────────────────────────────────────

def test_add_op_cost_accumulates():
    m = _fresh_metrics()
    nat.vm_metrics_add_op_cost(m, 10)
    nat.vm_metrics_add_op_cost(m, 20)
    nat.vm_metrics_add_op_cost(m, 100)
    assert nat.vm_metrics_op_cost(m) == 130


def test_add_push_op_is_alias_of_add_op_cost():
    # `add_push_op` is the BCHN-TallyPushOp-shaped alias. Must be
    # byte-for-byte equivalent to `add_op_cost`.
    via_push = _fresh_metrics()
    nat.vm_metrics_add_push_op(via_push, 5)
    nat.vm_metrics_add_push_op(via_push, 17)

    via_op_cost = _fresh_metrics()
    nat.vm_metrics_add_op_cost(via_op_cost, 5)
    nat.vm_metrics_add_op_cost(via_op_cost, 17)

    assert nat.vm_metrics_op_cost(via_push) == nat.vm_metrics_op_cost(via_op_cost) == 22


def test_add_sig_checks_accumulates():
    m = _fresh_metrics()
    nat.vm_metrics_add_sig_checks(m, 1)
    nat.vm_metrics_add_sig_checks(m, 1)
    nat.vm_metrics_add_sig_checks(m, 15)     # e.g. 15-key multisig
    assert nat.vm_metrics_sig_checks(m) == 17


# ─── Hash-iteration formula ───────────────────────────────────────

def test_add_hash_iterations_one_round_short_message():
    # iters = is_two_round + 1 + ((msg_len + 8) / 64)
    # msg_len = 0, one-round: 0 + 1 + 0 = 1
    m = _fresh_metrics()
    nat.vm_metrics_add_hash_iterations(m, 0, False)
    assert nat.vm_metrics_hash_digest_iterations(m) == 1


def test_add_hash_iterations_two_round_short_message():
    # msg_len = 0, two-round: 1 + 1 + 0 = 2
    m = _fresh_metrics()
    nat.vm_metrics_add_hash_iterations(m, 0, True)
    assert nat.vm_metrics_hash_digest_iterations(m) == 2


def test_add_hash_iterations_one_round_one_block():
    # msg_len = 56, one-round: 0 + 1 + ((56 + 8) / 64) = 2
    m = _fresh_metrics()
    nat.vm_metrics_add_hash_iterations(m, 56, False)
    assert nat.vm_metrics_hash_digest_iterations(m) == 2


def test_add_hash_iterations_accumulates_across_calls():
    m = _fresh_metrics()
    nat.vm_metrics_add_hash_iterations(m, 0, False)    # 1
    nat.vm_metrics_add_hash_iterations(m, 0, True)     # 2
    nat.vm_metrics_add_hash_iterations(m, 56, False)   # 2
    assert nat.vm_metrics_hash_digest_iterations(m) == 5


# ─── composite_op_cost ────────────────────────────────────────────

def test_composite_op_cost_on_zero_metrics_is_zero():
    m = _fresh_metrics()
    assert nat.vm_metrics_composite_op_cost_bool(m, False) == 0
    assert nat.vm_metrics_composite_op_cost_bool(m, True) == 0


def test_composite_op_cost_sig_checks_contribution():
    # 3 sig checks → 3 * 26'000 = 78'000. Standard/non-standard bit
    # is moot because hash_digest_iterations_ is 0.
    m = _fresh_metrics()
    nat.vm_metrics_add_sig_checks(m, 3)
    assert nat.vm_metrics_composite_op_cost_bool(m, False) == 3 * SIG_CHECK_COST_FACTOR
    assert nat.vm_metrics_composite_op_cost_bool(m, True) == 3 * SIG_CHECK_COST_FACTOR


def test_composite_op_cost_hash_iters_weighted_by_standard():
    m = _fresh_metrics()
    nat.vm_metrics_add_hash_iterations(m, 0, False)   # +1 iter
    assert nat.vm_metrics_composite_op_cost_bool(m, False) == HASH_ITER_FACTOR_CONSENSUS   # 64
    assert nat.vm_metrics_composite_op_cost_bool(m, True) == HASH_ITER_FACTOR_STANDARD     # 192


def test_composite_op_cost_composes_all_contributions():
    # 500 (op_cost) + 2 * 64 (two-round hash iters) + 1 * 26'000 (sig_checks)
    # = 500 + 128 + 26'000 = 26'628
    m = _fresh_metrics()
    nat.vm_metrics_add_op_cost(m, 500)
    nat.vm_metrics_add_hash_iterations(m, 0, True)    # +2
    nat.vm_metrics_add_sig_checks(m, 1)
    assert nat.vm_metrics_composite_op_cost_bool(m, False) == (
        500 + 2 * HASH_ITER_FACTOR_CONSENSUS + 1 * SIG_CHECK_COST_FACTOR
    )


def test_composite_op_cost_flags_routes_through_is_vm_limits_standard():
    # The flags-taking overload picks the 192x / 64x factor based on
    # whether `bch_vm_limits_standard` is present in the bitmask.
    m = _fresh_metrics()
    nat.vm_metrics_add_hash_iterations(m, 0, False)

    assert (
        nat.vm_metrics_composite_op_cost_script_flags(m, SCRIPT_FLAGS_BCH_VM_LIMITS_STANDARD)
        == nat.vm_metrics_composite_op_cost_bool(m, True)
    )
    assert (
        nat.vm_metrics_composite_op_cost_script_flags(m, 0)
        == nat.vm_metrics_composite_op_cost_bool(m, False)
    )


# ─── set_script_limits / set_native_script_limits ─────────────────

def test_set_script_limits_activates_has_valid_script_limits():
    m = _fresh_metrics()
    assert nat.vm_metrics_has_valid_script_limits(m) is False

    nat.vm_metrics_set_script_limits(m, 0, SCRIPT_SIG_SIZE)
    assert nat.vm_metrics_has_valid_script_limits(m) is True


def test_set_native_script_limits_picks_hash_iters_ceiling_from_standard():
    # hash_iters_limit = ((n + 41) * factor) / 2, with factor = 1 for
    # standard and factor = 7 for non-standard (consensus). At n=100:
    #   standard     → 70
    #   non-standard → 493
    # Pump the counter to 79 (msg_len=5000, one-round): crosses 70
    # but not 493 — proving `set_native_script_limits` persists the
    # 'standard' bit into the stored limits.
    consensus = _fresh_metrics()
    nat.vm_metrics_set_native_script_limits(consensus, False, SCRIPT_SIG_SIZE)

    standard = _fresh_metrics()
    nat.vm_metrics_set_native_script_limits(standard, True, SCRIPT_SIG_SIZE)

    nat.vm_metrics_add_hash_iterations(consensus, 5000, False)  # +79
    nat.vm_metrics_add_hash_iterations(standard, 5000, False)   # +79

    assert nat.vm_metrics_is_over_hash_iters_limit(consensus) is False
    assert nat.vm_metrics_is_over_hash_iters_limit(standard) is True


# ─── Limit crossings ──────────────────────────────────────────────

def test_is_over_op_cost_limit_crosses_when_composite_exceeds_ceiling():
    # op_cost_limit at n=100 is 112'800. With no iters and no sig
    # checks, composite_op_cost == op_cost_, so push op_cost right
    # below the ceiling, then cross it.
    m = _fresh_metrics()
    nat.vm_metrics_set_native_script_limits(m, False, SCRIPT_SIG_SIZE)
    nat.vm_metrics_add_op_cost(m, 112_800)
    assert nat.vm_metrics_is_over_op_cost_limit_simple(m) is False

    nat.vm_metrics_add_op_cost(m, 1)
    assert nat.vm_metrics_is_over_op_cost_limit_simple(m) is True


def test_is_over_hash_iters_limit_crosses_when_iters_exceed_ceiling():
    # hash_iters_limit at n=100 non-standard: 493.
    # msg_len = 30'000, one-round: 0 + 1 + (30'008 / 64) = 469.
    # Two calls → 938, crossing 493.
    m = _fresh_metrics()
    nat.vm_metrics_set_native_script_limits(m, False, SCRIPT_SIG_SIZE)
    nat.vm_metrics_add_hash_iterations(m, 30_000, False)   # +469
    assert nat.vm_metrics_is_over_hash_iters_limit(m) is False
    nat.vm_metrics_add_hash_iterations(m, 30_000, False)   # +469 → 938
    assert nat.vm_metrics_is_over_hash_iters_limit(m) is True


# ─── copy + borrowed view from program ────────────────────────────

def test_copy_is_independent_of_source():
    a = _fresh_metrics()
    nat.vm_metrics_add_op_cost(a, 500)

    b = nat.vm_metrics_copy(a)
    assert nat.vm_metrics_op_cost(b) == 500

    # Mutating the copy must not bleed back into the source.
    nat.vm_metrics_add_op_cost(b, 100)
    assert nat.vm_metrics_op_cost(a) == 500
    assert nat.vm_metrics_op_cost(b) == 600


def test_vm_program_get_metrics_returns_queryable_borrowed_view():
    # `vm_program_get_metrics` returns a borrowed capsule into the
    # program's internal metrics field. It must be queryable with
    # the same accessors as an owned metrics handle — the capsule
    # wrapper keeps `program` alive for the lifetime of the view.
    script = nat.chain_script_construct_from_data(TWO_PUSH_BYTES, False)
    program = nat.vm_program_construct_from_script(script)
    borrowed = nat.vm_program_get_metrics(program)
    assert borrowed is not None
    # Default program → all counters zero.
    assert nat.vm_metrics_sig_checks(borrowed) == 0
    assert nat.vm_metrics_op_cost(borrowed) == 0
    assert nat.vm_metrics_hash_digest_iterations(borrowed) == 0
