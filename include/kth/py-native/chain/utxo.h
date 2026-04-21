// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_PY_NATIVE_CHAIN_UTXO_H_
#define KTH_PY_NATIVE_CHAIN_UTXO_H_

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#ifdef __cplusplus
extern "C" {
#endif

PyObject* kth_py_native_chain_utxo_construct_default(PyObject* self, PyObject* args);
PyObject* kth_py_native_chain_utxo_copy(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_utxo_destruct(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_utxo_equals(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_utxo_height(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_utxo_point(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_utxo_amount(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_utxo_set_height(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_utxo_set_point(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_utxo_set_amount(PyObject* self, PyObject* args, PyObject* kwds);

extern PyMethodDef kth_py_native_chain_utxo_methods[];

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_PY_NATIVE_CHAIN_UTXO_H_
