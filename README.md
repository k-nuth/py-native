# kth-py-native

[![CI](https://github.com/k-nuth/py-native/actions/workflows/ci.yml/badge.svg)](https://github.com/k-nuth/py-native/actions/workflows/ci.yml)
[![PyPI](https://img.shields.io/pypi/v/kth-py-native.svg)](https://pypi.org/project/kth-py-native/)
[![Python](https://img.shields.io/pypi/pyversions/kth-py-native.svg)](https://pypi.org/project/kth-py-native/)

CPython bindings for the [Knuth](https://kth.cash) Bitcoin Cash node — a thin
1-to-1 layer over the Knuth C-API (`kth/c-api`) that exposes every C function
as a Python callable, plus typed Python objects (`Settings`, `BlockchainSettings`,
`DatabaseSettings`, `NetworkSettings`, ...) for the configuration structs.

> [!IMPORTANT]
> **You probably want [`kth-py-api`](https://github.com/k-nuth/py-api), not this
> package.** `py-native` is the low-level binding layer; `py-api` is the
> Pythonic, ergonomic API built on top. End users and application developers
> should depend on `py-api` and let it pull in `py-native` transitively. The
> only reasons to use `py-native` directly are: writing `py-api` itself,
> implementing a different high-level wrapper, or debugging the C-API.

## Highlights

- **Statically linked** against the Knuth C-API and all its transitive native
  deps (boost, secp256k1, lmdb, gmp, openssl, ...). One `.so`, no system libs
  to install.
- **Real BCH node embedded** — `node_construct` + `node_init_run_and_wait_for_signal`
  starts a full-fledged Knuth node from inside a Python process.
- **Type stubs** (`kth_native.pyi`) and a **PEP 561** `py.typed` marker so
  IDEs and type-checkers see real signatures, not opaque `Any`.
- **Modern build pipeline**: Conan 2, `cibuildwheel`, `setuptools-scm`,
  PEP 621 metadata in `pyproject.toml`, `mypy` + `ruff` configured.
- **Wheels published for**: Linux x86_64 (manylinux_2_34), macOS arm64
  (Apple Silicon, macOS 14+). Python 3.9 → 3.13. Windows and Intel macOS
  are tracked as follow-ups.

## Install

The easy path — let `py-api` pull this in:

```bash
pip install kth-py-api
```

Or directly, if you really want the raw bindings:

```bash
pip install kth-py-native
```

## Quick taste

```python
import kth_native as nat

# Default mainnet settings (db=normal, currency=BCH).
setts = nat.config_settings_default(0)
print(f"checkpoints: {len(setts.chain.checkpoints)}")
print(f"db_max_size: {setts.database.db_max_size:,}")

# Boot a real Knuth node from Python.
node = nat.node_construct(setts, True)
nat.node_init_run_and_wait_for_signal(
    node, 1, lambda err: print(f"node start: {err}")
)
chain = nat.node_chain(node)
nat.chain_fetch_last_height(chain, lambda err, h: print(f"height = {h}"))
nat.node_signal_stop(node)
nat.node_destruct(node)
```

The `examples/` directory has a few more (initchain, settings printer, tx
serialization, payment address roundtrip).

## Building from source

You need a modern toolchain capable of C++23 (GCC 13+, Apple Clang 16+) and
Conan 2.

```bash
python -m venv .venv
.venv/bin/pip install --upgrade pip setuptools wheel conan kthbuild

# Conan 2 default profile uses C++17; the kth recipe requires C++23.
# (`sed -i.bak` is the portable form that works on both GNU and BSD/macOS sed.)
conan profile detect --force
profile="$(conan profile path default)"
sed -i.bak 's/compiler.cppstd=.*/compiler.cppstd=23/' "$profile" && rm -f "$profile.bak"

.venv/bin/pip install --no-build-isolation -e .
.venv/bin/python -m pytest tests/ -v
```

`setup.py` shells out to `conan install` to stage the Knuth headers and static
libs into `./kth/` before building the extension. The `BuildExtCommand` in
`setup.py` then discovers every staged `.a` and links them into the resulting
`kth_native.so` (wrapped in `--start-group/--end-group` on Linux to handle the
boost ↔ kth ↔ libc circular references).

### Build flavor

Two env vars control the flavor — both are read by `conanfile.py` (which forwards
to Conan options) and `setup.py` (which emits matching `KTH_*` defines), so they
can never disagree:

| Env var          | Default        | Notes                                              |
| ---------------- | -------------- | -------------------------------------------------- |
| `KTH_CURRENCY`   | `BCH`          | One of `BCH`, `BTC`, `LTC`.                        |
| `KTH_MARCH_ID`   | recipe default | CPU microarch (e.g. `ZLm9Pjh` for x86-64-v3-ish).  |

## Versioning

Version comes from `git describe` via [`setuptools-scm`](https://setuptools-scm.readthedocs.io/).
The repo's latest `vX.Y.Z` tag is the source of truth — there is no `version.py`
to keep in sync. Untagged builds get a dev version like `0.10.1.dev3+gabcdef0`.

To cut a release, tag and push:

```bash
git tag v0.11.0
git push origin v0.11.0
```

The `Publish` job in CI then runs cibuildwheel, uploads the wheels + sdist
to PyPI via Trusted Publishing (OIDC, no tokens), and creates a GitHub Release
with the artifacts attached.

## Layout

```text
.
├── conanfile.py        # Conan 2 recipe — pins kth/0.78.0, stages deps into ./kth/
├── pyproject.toml      # PEP 621 metadata, setuptools-scm, mypy, ruff, pytest
├── setup.py            # C extension declaration + custom build_ext
├── kth_native.pyi      # Type stubs (typed classes + key functions)
├── py.typed            # PEP 561 marker
├── src/                # C / C++ source for the extension
│   ├── module.c        #   Module init + PyMethodDef table + PyTypeObject defs
│   ├── chain/          #   Wrappers for kth_chain_* (block/header/tx/...)
│   ├── config/         #   Settings struct ↔ Python class converters
│   ├── p2p/            #   p2p_* wrappers
│   └── node.cpp        #   node_construct / init_run / chain / destruct
├── include/kth/py-native/   # Headers for the wrappers above
├── tests/              # pytest suite — covers config defaults and node bootstrap
├── examples/           # Standalone scripts (don't run as tests)
└── .github/workflows/  # Single ci.yml (sdist + wheels + publish)
```

## Reference documentation

For broader Knuth project documentation, see [kth.cash](https://kth.cash).

## License

MIT — see [LICENSE](LICENSE).
