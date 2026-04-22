# Copyright (c) 2016-present Knuth Project developers.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

"""Tests for the vm_program binding."""

import kth_native as nat


# Two-op script: `OP_1 OP_1` (bytes 0x51, 0x51). Mirrors the fixture
# used by the C-API vm test (src/c-api/test/vm/program.cpp) so the
# two layers exercise the same canonical script.
TWO_PUSH_BYTES = bytes((0x51, 0x51))


def _make_two_push_script():
    # `wire=False` → raw opcode bytes (no length prefix).
    return nat.chain_script_construct_from_data(TWO_PUSH_BYTES, False)


def test_default_construct_succeeds():
    # A default-constructed program is returned as a non-NULL
    # handle. Its exact `is_valid` / `operation_count` state is an
    # implementation detail (pre-execution) — we just anchor that
    # the constructor and the getter don't raise on a fresh handle.
    prog = nat.vm_program_construct_default()
    assert prog is not None
    # `is_valid` returns a bool without aborting.
    assert isinstance(nat.vm_program_is_valid(prog), bool)


def test_construct_from_script_succeeds():
    script = _make_two_push_script()
    prog = nat.vm_program_construct_from_script(script)
    assert prog is not None
    # Anchor that the program's getters are queryable post-ctor;
    # specific post-construction counters (`operation_count`) are
    # runtime state that the C-API initialises to zero — the
    # interpreter increments it as the script executes.
    assert nat.vm_program_operation_count(prog) == 0


def test_copy_produces_independent_handle():
    script = _make_two_push_script()
    prog = nat.vm_program_construct_from_script(script)
    dup = nat.vm_program_copy(prog)
    # The copy is a separate non-NULL handle with matching
    # runtime state — same input_index, same value, same
    # operation count (all zero for a fresh program).
    assert dup is not None
    assert nat.vm_program_input_index(dup) == nat.vm_program_input_index(prog)
    assert nat.vm_program_value(dup) == nat.vm_program_value(prog)
    assert nat.vm_program_operation_count(dup) == nat.vm_program_operation_count(prog)


def test_destruct_is_safe():
    prog = nat.vm_program_construct_default()
    nat.vm_program_destruct(prog)
    # No double-destruct on GC because the destructor retags the
    # capsule name; we're just asserting the explicit destruct does
    # not raise.


def test_getters_on_scripted_program():
    script = _make_two_push_script()
    prog = nat.vm_program_construct_from_script(script)
    # `input_index` and `value` default to 0 when the program was
    # built from a bare script (no transaction context).
    assert nat.vm_program_input_index(prog) == 0
    assert nat.vm_program_value(prog) == 0
    # `flags` is zero by default; the bit query returns an int.
    assert isinstance(nat.vm_program_flags(prog), int)


def test_limits_accessors_return_non_zero():
    # The program exposes the VM's active limits (max script element
    # size, max integer size, ...) — these are policy constants set
    # at construction and should be strictly positive for any
    # normally-configured program.
    script = _make_two_push_script()
    prog = nat.vm_program_construct_from_script(script)
    assert nat.vm_program_max_script_element_size(prog) > 0
    assert nat.vm_program_max_integer_size(prog) > 0
    assert nat.vm_program_max_integer_size_legacy(prog) > 0
