// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_PY_NATIVE_CHAIN_GET_HEADERS_H_
#define KTH_PY_NATIVE_CHAIN_GET_HEADERS_H_

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#ifdef __cplusplus
extern "C" {
#endif

PyObject* kth_py_native_chain_get_headers_construct_default(PyObject* self, PyObject* args);
PyObject* kth_py_native_chain_get_headers_construct_from_data(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_get_headers_construct(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_get_headers_copy(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_get_headers_destruct(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_get_headers_equals(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_get_headers_start_hashes(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_get_headers_set_start_hashes(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_get_headers_stop_hash(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_get_headers_set_stop_hash(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_get_headers_to_data(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_get_headers_is_valid(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_get_headers_reset(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_get_headers_serialized_size(PyObject* self, PyObject* args, PyObject* kwds);

extern PyMethodDef kth_py_native_chain_get_headers_methods[];

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_PY_NATIVE_CHAIN_GET_HEADERS_H_
