// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_PY_NATIVE_CHAIN_MERKLE_BLOCK_H_
#define KTH_PY_NATIVE_CHAIN_MERKLE_BLOCK_H_

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#ifdef __cplusplus
extern "C" {
#endif

PyObject* kth_py_native_chain_merkle_block_construct_default(PyObject* self, PyObject* args);
PyObject* kth_py_native_chain_merkle_block_construct_from_data(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_merkle_block_construct_from_header_total_transactions_hashes_flags(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_merkle_block_construct_from_block(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_merkle_block_copy(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_merkle_block_destruct(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_merkle_block_equals(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_merkle_block_header(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_merkle_block_set_header(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_merkle_block_total_transactions(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_merkle_block_set_total_transactions(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_merkle_block_hashes(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_merkle_block_set_hashes(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_merkle_block_flags(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_merkle_block_set_flags(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_merkle_block_to_data(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_merkle_block_is_valid(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_merkle_block_reset(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_merkle_block_serialized_size(PyObject* self, PyObject* args, PyObject* kwds);

extern PyMethodDef kth_py_native_chain_merkle_block_methods[];

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_PY_NATIVE_CHAIN_MERKLE_BLOCK_H_
