// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_PY_NATIVE_CHAIN_HEADER_H_
#define KTH_PY_NATIVE_CHAIN_HEADER_H_

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#ifdef __cplusplus
extern "C" {
#endif

PyObject* kth_py_native_chain_header_construct_default(PyObject* self, PyObject* args);
PyObject* kth_py_native_chain_header_construct_from_data(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_header_construct(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_header_copy(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_header_destruct(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_header_to_data(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_header_serialized_size(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_header_set_version(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_header_set_previous_block_hash(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_header_set_merkle(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_header_set_timestamp(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_header_set_bits(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_header_set_nonce(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_header_hash_pow(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_header_is_valid_proof_of_work(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_header_check(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_header_accept(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_header_reset(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_header_equals(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_header_is_valid(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_header_satoshi_fixed_size(PyObject* self, PyObject* args);
PyObject* kth_py_native_chain_header_version(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_header_previous_block_hash(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_header_merkle(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_header_timestamp(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_header_bits(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_header_nonce(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_header_is_valid_timestamp(PyObject* self, PyObject* arg);

extern PyMethodDef kth_py_native_chain_header_methods[];

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_PY_NATIVE_CHAIN_HEADER_H_
