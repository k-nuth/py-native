// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_PY_NATIVE_CHAIN_GET_BLOCKS_H_
#define KTH_PY_NATIVE_CHAIN_GET_BLOCKS_H_

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#ifdef __cplusplus
extern "C" {
#endif

PyObject* kth_py_native_chain_get_blocks_construct_default(PyObject* self, PyObject* args);
PyObject* kth_py_native_chain_get_blocks_construct_from_data(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_get_blocks_construct(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_get_blocks_copy(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_get_blocks_destruct(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_get_blocks_equals(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_get_blocks_start_hashes(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_get_blocks_set_start_hashes(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_get_blocks_stop_hash(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_get_blocks_set_stop_hash(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_get_blocks_to_data(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_get_blocks_is_valid(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_get_blocks_reset(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_get_blocks_serialized_size(PyObject* self, PyObject* args, PyObject* kwds);

extern PyMethodDef kth_py_native_chain_get_blocks_methods[];

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_PY_NATIVE_CHAIN_GET_BLOCKS_H_
