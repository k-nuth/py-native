// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_PY_NATIVE_WALLET_MESSAGE_H_
#define KTH_PY_NATIVE_WALLET_MESSAGE_H_

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#ifdef __cplusplus
extern "C" {
#endif

PyObject* kth_py_native_wallet_message_hash_message(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_message_sign_message_ec_private(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_message_sign_message_string(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_message_sign_message_hash(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_message_verify_message(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_message_recovery_id_to_magic(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_message_magic_to_recovery_id(PyObject* self, PyObject* args, PyObject* kwds);

extern PyMethodDef kth_py_native_wallet_message_methods[];

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_PY_NATIVE_WALLET_MESSAGE_H_
