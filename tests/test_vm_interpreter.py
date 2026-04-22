# Copyright (c) 2016-present Knuth Project developers.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

"""Tests for the vm_interpreter binding.

The `interpreter` surface is static-only (no constructor / destructor)
— it wraps the script VM's execution entry points: `run`, `run_simple`,
and the `debug_*` stepper family. Together with `vm_debug_snapshot`
these drive the rewind-friendly single-step debugger.
"""

import kth_native as nat


# `OP_1 OP_1` — two truthy pushes. After executing both ops the stack
# top is 1, so `debug_finalize` reports success.
TWO_PUSH_BYTES = bytes((0x51, 0x51))

# kth error-code value for `success`. We compare against a magic
# number instead of a named constant because the binding currently
# exposes error codes as plain ints.
KTH_EC_SUCCESS = 0


def _make_two_push_program():
    # `program` stores a POINTER to its backing `script`, so the
    # script capsule MUST outlive the program. Return both and let
    # the caller hold references — GC'ing just the script before
    # the program would leave the program's internal pointer
    # dangling and the next debug_* call would abort.
    script = nat.chain_script_construct_from_data(TWO_PUSH_BYTES, False)
    program = nat.vm_program_construct_from_script(script)
    return program, script


# ─── run / run_simple ─────────────────────────────────────────────

def test_run_simple_on_trivial_truthy_script_returns_success():
    prog, _script = _make_two_push_program()
    # `run_simple` returns the integer error code directly — 0 on
    # success, non-zero otherwise. Mirrors the C-API
    # `kth_vm_interpreter_run_simple` return shape.
    assert nat.vm_interpreter_run_simple(prog) == KTH_EC_SUCCESS


# ─── debug_begin / debug_step / debug_step_n ──────────────────────

def test_debug_begin_yields_fresh_snapshot_at_step_zero():
    prog, _script = _make_two_push_program()
    snap = nat.vm_interpreter_debug_begin(prog)
    assert snap is not None
    assert nat.vm_debug_snapshot_step(snap) == 0
    assert nat.vm_debug_snapshot_done(snap) is False


def test_debug_step_advances_one_op_at_a_time():
    # Two ops → two debug_steps move through the whole script, ending
    # in `done` after step 2.
    prog, _script = _make_two_push_program()
    s0 = nat.vm_interpreter_debug_begin(prog)
    s1 = nat.vm_interpreter_debug_step(s0)
    assert nat.vm_debug_snapshot_step(s1) == 1
    assert nat.vm_debug_snapshot_done(s1) is False

    s2 = nat.vm_interpreter_debug_step(s1)
    assert nat.vm_debug_snapshot_step(s2) == 2
    assert nat.vm_debug_snapshot_done(s2) is True


def test_debug_step_n_advances_by_n_or_stops_at_done():
    # Asking for more steps than the script has: the stepper clamps
    # at the end and reports `done`. Ported from the domain test
    # `debug_step_n advances by N (or stops at done)`.
    prog, _script = _make_two_push_program()
    s0 = nat.vm_interpreter_debug_begin(prog)
    s_many = nat.vm_interpreter_debug_step_n(s0, 10)
    assert nat.vm_debug_snapshot_done(s_many) is True


# ─── debug_run / debug_finalize ───────────────────────────────────

def test_debug_run_plus_finalize_reaches_success():
    prog, _script = _make_two_push_program()
    s0 = nat.vm_interpreter_debug_begin(prog)
    done = nat.vm_interpreter_debug_run(s0)
    assert nat.vm_debug_snapshot_done(done) is True
    assert nat.vm_interpreter_debug_finalize(done) == KTH_EC_SUCCESS


# ─── debug_run_traced ─────────────────────────────────────────────

def test_debug_run_traced_records_initial_plus_per_step_snapshots():
    # A 2-op script yields: the initial snapshot + one snapshot per
    # step = 3 entries. Ported from the domain test
    # `debug_run_traced yields one snapshot per step`.
    prog, _script = _make_two_push_program()
    start = nat.vm_interpreter_debug_begin(prog)
    trace = nat.vm_interpreter_debug_run_traced(start)
    assert trace is not None
    assert nat.vm_debug_snapshot_list_count(trace) == 3


# ─── Rewind semantics — inputs untouched by stepping ──────────────

def test_debug_step_preserves_input_snapshot():
    # `debug_step` returns a NEW snapshot; the input keeps its step
    # index. This is the contract that makes the debugger
    # rewind-friendly — the caller can fork execution off any prior
    # snapshot without having to rebuild it from scratch. Ported
    # from the domain test
    # `debug_step preserves the input snapshot (rewind-friendly)`.
    prog, _script = _make_two_push_program()
    start = nat.vm_interpreter_debug_begin(prog)
    advanced = nat.vm_interpreter_debug_step(start)
    assert nat.vm_debug_snapshot_step(start) == 0
    assert nat.vm_debug_snapshot_step(advanced) == 1
