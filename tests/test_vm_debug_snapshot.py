# Copyright (c) 2016-present Knuth Project developers.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

"""Tests for the vm_debug_snapshot binding.

`debug_snapshot` is the per-step state the VM debugger exposes —
ip / step counter / last error / done flag / control stack /
loop stack / function table / invoke depth / outer loop depth.
The lifecycle and getter contract mirror the C-API
(`src/c-api/test/vm/debug_snapshot.cpp`); the rewind cases come
from the C++ domain test (`src/domain/test/machine/interpreter.cpp`).
"""

import kth_native as nat


TWO_PUSH_BYTES = bytes((0x51, 0x51))
KTH_EC_SUCCESS = 0


def _make_two_push_program():
    # `program` stores a POINTER to its backing `script`, so the
    # script capsule MUST outlive the program. Return both and let
    # the caller hold references.
    script = nat.chain_script_construct_from_data(TWO_PUSH_BYTES, False)
    program = nat.vm_program_construct_from_script(script)
    return program, script


# ─── Lifecycle ────────────────────────────────────────────────────

def test_default_construct_is_queryable():
    snap = nat.vm_debug_snapshot_construct_default()
    assert snap is not None
    assert nat.vm_debug_snapshot_step(snap) == 0
    assert nat.vm_debug_snapshot_done(snap) is False
    assert nat.vm_debug_snapshot_last(snap) == KTH_EC_SUCCESS
    assert nat.vm_debug_snapshot_invoke_depth(snap) == 0
    assert nat.vm_debug_snapshot_outer_loop_depth(snap) == 0


def test_construct_from_program_seats_on_script():
    prog, _script = _make_two_push_program()
    snap = nat.vm_debug_snapshot_construct(prog)
    assert snap is not None
    assert nat.vm_debug_snapshot_step(snap) == 0
    assert nat.vm_debug_snapshot_done(snap) is False
    # `prog` getter returns a borrowed view (non-None handle) —
    # the borrowed-capsule wrapper keeps the parent snapshot alive
    # for the duration of this local reference.
    assert nat.vm_debug_snapshot_prog(snap) is not None


def test_copy_preserves_step_after_advance():
    prog, _script = _make_two_push_program()
    s0 = nat.vm_interpreter_debug_begin(prog)
    s1 = nat.vm_interpreter_debug_step(s0)
    cp = nat.vm_debug_snapshot_copy(s1)
    # The copy reports the same step as the source. Subsequent
    # destruct of the copy must not disturb the source — this
    # exercises the deep-copy contract (mirrors the domain
    # interpreter tests that call `snap = step(std::move(snap))`
    # and then inspect the prior snapshot).
    assert nat.vm_debug_snapshot_step(cp) == 1
    nat.vm_debug_snapshot_destruct(cp)
    assert nat.vm_debug_snapshot_step(s1) == 1


# ─── Rewind semantics — stepping does not mutate the input ────────

def test_debug_step_preserves_input_snapshot():
    # Mirrors the domain-level test
    # `debug_step preserves the input snapshot (rewind-friendly)`:
    # the caller can keep any prior snapshot live and re-step from
    # it because stepping produces a new snapshot without mutating
    # the input.
    prog, _script = _make_two_push_program()
    start = nat.vm_interpreter_debug_begin(prog)
    advanced = nat.vm_interpreter_debug_step(start)
    assert nat.vm_debug_snapshot_step(start) == 0
    assert nat.vm_debug_snapshot_step(advanced) == 1


def test_debug_step_on_done_snapshot_is_noop():
    # Single-op script: after one step the snapshot is `done`.
    # Stepping a done snapshot produces another done snapshot with
    # the same step index — mirrors the domain test
    # `debug_step on a done snapshot is a no-op`.
    one_push = bytes((0x51,))
    script = nat.chain_script_construct_from_data(one_push, False)
    prog = nat.vm_program_construct_from_script(script)

    s0 = nat.vm_interpreter_debug_begin(prog)
    s1 = nat.vm_interpreter_debug_step(s0)
    assert nat.vm_debug_snapshot_done(s1) is True
    before_step = nat.vm_debug_snapshot_step(s1)

    s2 = nat.vm_interpreter_debug_step(s1)
    assert nat.vm_debug_snapshot_done(s2) is True
    assert nat.vm_debug_snapshot_step(s2) == before_step


# ─── Depth getters are queryable after stepping ───────────────────

def test_depth_getters_are_non_negative_after_step():
    # No OP_INVOKE / OP_BEGIN in the fixture script, so invoke_depth
    # and outer_loop_depth both stay at 0 throughout. We assert they
    # are reported as concrete integers — a smoke test that the
    # getters don't raise and the native size_t maps cleanly to a
    # Python int.
    prog, _script = _make_two_push_program()
    snap = nat.vm_interpreter_debug_begin(prog)
    snap = nat.vm_interpreter_debug_step(snap)
    assert nat.vm_debug_snapshot_invoke_depth(snap) == 0
    assert nat.vm_debug_snapshot_outer_loop_depth(snap) == 0
