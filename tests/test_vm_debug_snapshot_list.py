# Copyright (c) 2016-present Knuth Project developers.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

"""Tests for the vm_debug_snapshot_list binding.

The list surface covers: default construct, push_back, count, nth,
assign_at, erase. `assign_at` is listed here as the documented
surface even though no test exercises it yet — the in-place
replacement it performs interacts with the broader borrowed-view
lifecycle work that several `nth()`-style accessors share, and
the test shape depends on the resolution of that work. The test
will land once that design decision is settled.

Lists are produced organically by `debug_run_traced` (one entry
per executed step) and are constructible directly via
`vm_debug_snapshot_list_construct_default` for round-trip tests.
"""

import kth_native as nat


TWO_PUSH_BYTES = bytes((0x51, 0x51))


def _make_two_push_program():
    # `program` stores a POINTER to its backing `script`, so the
    # script capsule MUST outlive the program. Return both and let
    # the caller hold a reference — GC'ing just the script before
    # the program would leave the program's internal pointer
    # dangling and the next debug_* call would abort.
    script = nat.chain_script_construct_from_data(TWO_PUSH_BYTES, False)
    program = nat.vm_program_construct_from_script(script)
    return program, script


def test_default_construct_is_empty():
    lst = nat.vm_debug_snapshot_list_construct_default()
    assert nat.vm_debug_snapshot_list_count(lst) == 0
    nat.vm_debug_snapshot_list_destruct(lst)


def test_push_back_and_count():
    lst = nat.vm_debug_snapshot_list_construct_default()
    snap = nat.vm_debug_snapshot_construct_default()
    nat.vm_debug_snapshot_list_push_back(lst, snap)
    assert nat.vm_debug_snapshot_list_count(lst) == 1


def test_nth_returns_snapshot_view():
    lst = nat.vm_debug_snapshot_list_construct_default()
    snap = nat.vm_debug_snapshot_construct_default()
    nat.vm_debug_snapshot_list_push_back(lst, snap)
    got = nat.vm_debug_snapshot_list_nth(lst, 0)
    assert got is not None
    # The default-constructed snapshot has step 0; the nth'd view
    # should report the same.
    assert nat.vm_debug_snapshot_step(got) == 0


def test_erase_shrinks_count():
    lst = nat.vm_debug_snapshot_list_construct_default()
    nat.vm_debug_snapshot_list_push_back(lst, nat.vm_debug_snapshot_construct_default())
    nat.vm_debug_snapshot_list_push_back(lst, nat.vm_debug_snapshot_construct_default())
    assert nat.vm_debug_snapshot_list_count(lst) == 2
    nat.vm_debug_snapshot_list_erase(lst, 0)
    assert nat.vm_debug_snapshot_list_count(lst) == 1


def test_debug_run_traced_list_count_matches_script():
    # A 2-op script → `debug_run_traced` yields 1 initial snapshot
    # + 2 per-step snapshots = 3 entries. Anchors the trace-list
    # count semantics end-to-end. Mirrors the C-API test's
    # `kth_vm_debug_snapshot_list_count(trace) == 3` assertion.
    prog, script = _make_two_push_program()
    start = nat.vm_interpreter_debug_begin(prog)
    trace = nat.vm_interpreter_debug_run_traced(start)
    assert nat.vm_debug_snapshot_list_count(trace) == 3
    # Touch `script` at the end of the test so Python's GC keeps it
    # alive until after `prog` is done with it. Without this the
    # script capsule could be collected mid-test and the program's
    # internal pointer to it would dangle.
    assert script is not None
