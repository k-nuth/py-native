// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_PY_NATIVE_WALLET_BITCOIN_URI_H_
#define KTH_PY_NATIVE_WALLET_BITCOIN_URI_H_

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#ifdef __cplusplus
extern "C" {
#endif

PyObject* kth_py_native_wallet_bitcoin_uri_construct_default(PyObject* self, PyObject* args);
PyObject* kth_py_native_wallet_bitcoin_uri_construct(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_bitcoin_uri_copy(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_bitcoin_uri_destruct(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_bitcoin_uri_equals(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_bitcoin_uri_less(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_bitcoin_uri_valid(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_bitcoin_uri_encoded(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_bitcoin_uri_amount(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_bitcoin_uri_label(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_bitcoin_uri_message(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_bitcoin_uri_r(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_bitcoin_uri_address(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_bitcoin_uri_payment(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_bitcoin_uri_stealth(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_bitcoin_uri_parameter(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_bitcoin_uri_set_amount(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_bitcoin_uri_set_label(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_bitcoin_uri_set_message(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_bitcoin_uri_set_r(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_bitcoin_uri_set_address_string(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_bitcoin_uri_set_address_payment_address(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_bitcoin_uri_set_address_stealth_address(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_bitcoin_uri_set_strict(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_bitcoin_uri_set_scheme(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_bitcoin_uri_set_authority(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_bitcoin_uri_set_path(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_bitcoin_uri_set_fragment(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_bitcoin_uri_set_parameter(PyObject* self, PyObject* args, PyObject* kwds);

extern PyMethodDef kth_py_native_wallet_bitcoin_uri_methods[];

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_PY_NATIVE_WALLET_BITCOIN_URI_H_
