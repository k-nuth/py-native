# Copyright (c) 2016-present Knuth Project developers.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

"""Tests for the borrowed-capsule parent-lifetime tie.

Accessors that return a view into a parent's internal storage
(`block.header()`, `block.transaction_nth(i)`, `*_list_nth(lst, i)`,
...) capsule-wrap a raw pointer into the parent's memory. Those
child capsules must keep the parent alive for as long as any child
view of it is reachable — otherwise dropping the parent while
still holding the child hands the caller a dangling pointer and
the next access is UB.

The generator wires this up through `PyCapsule_SetContext(child,
py_self)` plus `kth_py_native_borrowed_parent_dtor` (declared in
`utils.h`): the child holds a strong reference to the parent; on
GC the helper `Py_DECREF`s the parent so it can finally be
collected once every child view of it is gone.

These tests pin the contract so a future regen regression (e.g.
going back to a NULL capsule destructor or dropping the context)
fails visibly instead of turning every borrowed accessor into a
use-after-free.
"""

import gc
import sys

import pytest

import kth_native as nat


# ─── Fixtures ─────────────────────────────────────────────────────────────

VERSION = 10
TIMESTAMP = 531234
BITS = 6523454
NONCE = 68644

PREV_HASH = bytes(range(32))
MERKLE = bytes(32 - i for i in range(32))


def _make_header():
    return nat.chain_header_construct(
        VERSION, PREV_HASH, MERKLE, TIMESTAMP, BITS, NONCE,
    )


def _make_empty_block():
    hdr = _make_header()
    tx_list = nat.chain_transaction_list_construct_default()
    return nat.chain_block_construct(hdr, tx_list)


# ─── chain_block.header() — borrowed accessor ────────────────────────────

def test_borrowed_header_outlives_explicit_parent_deletion():
    """Grab a borrowed header from a block, drop the only Python ref to
    the block, force a GC cycle, then read through the header. The
    parent-lifetime tie keeps the block alive until the header itself
    is collected, so the read must succeed."""
    block = _make_empty_block()
    header = nat.chain_block_header(block)
    del block
    gc.collect()
    # If the parent were prematurely collected, this read would either
    # segfault the interpreter or return garbage. With the lifetime tie
    # in place the block stays alive.
    assert nat.chain_header_version(header) == VERSION
    assert nat.chain_header_timestamp(header) == TIMESTAMP
    assert nat.chain_header_previous_block_hash(header) == PREV_HASH


def test_borrowed_header_keeps_parent_block_refcount_elevated():
    """The child capsule holds a strong reference to the parent, so
    the parent's refcount is higher while any child view is live."""
    block = _make_empty_block()
    rc_before = sys.getrefcount(block)
    header = nat.chain_block_header(block)
    rc_with_child = sys.getrefcount(block)
    assert rc_with_child == rc_before + 1, (
        'borrowed-view capsule must INCREF the parent so the child can '
        f'outlive an explicit parent `del` (before={rc_before}, '
        f'after={rc_with_child})'
    )
    # Keep `header` reachable to prevent early GC from reordering the
    # reference count observation above.
    _ = nat.chain_header_version(header)


def test_borrowed_header_releases_parent_on_child_gc():
    """Once the child is collected, the parent reference it was
    holding must drop — the parent's refcount returns to baseline."""
    block = _make_empty_block()
    rc_before = sys.getrefcount(block)
    header = nat.chain_block_header(block)
    assert sys.getrefcount(block) == rc_before + 1
    del header
    gc.collect()
    assert sys.getrefcount(block) == rc_before, (
        'borrowed-child destructor must release the parent reference '
        'so the block refcount returns to its pre-accessor baseline'
    )


# ─── *_list_nth — borrowed element tied to the list ──────────────────────

def test_borrowed_list_element_outlives_list_deletion():
    """Element capsules from `*_list_nth` tie lifetime to the list.
    Dropping the list capsule while still holding the element must
    not invalidate the element."""
    lst = nat.chain_transaction_list_construct_default()
    tx = nat.chain_transaction_construct_default()
    nat.chain_transaction_list_push_back(lst, tx)
    borrowed = nat.chain_transaction_list_nth(lst, 0)
    del lst
    gc.collect()
    # Even though the list Python ref is gone, `borrowed` holds the
    # list alive via PyCapsule context, so this read is safe.
    _ = nat.chain_transaction_version(borrowed)


def test_borrowed_list_element_keeps_list_refcount_elevated():
    lst = nat.chain_transaction_list_construct_default()
    nat.chain_transaction_list_push_back(lst, nat.chain_transaction_construct_default())
    rc_before = sys.getrefcount(lst)
    borrowed = nat.chain_transaction_list_nth(lst, 0)
    rc_with_child = sys.getrefcount(lst)
    assert rc_with_child == rc_before + 1
    # Use `borrowed` so the optimiser / interpreter doesn't reorder
    # its lifetime across the refcount observation.
    _ = nat.chain_transaction_version(borrowed)


# ─── Robustness to many borrowed views off the same parent ───────────────

def test_multiple_borrowed_views_each_contribute_one_ref():
    """Fan out N borrowed views from one parent and verify each one
    contributes exactly +1 to the parent's refcount. Destroying them
    one by one returns the refcount monotonically to baseline."""
    block = _make_empty_block()
    baseline = sys.getrefcount(block)
    views = [nat.chain_block_header(block) for _ in range(5)]
    assert sys.getrefcount(block) == baseline + 5
    # Don't bind the loop variable — the loop-local would outlive the
    # loop and keep the last view (and therefore one parent ref) alive
    # even after `views[i] = None`.
    for i in range(len(views)):
        views[i] = None
        gc.collect()
    views.clear()
    gc.collect()
    assert sys.getrefcount(block) == baseline
