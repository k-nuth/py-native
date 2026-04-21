// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_PY_NATIVE_CHAIN_PREFILLED_TRANSACTION_H_
#define KTH_PY_NATIVE_CHAIN_PREFILLED_TRANSACTION_H_

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#ifdef __cplusplus
extern "C" {
#endif

PyObject* kth_py_native_chain_prefilled_transaction_construct_default(PyObject* self, PyObject* args);
PyObject* kth_py_native_chain_prefilled_transaction_construct_from_data(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_prefilled_transaction_construct(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_prefilled_transaction_copy(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_prefilled_transaction_destruct(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_prefilled_transaction_equals(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_prefilled_transaction_index(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_prefilled_transaction_set_index(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_prefilled_transaction_transaction(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_prefilled_transaction_set_transaction(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_prefilled_transaction_to_data(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_prefilled_transaction_is_valid(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_prefilled_transaction_reset(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_prefilled_transaction_serialized_size(PyObject* self, PyObject* args, PyObject* kwds);

extern PyMethodDef kth_py_native_chain_prefilled_transaction_methods[];

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_PY_NATIVE_CHAIN_PREFILLED_TRANSACTION_H_
