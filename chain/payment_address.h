#ifndef KTH_PY_NATIVE_CHAIN_PAYMENT_ADDRESS_H_
#define KTH_PY_NATIVE_CHAIN_PAYMENT_ADDRESS_H_

#include <Python.h>
#include <kth/capi.h>
#include "../utils.h"

#ifdef __cplusplus
extern "C" {
#endif

PyObject* kth_py_native_chain_payment_address_destruct(PyObject* self, PyObject* args);
PyObject* kth_py_native_chain_payment_address_encoded(PyObject* self, PyObject* args);
PyObject* kth_py_native_chain_payment_address_version(PyObject* self, PyObject* args);
PyObject* kth_py_native_chain_payment_address_construct_from_string(PyObject* self, PyObject* args);

#ifdef __cplusplus
} //extern "C"
#endif

#endif
