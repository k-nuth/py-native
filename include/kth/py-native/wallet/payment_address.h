// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_PY_NATIVE_WALLET_PAYMENT_ADDRESS_H_
#define KTH_PY_NATIVE_WALLET_PAYMENT_ADDRESS_H_

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#ifdef __cplusplus
extern "C" {
#endif

PyObject* kth_py_native_wallet_payment_address_construct_default(PyObject* self, PyObject* args);
PyObject* kth_py_native_wallet_payment_address_construct_from_decoded(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_payment_address_construct_from_ec_private(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_payment_address_construct_from_address(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_payment_address_construct_from_address_net(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_payment_address_construct_from_short_hash_version(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_payment_address_construct_from_hash_version(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_payment_address_construct_from_ec_public_version(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_payment_address_construct_from_script_version(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_payment_address_copy(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_payment_address_destruct(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_payment_address_cashaddr_prefix_for(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_payment_address_from_pay_public_key_hash_script(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_payment_address_equals(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_payment_address_less(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_payment_address_valid(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_payment_address_encoded_legacy(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_payment_address_encoded_cashaddr(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_payment_address_encoded_token(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_payment_address_version(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_payment_address_hash_span(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_payment_address_hash20(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_payment_address_hash32(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_payment_address_to_payment(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_payment_address_extract(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_payment_address_extract_input(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_payment_address_extract_output(PyObject* self, PyObject* args, PyObject* kwds);

extern PyMethodDef kth_py_native_wallet_payment_address_methods[];

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_PY_NATIVE_WALLET_PAYMENT_ADDRESS_H_
