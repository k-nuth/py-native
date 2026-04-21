// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_PY_NATIVE_CHAIN_STEALTH_COMPACT_H_
#define KTH_PY_NATIVE_CHAIN_STEALTH_COMPACT_H_

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#ifdef __cplusplus
extern "C" {
#endif

PyObject* kth_py_native_chain_stealth_compact_copy(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_stealth_compact_destruct(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_stealth_compact_ephemeral_public_key_hash(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_stealth_compact_set_ephemeral_public_key_hash(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_stealth_compact_public_key_hash(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_stealth_compact_set_public_key_hash(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_stealth_compact_transaction_hash(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_stealth_compact_set_transaction_hash(PyObject* self, PyObject* args, PyObject* kwds);

extern PyMethodDef kth_py_native_chain_stealth_compact_methods[];

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_PY_NATIVE_CHAIN_STEALTH_COMPACT_H_
