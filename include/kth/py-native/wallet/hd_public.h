// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_PY_NATIVE_WALLET_HD_PUBLIC_H_
#define KTH_PY_NATIVE_WALLET_HD_PUBLIC_H_

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#ifdef __cplusplus
extern "C" {
#endif

PyObject* kth_py_native_wallet_hd_public_construct_default(PyObject* self, PyObject* args);
PyObject* kth_py_native_wallet_hd_public_construct_from_public_key(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_hd_public_construct_from_public_key_prefix(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_hd_public_construct_from_encoded(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_hd_public_construct_from_encoded_prefix(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_hd_public_copy(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_hd_public_destruct(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_hd_public_to_prefix(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_hd_public_less(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_hd_public_equals(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_hd_public_valid(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_hd_public_encoded(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_hd_public_chain_code(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_hd_public_lineage(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_hd_public_point(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_hd_public_to_hd_key(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_hd_public_derive_public(PyObject* self, PyObject* args, PyObject* kwds);

extern PyMethodDef kth_py_native_wallet_hd_public_methods[];

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_PY_NATIVE_WALLET_HD_PUBLIC_H_
