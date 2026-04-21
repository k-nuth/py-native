// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_PY_NATIVE_CHAIN_PREFILLED_TRANSACTION_LIST_H_
#define KTH_PY_NATIVE_CHAIN_PREFILLED_TRANSACTION_LIST_H_

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#ifdef __cplusplus
extern "C" {
#endif

PyObject* kth_py_native_chain_prefilled_transaction_list_construct_default(PyObject* self, PyObject* args);
PyObject* kth_py_native_chain_prefilled_transaction_list_push_back(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_prefilled_transaction_list_destruct(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_prefilled_transaction_list_count(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_prefilled_transaction_list_nth(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_prefilled_transaction_list_assign_at(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_prefilled_transaction_list_erase(PyObject* self, PyObject* args, PyObject* kwds);

extern PyMethodDef kth_py_native_chain_prefilled_transaction_list_methods[];

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_PY_NATIVE_CHAIN_PREFILLED_TRANSACTION_LIST_H_
