// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_PY_NATIVE_CHAIN_OUTPUT_H_
#define KTH_PY_NATIVE_CHAIN_OUTPUT_H_

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#ifdef __cplusplus
extern "C" {
#endif

PyObject* kth_py_native_chain_output_construct_default(PyObject* self, PyObject* args);
PyObject* kth_py_native_chain_output_construct_from_data(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_output_copy(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_output_destruct(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_output_to_data(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_output_serialized_size(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_output_set_script(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_output_address_simple(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_output_address(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_output_addresses(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_output_equals(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_output_is_valid(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_output_value(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_output_set_value(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_output_script(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_output_signature_operations(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_output_is_dust(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_output_reset(PyObject* self, PyObject* arg);

extern PyMethodDef kth_py_native_chain_output_methods[];

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_PY_NATIVE_CHAIN_OUTPUT_H_
