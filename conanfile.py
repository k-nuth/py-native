import os
import shutil

from conan import ConanFile
from conan.tools.files import copy

# Read the build flavor from the env at module load. setup.py reads the
# same env to emit matching `KTH_CURRENCY_*` defines, so the conan dep
# graph and the C extension can never disagree.
_KTH_CURRENCY = os.environ.get("KTH_CURRENCY", "BCH")


class KnuthPyNative(ConanFile):
    name = "knuth-py-native"
    license = "MIT"
    url = "https://github.com/k-nuth/py-native"
    description = "Bitcoin/BCH full node Python bindings (CPython extension)"
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False]}
    # Note we use `default_options` rather than assigning into
    # `self.options[...]` from `configure()` — the latter creates a
    # final binding that wins over `-o kth/*:foo=bar` on the CLI,
    # which is the opposite of what we want for an overridable default.
    default_options = {
        "shared": False,
        "kth/*:shared": False,
        "kth/*:db": "dynamic",
        # We don't run upstream kth tests as part of py-native's build,
        # and the recipe's TSan test targets pull -ltsan which isn't
        # present in the manylinux containers we use in CI. Skipping
        # the whole test suite avoids the link error and shaves several
        # minutes off cold builds.
        "kth/*:tests": False,
        "kth/*:currency": _KTH_CURRENCY,
        # NOTE: march_id default is left to the recipe; override via env
        # KTH_MARCH_ID + setup.py, or pass `-o kth/*:march_id=...` on
        # the conan command line directly.
    }

    # Single unified Knuth package; previously this used the standalone
    # c-api/<ver>@kth/stable recipe, which no longer exists.
    def requirements(self):
        self.requires("kth/0.78.0", transitive_headers=True, transitive_libs=True)

    def generate(self):
        # Stage headers and static libs from kth AND all its transitive
        # dependencies (boost, gmp, lmdb, openssl, ...) into ./kth/ so
        # setup.py can pick them up with stable relative paths.
        #
        # Wipe the staging tree first so that bumping the Knuth version
        # (or flipping a build option) cannot leave orphaned `.a`/`.lib`
        # files or stale headers behind from a previous run.
        stage_root = f"{self.source_folder}/kth"
        if os.path.isdir(stage_root):
            shutil.rmtree(stage_root)

        inc_dst = f"{stage_root}/include"
        lib_dst = f"{stage_root}/lib"
        for _, dep in self.dependencies.host.items():
            for inc in dep.cpp_info.includedirs:
                copy(self, "*.h",   src=inc, dst=inc_dst)
                copy(self, "*.hpp", src=inc, dst=inc_dst)
            for libdir in dep.cpp_info.libdirs:
                for pat in ("*.a", "*.lib", "*.so", "*.so.*", "*.dylib", "*.dll"):
                    copy(self, pat, src=libdir, dst=lib_dst)
