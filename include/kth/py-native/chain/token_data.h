// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_PY_NATIVE_CHAIN_TOKEN_DATA_H_
#define KTH_PY_NATIVE_CHAIN_TOKEN_DATA_H_

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#ifdef __cplusplus
extern "C" {
#endif

PyObject* kth_py_native_chain_token_data_construct_from_data(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_token_data_copy(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_token_data_destruct(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_token_data_id(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_token_data_set_id(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_token_data_equals(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_token_data_make_fungible(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_token_data_make_non_fungible(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_token_data_make_both(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_token_data_get_kind(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_token_data_is_valid(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_token_data_get_amount(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_token_data_has_nft(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_token_data_is_fungible_only(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_token_data_get_nft_capability(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_token_data_get_nft_commitment(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_token_data_is_immutable_nft(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_token_data_is_mutable_nft(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_token_data_is_minting_nft(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_token_data_serialized_size(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_token_data_bitfield(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_token_data_to_data(PyObject* self, PyObject* arg);

extern PyMethodDef kth_py_native_chain_token_data_methods[];

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_PY_NATIVE_CHAIN_TOKEN_DATA_H_
