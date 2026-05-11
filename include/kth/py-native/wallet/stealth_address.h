// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_PY_NATIVE_WALLET_STEALTH_ADDRESS_H_
#define KTH_PY_NATIVE_WALLET_STEALTH_ADDRESS_H_

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#ifdef __cplusplus
extern "C" {
#endif

PyObject* kth_py_native_wallet_stealth_address_construct_default(PyObject* self, PyObject* args);
PyObject* kth_py_native_wallet_stealth_address_construct_from_decoded(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_stealth_address_construct_from_encoded(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_stealth_address_construct_from_binary_scan_key_spend_keys_signatures_version(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_stealth_address_copy(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_stealth_address_destruct(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_stealth_address_equals(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_stealth_address_less(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_stealth_address_valid(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_stealth_address_encoded(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_stealth_address_version(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_stealth_address_scan_key(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_stealth_address_spend_keys(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_stealth_address_signatures(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_stealth_address_filter(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_stealth_address_to_chunk(PyObject* self, PyObject* arg);

extern PyMethodDef kth_py_native_wallet_stealth_address_methods[];

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_PY_NATIVE_WALLET_STEALTH_ADDRESS_H_
