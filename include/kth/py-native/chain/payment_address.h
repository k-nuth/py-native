#ifndef KTH_PY_NATIVE_CHAIN_PAYMENT_ADDRESS_H_
#define KTH_PY_NATIVE_CHAIN_PAYMENT_ADDRESS_H_

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#ifdef __cplusplus
extern "C" {
#endif

PyObject* kth_py_native_wallet_payment_address_destruct(PyObject* self, PyObject* args);
PyObject* kth_py_native_wallet_payment_address_encoded_legacy(PyObject* self, PyObject* args);
#if defined(KTH_CURRENCY_BCH)
PyObject* kth_py_native_wallet_payment_address_encoded_cashaddr(PyObject* self, PyObject* args);
PyObject* kth_py_native_wallet_payment_address_encoded_token(PyObject* self, PyObject* args);
#endif
PyObject* kth_py_native_wallet_payment_address_version(PyObject* self, PyObject* args);
PyObject* kth_py_native_wallet_payment_address_construct_from_string(PyObject* self, PyObject* args);

#ifdef __cplusplus
} //extern "C"
#endif

#endif
