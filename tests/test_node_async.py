# Copyright (c) 2016-present Knuth Project developers.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

"""Unit test for the callback → asyncio bridge.

The Knuth C-API exposes its async operations as functions that take a
trailing result callback (`callback(error, *result)`). This module
documents the canonical "wrap a callback as an awaitable" pattern that
downstream consumers like py-api should use, and unit-tests it against
synthetic callable shapes.

We can't drive the real node here: a single Python process can only
bootstrap one Knuth node — global logging/thread state from the first
`node_construct/destruct` cycle survives and trips the second one.
`tests/test_node.py` already covers the live-node path; this file
covers the async helper in isolation.

The helper itself originally lived in `old_tests/test_native_async_py`
(deleted in the same commit); the rest of that file was either
duplicated by `examples/settings.py` or by `tests/test_node.py`.
"""

from __future__ import annotations

import asyncio
import threading
from collections.abc import Callable
from typing import Any


# ──────────────────────────────────────────────────────────────────────
# The bridge — copy this verbatim into py-api when wrapping kth_native
# ──────────────────────────────────────────────────────────────────────


async def async_exec(
    func: Callable[..., Any],
    pick: int,
    *args: Any,
) -> Any:
    """Call a kth_native function whose last arg is a result callback,
    and return the `pick`-th positional argument the callback receives.

    The C-API hands results back through `callback(error, *result)`. We
    create a future, hop the callback's args back to the loop thread
    via `call_soon_threadsafe`, and await the future. `pick` selects
    which positional arg from the callback (0 = error, 1 = first
    payload, ...).
    """
    future: asyncio.Future[tuple[Any, ...]] = asyncio.Future()
    loop = asyncio.get_running_loop()

    def callback(*cb_args: Any) -> None:
        loop.call_soon_threadsafe(future.set_result, cb_args)

    func(*args, callback)
    cb_args = await future
    return cb_args[pick]


# ──────────────────────────────────────────────────────────────────────
# Tests
# ──────────────────────────────────────────────────────────────────────


def _fake_inline(value: int, callback: Callable[[int, int], None]) -> None:
    """Synthetic kth-style call that fires its callback synchronously
    on the calling thread, mimicking a fast-path C-API result."""
    callback(0, value * 2)


def _fake_threaded(value: int, callback: Callable[[int, int], None]) -> None:
    """Synthetic kth-style call that fires its callback from a worker
    thread, mimicking the I/O-async path the real C-API takes."""
    threading.Thread(target=callback, args=(0, value * 3), daemon=True).start()


def _fake_error(callback: Callable[[int, int], None]) -> None:
    """Synthetic kth-style call that returns a non-zero error code."""
    callback(42, 0)


def test_async_exec_inline_callback_returns_payload() -> None:
    """Sync callback fired before await: future should still resolve."""
    result = asyncio.run(async_exec(_fake_inline, 1, 21))
    assert result == 42


def test_async_exec_threaded_callback_returns_payload() -> None:
    """Callback fired from another thread: call_soon_threadsafe must
    bring the result back to the loop thread cleanly."""
    result = asyncio.run(async_exec(_fake_threaded, 1, 7))
    assert result == 21


def test_async_exec_pick_zero_returns_error_code() -> None:
    """`pick=0` selects the first arg of the callback, which by C-API
    convention is the error code."""
    err = asyncio.run(async_exec(_fake_error, 0))
    assert err == 42
