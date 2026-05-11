// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_PY_NATIVE_WALLET_STEALTH_RECEIVER_H_
#define KTH_PY_NATIVE_WALLET_STEALTH_RECEIVER_H_

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#ifdef __cplusplus
extern "C" {
#endif

PyObject* kth_py_native_wallet_stealth_receiver_construct(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_stealth_receiver_copy(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_stealth_receiver_destruct(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_stealth_receiver_valid(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_stealth_receiver_stealth_address(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_stealth_receiver_derive_address(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_stealth_receiver_derive_private(PyObject* self, PyObject* args, PyObject* kwds);

extern PyMethodDef kth_py_native_wallet_stealth_receiver_methods[];

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_PY_NATIVE_WALLET_STEALTH_RECEIVER_H_
