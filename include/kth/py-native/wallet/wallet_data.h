// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_PY_NATIVE_WALLET_WALLET_DATA_H_
#define KTH_PY_NATIVE_WALLET_WALLET_DATA_H_

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#ifdef __cplusplus
extern "C" {
#endif

PyObject* kth_py_native_wallet_wallet_data_copy(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_wallet_data_destruct(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_wallet_data_mnemonics(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_wallet_data_set_mnemonics(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_wallet_data_xpub(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_wallet_data_set_xpub(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_wallet_data_encrypted_seed(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_wallet_data_set_encrypted_seed(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_wallet_data_create(PyObject* self, PyObject* args, PyObject* kwds);

extern PyMethodDef kth_py_native_wallet_wallet_data_methods[];

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_PY_NATIVE_WALLET_WALLET_DATA_H_
