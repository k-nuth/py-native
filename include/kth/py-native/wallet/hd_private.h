// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_PY_NATIVE_WALLET_HD_PRIVATE_H_
#define KTH_PY_NATIVE_WALLET_HD_PRIVATE_H_

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#ifdef __cplusplus
extern "C" {
#endif

PyObject* kth_py_native_wallet_hd_private_construct_default(PyObject* self, PyObject* args);
PyObject* kth_py_native_wallet_hd_private_construct_from_seed_prefixes(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_hd_private_construct_from_private_key(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_hd_private_construct_from_private_key_prefixes(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_hd_private_construct_from_private_key_prefix(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_hd_private_construct_from_encoded(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_hd_private_construct_from_encoded_prefixes(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_hd_private_construct_from_encoded_prefix(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_hd_private_copy(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_hd_private_destruct(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_hd_private_to_prefix(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_hd_private_less(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_hd_private_equals(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_hd_private_encoded(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_hd_private_secret(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_hd_private_to_hd_key(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_hd_private_to_public(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_hd_private_derive_private(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_hd_private_derive_public(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_hd_private_valid(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_hd_private_chain_code(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_hd_private_lineage(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_hd_private_point(PyObject* self, PyObject* arg);

extern PyMethodDef kth_py_native_wallet_hd_private_methods[];

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_PY_NATIVE_WALLET_HD_PRIVATE_H_
