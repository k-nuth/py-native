// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_PY_NATIVE_CHAIN_OUTPUT_POINT_H_
#define KTH_PY_NATIVE_CHAIN_OUTPUT_POINT_H_

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#ifdef __cplusplus
extern "C" {
#endif

PyObject* kth_py_native_chain_output_point_construct_default(PyObject* self, PyObject* args);
PyObject* kth_py_native_chain_output_point_construct_from_data(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_output_point_construct_from_hash_index(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_output_point_construct_from_point(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_output_point_copy(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_output_point_destruct(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_output_point_equals(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_output_point_is_mature(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_output_point_is_valid(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_output_point_to_data(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_output_point_satoshi_fixed_size(PyObject* self, PyObject* args);
PyObject* kth_py_native_chain_output_point_serialized_size(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_output_point_hash(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_output_point_set_hash(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_output_point_index(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_output_point_set_index(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_output_point_checksum(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_output_point_is_null(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_output_point_reset(PyObject* self, PyObject* arg);

extern PyMethodDef kth_py_native_chain_output_point_methods[];

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_PY_NATIVE_CHAIN_OUTPUT_POINT_H_
