// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_PY_NATIVE_CHAIN_POINT_H_
#define KTH_PY_NATIVE_CHAIN_POINT_H_

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#ifdef __cplusplus
extern "C" {
#endif

PyObject* kth_py_native_chain_point_construct_default(PyObject* self, PyObject* args);
PyObject* kth_py_native_chain_point_construct_from_data(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_point_construct(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_point_copy(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_point_destruct(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_point_equals(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_point_null(PyObject* self, PyObject* args);
PyObject* kth_py_native_chain_point_is_valid(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_point_to_data(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_point_satoshi_fixed_size(PyObject* self, PyObject* args);
PyObject* kth_py_native_chain_point_serialized_size(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_point_hash(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_point_set_hash(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_point_index(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_point_set_index(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_point_checksum(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_point_is_null(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_point_reset(PyObject* self, PyObject* arg);

extern PyMethodDef kth_py_native_chain_point_methods[];

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_PY_NATIVE_CHAIN_POINT_H_
