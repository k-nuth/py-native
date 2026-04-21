# Copyright (c) 2016-present Knuth Project developers.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

"""Tests for chain_operation + chain_operation_list bindings."""

import kth_native as nat


# ─── Fixtures ─────────────────────────────────────────────────────────

# Minimal push of 1 byte (0xaa). Script bytes: push_size=0x01, payload=0xaa.
PUSH_ONE_BYTE = bytes([0x01, 0xaa])

# OP_DUP opcode value (0x76). Used by is_push / is_counted static probes.
OPCODE_OP_DUP = 0x76


# ─── Operation — construction / lifecycle ────────────────────────────

def test_operation_default_is_invalid():
    op = nat.chain_operation_construct_default()
    assert nat.chain_operation_is_valid(op) is False
    nat.chain_operation_destruct(op)


def test_operation_construct_from_code_is_valid():
    op = nat.chain_operation_construct_from_code(OPCODE_OP_DUP)
    assert nat.chain_operation_is_valid(op) is True
    assert nat.chain_operation_code(op) == OPCODE_OP_DUP


def test_operation_from_data_round_trips_minimal_push():
    op = nat.chain_operation_construct_from_data(PUSH_ONE_BYTE)
    assert nat.chain_operation_is_valid(op) is True
    assert nat.chain_operation_data(op) == bytes([0xaa])
    assert nat.chain_operation_to_data(op) == PUSH_ONE_BYTE
    assert nat.chain_operation_serialized_size(op) == len(PUSH_ONE_BYTE)


def test_operation_copy_roundtrip_preserves_equality():
    a = nat.chain_operation_construct_from_code(OPCODE_OP_DUP)
    b = nat.chain_operation_copy(a)
    assert nat.chain_operation_equals(a, b) is True


def test_operation_equals_detects_mismatch():
    a = nat.chain_operation_construct_from_code(OPCODE_OP_DUP)
    b = nat.chain_operation_construct_from_code(OPCODE_OP_DUP + 1)
    assert nat.chain_operation_equals(a, b) is False


# ─── Static opcode probes ────────────────────────────────────────────

def test_operation_is_push_recognises_op_dup_as_non_push():
    # OP_DUP is counted, not a push opcode.
    assert nat.chain_operation_is_push(OPCODE_OP_DUP) is False
    assert nat.chain_operation_is_counted(OPCODE_OP_DUP) is True


def test_operation_opcode_from_positive_round_trip():
    # OP_1 (0x51) is `opcode_from_positive(1)`; the reverse maps back.
    code = nat.chain_operation_opcode_from_positive(1)
    assert nat.chain_operation_opcode_to_positive(code) == 1


# ─── OperationList ───────────────────────────────────────────────────

def test_operation_list_default_construct_is_empty():
    lst = nat.chain_operation_list_construct_default()
    assert nat.chain_operation_list_count(lst) == 0
    nat.chain_operation_list_destruct(lst)


def test_operation_list_push_back_and_nth():
    lst = nat.chain_operation_list_construct_default()
    op = nat.chain_operation_construct_from_code(OPCODE_OP_DUP)
    nat.chain_operation_list_push_back(lst, op)
    assert nat.chain_operation_list_count(lst) == 1
    got = nat.chain_operation_list_nth(lst, 0)
    assert nat.chain_operation_code(got) == OPCODE_OP_DUP
