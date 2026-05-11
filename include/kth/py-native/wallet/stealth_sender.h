// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_PY_NATIVE_WALLET_STEALTH_SENDER_H_
#define KTH_PY_NATIVE_WALLET_STEALTH_SENDER_H_

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#ifdef __cplusplus
extern "C" {
#endif

PyObject* kth_py_native_wallet_stealth_sender_construct_from_stealth_address_seed_binary_version(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_stealth_sender_construct_from_ephemeral_private_stealth_address_seed_binary_version(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_stealth_sender_copy(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_stealth_sender_destruct(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_stealth_sender_valid(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_stealth_sender_stealth_script(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_stealth_sender_payment_address(PyObject* self, PyObject* arg);

extern PyMethodDef kth_py_native_wallet_stealth_sender_methods[];

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_PY_NATIVE_WALLET_STEALTH_SENDER_H_
