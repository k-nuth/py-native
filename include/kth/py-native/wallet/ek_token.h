// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_PY_NATIVE_WALLET_EK_TOKEN_H_
#define KTH_PY_NATIVE_WALLET_EK_TOKEN_H_

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#ifdef __cplusplus
extern "C" {
#endif

PyObject* kth_py_native_wallet_ek_token_construct_default(PyObject* self, PyObject* args);
PyObject* kth_py_native_wallet_ek_token_construct_from_encoded(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_ek_token_construct_from_value(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_ek_token_copy(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_ek_token_destruct(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_ek_token_equals(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_ek_token_less(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_ek_token_valid(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_ek_token_encoded(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_ek_token_token(PyObject* self, PyObject* arg);

extern PyMethodDef kth_py_native_wallet_ek_token_methods[];

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_PY_NATIVE_WALLET_EK_TOKEN_H_
