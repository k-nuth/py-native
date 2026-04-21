// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_PY_NATIVE_WALLET_EC_PUBLIC_H_
#define KTH_PY_NATIVE_WALLET_EC_PUBLIC_H_

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#ifdef __cplusplus
extern "C" {
#endif

PyObject* kth_py_native_wallet_ec_public_construct_default(PyObject* self, PyObject* args);
PyObject* kth_py_native_wallet_ec_public_construct_from_ec_private(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_ec_public_construct_from_decoded(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_ec_public_construct_from_base16(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_ec_public_construct_from_compressed_point_compress(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_ec_public_construct_from_uncompressed_point_compress(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_ec_public_copy(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_ec_public_destruct(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_ec_public_equals(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_ec_public_less(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_ec_public_valid(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_ec_public_encoded(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_ec_public_point(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_ec_public_compressed(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_ec_public_to_data(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_ec_public_to_uncompressed(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_ec_public_to_payment_address(PyObject* self, PyObject* args, PyObject* kwds);

extern PyMethodDef kth_py_native_wallet_ec_public_methods[];

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_PY_NATIVE_WALLET_EC_PUBLIC_H_
