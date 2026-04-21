// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_PY_NATIVE_WALLET_EC_PRIVATE_H_
#define KTH_PY_NATIVE_WALLET_EC_PRIVATE_H_

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#ifdef __cplusplus
extern "C" {
#endif

PyObject* kth_py_native_wallet_ec_private_construct_default(PyObject* self, PyObject* args);
PyObject* kth_py_native_wallet_ec_private_construct_from_wif_version(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_ec_private_construct_from_wif_compressed_version(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_ec_private_construct_from_wif_uncompressed_version(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_ec_private_construct_from_secret_version_compress(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_ec_private_copy(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_ec_private_destruct(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_ec_private_to_address_prefix(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_ec_private_to_wif_prefix(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_ec_private_to_version(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_ec_private_equals(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_ec_private_less(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_ec_private_valid(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_ec_private_encoded(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_ec_private_secret(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_ec_private_version(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_ec_private_payment_version(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_ec_private_wif_version(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_ec_private_compressed(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_ec_private_to_public(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_ec_private_to_payment_address(PyObject* self, PyObject* arg);

extern PyMethodDef kth_py_native_wallet_ec_private_methods[];

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_PY_NATIVE_WALLET_EC_PRIVATE_H_
