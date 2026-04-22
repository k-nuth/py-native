#!/usr/bin/env python

# Copyright (c) 2016-present Knuth Project developers.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

import glob
import os
import subprocess
import sys

from setuptools import setup
from setuptools.extension import Extension
from setuptools.command.build_ext import build_ext
from setuptools.command.develop import develop
from setuptools.command.install import install
from distutils.command.build import build

HERE = os.path.dirname(os.path.abspath(__file__))
KTH_INCLUDE = os.path.join(HERE, 'kth', 'include')
KTH_LIB = os.path.join(HERE, 'kth', 'lib')


def run_conan_install(microarch=None, currency=None):
    """Stage Knuth headers + static libs into ./kth/ via Conan 2."""
    # CLI flags win over env, env wins over recipe defaults.
    microarch = microarch or os.environ.get('KTH_MARCH_ID')
    currency = currency or os.environ.get('KTH_CURRENCY')

    cmd = [
        'conan', 'install', '.',
        '--build=missing',
        '-s', 'build_type=Release',
        # kth/0.78.0 requires cppstd=23 (or higher). Conan's auto-detected
        # default profile picks gnu17 on most toolchains, so force it here.
        '-s', 'compiler.cppstd=23',
    ]
    if microarch:
        cmd += ['-o', f'kth/*:march_id={microarch}']
    if currency:
        cmd += ['-o', f'kth/*:currency={currency}']

    print('Running:', ' '.join(cmd))
    subprocess.check_call(cmd, cwd=HERE)


def discover_static_libs():
    """Return absolute paths to every static lib staged by conanfile.py."""
    if not os.path.isdir(KTH_LIB):
        return []
    libs = sorted(glob.glob(os.path.join(KTH_LIB, '*.a')))
    if sys.platform == 'win32':
        libs += sorted(glob.glob(os.path.join(KTH_LIB, '*.lib')))
    return libs


class _ConanMixin:
    user_options_extra = [
        ('microarch=', None, 'CPU microarchitecture (kth march_id)'),
        ('currency=', None, 'Cryptocurrency (BCH/BTC/LTC)'),
    ]

    def _init_extra(self):
        self.microarch = None
        self.currency = None

    def _do_conan(self):
        run_conan_install(self.microarch, self.currency)


class BuildCommand(_ConanMixin, build):
    user_options = build.user_options + _ConanMixin.user_options_extra

    def initialize_options(self):
        build.initialize_options(self)
        self._init_extra()

    def run(self):
        self._do_conan()
        build.run(self)


class InstallCommand(_ConanMixin, install):
    user_options = install.user_options + _ConanMixin.user_options_extra

    def initialize_options(self):
        install.initialize_options(self)
        self._init_extra()

    def run(self):
        self._do_conan()
        install.run(self)


class DevelopCommand(_ConanMixin, develop):
    user_options = develop.user_options + _ConanMixin.user_options_extra

    def initialize_options(self):
        develop.initialize_options(self)
        self._init_extra()

    def run(self):
        self._do_conan()
        develop.run(self)


class BuildExtCommand(build_ext):
    """Run `conan install` if libs aren't staged yet, then build the ext."""

    user_options = build_ext.user_options + _ConanMixin.user_options_extra

    def initialize_options(self):
        build_ext.initialize_options(self)
        self.microarch = None
        self.currency = None

    def build_extensions(self):
        # The extension mixes C (src/module.c — Python type tables that
        # don't trivially retrofit as C++) with C++ for the rest. The
        # Extension carries `-std=c++23` in extra_compile_args for the
        # whole project, which C compilers reject when handed a .c file.
        # Hook the underlying compiler to strip C++-only -std= flags
        # whenever the source ends in .c.
        original_compile = self.compiler._compile

        def filtered_compile(obj, src, ext, cc_args, extra_postargs, pp_opts):
            if src.endswith('.c'):
                extra_postargs = [
                    a for a in extra_postargs if not a.startswith('-std=c++')
                ]
            return original_compile(obj, src, ext, cc_args, extra_postargs, pp_opts)

        self.compiler._compile = filtered_compile
        super().build_extensions()

    def run(self):
        if not discover_static_libs():
            run_conan_install(self.microarch, self.currency)
        libs = discover_static_libs()
        if not libs:
            raise RuntimeError(
                f"No static libs found under {KTH_LIB}. "
                "Did `conan install` run successfully?"
            )
        # On GNU ld (Linux) we wrap the static libs in --start-group/
        # --end-group so the linker resolves circular dependencies between
        # kth/boost/etc. without caring about alphabetical order. macOS
        # ld64 doesn't support --start-group (and doesn't need it: it
        # always re-scans archives until no progress is made), and on
        # other platforms we just pass the libs raw.
        if sys.platform.startswith('linux'):
            link_libs = ['-Wl,--start-group', *libs, '-Wl,--end-group']
        else:
            link_libs = list(libs)
        for ext in self.extensions:
            ext.extra_link_args = (ext.extra_link_args or []) + link_libs
        build_ext.run(self)


_CURRENCY = os.environ.get('KTH_CURRENCY', 'BCH').upper()
if _CURRENCY not in ('BCH', 'BTC', 'LTC'):
    raise SystemExit(
        f"setup.py: unsupported KTH_CURRENCY={_CURRENCY!r} "
        "(expected one of: BCH, BTC, LTC)"
    )

extensions = [
    Extension(
        'kth_native',
        define_macros=[
            ('KTH_LIB_STATIC', None),
            ('KTH_DB_DYNAMIC', None),
            ('KTH_LOG_LIBRARY_SPDLOG', None),
            # Stays in lockstep with the currency option passed to
            # `conan install` (see conanfile.py::configure). Both
            # branches read KTH_CURRENCY from the env so they can't
            # disagree.
            (f'KTH_CURRENCY_{_CURRENCY}', None),
        ],
        sources=[
            'src/utils.cpp',
            'src/binary.cpp',
            # Auto-generated chain class wrappers (v2 generator).
            'src/chain/header.cpp',
            'src/chain/block.cpp',
            'src/chain/block_list.cpp',
            'src/chain/point.cpp',
            'src/chain/point_list.cpp',
            'src/chain/output_point.cpp',
            'src/chain/output_point_list.cpp',
            'src/chain/script.cpp',
            'src/chain/output.cpp',
            'src/chain/output_list.cpp',
            'src/chain/input.cpp',
            'src/chain/input_list.cpp',
            'src/chain/transaction.cpp',
            'src/chain/transaction_list.cpp',
            # Auto-generated (v2 generator) — chain extensions landed in the
            # 0.80.0 sync.
            'src/chain/compact_block.cpp',
            'src/chain/merkle_block.cpp',
            'src/chain/stealth_compact.cpp',
            'src/chain/stealth_compact_list.cpp',
            'src/chain/history_compact.cpp',
            'src/chain/history_compact_list.cpp',
            'src/chain/double_spend_proof.cpp',
            'src/chain/double_spend_proof_spender.cpp',
            'src/chain/get_blocks.cpp',
            'src/chain/get_headers.cpp',
            'src/chain/operation.cpp',
            'src/chain/operation_list.cpp',
            'src/chain/prefilled_transaction.cpp',
            'src/chain/prefilled_transaction_list.cpp',
            'src/chain/token_data.cpp',
            'src/chain/utxo.cpp',
            'src/chain/utxo_list.cpp',
            # Auto-generated (v2 generator) — wallet classes.
            'src/wallet/payment_address.cpp',
            'src/wallet/payment_address_list.cpp',
            'src/wallet/ec_private.cpp',
            'src/wallet/ec_public.cpp',
            'src/wallet/hd_private.cpp',
            'src/wallet/hd_public.cpp',
            'src/wallet/wallet_data.cpp',
            # Auto-generated (v2 generator) — VM classes.
            'src/vm/program.cpp',
            'src/vm/interpreter.cpp',
            'src/vm/debug_snapshot.cpp',
            'src/vm/debug_snapshot_list.cpp',
            # Hand-written async-callback bridge to safe_chain; not
            # generator-driven because the shape doesn't fit ClassConfig.
            'src/chain/chain.cpp',
            'src/node.cpp',
            'src/p2p/p2p.cpp',
            'src/config/database_settings.cpp',
            'src/config/node_settings.cpp',
            'src/module.c',
        ],
        include_dirs=[KTH_INCLUDE, 'include'],
        language='c++',
        # We require a toolchain new enough for C++23. Supported in:
        #   - GCC >= 13     (manylinux_2_34 ships GCC 14)
        #   - Apple Clang >= 16 (Xcode 16, default on macos-latest)
        # MSVC is not a supported target — Windows is intentionally
        # out of the build matrix; revisit when py-native gains a
        # Windows wheel job. The .c file in `sources` is filtered out
        # of this flag by BuildExtCommand.build_extensions() above.
        extra_compile_args=['-std=c++23'],
        extra_link_args=['-lstdc++'],
    ),
]

if sys.platform == 'darwin':
    extensions[0].extra_link_args = ['-stdlib=libc++', '-mmacosx-version-min=14']

# Almost all metadata lives in pyproject.toml (PEP 621). This setup.py
# only exists to declare the C extension and to drive the conan + custom
# build_ext path that staticly links the Knuth C-API into the .so.
setup(
    ext_modules=extensions,
    cmdclass={
        'build': BuildCommand,
        'install': InstallCommand,
        'develop': DevelopCommand,
        'build_ext': BuildExtCommand,
    },
)
