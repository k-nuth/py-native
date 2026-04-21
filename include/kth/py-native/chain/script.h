// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_PY_NATIVE_CHAIN_SCRIPT_H_
#define KTH_PY_NATIVE_CHAIN_SCRIPT_H_

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#ifdef __cplusplus
extern "C" {
#endif

PyObject* kth_py_native_chain_script_construct_default(PyObject* self, PyObject* args);
PyObject* kth_py_native_chain_script_construct_from_data(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_script_construct_from_operations(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_script_construct_from_encoded_prefix(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_script_copy(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_script_destruct(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_script_from_data_with_size(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_script_from_operations(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_script_from_string(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_script_is_valid_operations(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_script_to_string(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_script_clear(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_script_empty(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_script_size(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_script_front(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_script_back(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_script_at(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_script_operations(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_script_first_operation(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_script_create_endorsement(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_script_is_push_only(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_script_is_relaxed_push(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_script_is_coinbase_pattern(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_script_is_null_data_pattern(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_script_is_pay_multisig_pattern(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_script_is_pay_public_key_pattern(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_script_is_pay_public_key_hash_pattern(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_script_is_pay_script_hash_pattern(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_script_is_pay_script_hash_32_pattern(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_script_is_sign_multisig_pattern(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_script_is_sign_public_key_pattern(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_script_is_sign_public_key_hash_pattern(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_script_is_sign_script_hash_pattern(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_script_to_null_data_pattern(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_script_to_pay_public_key_pattern(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_script_to_pay_public_key_hash_pattern(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_script_to_pay_public_key_hash_pattern_unlocking(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_script_to_pay_public_key_hash_pattern_unlocking_placeholder(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_script_to_pay_script_hash_pattern_unlocking_placeholder(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_script_to_pay_script_hash_pattern(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_script_to_pay_script_hash_32_pattern(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_script_to_pay_multisig_pattern_ec_compressed_list(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_script_to_pay_multisig_pattern_data_stack(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_script_pattern(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_script_output_pattern_simple(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_script_output_pattern(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_script_input_pattern(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_script_sigops(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_script_is_unspendable(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_script_reset(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_script_is_pay_to_script_hash(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_script_is_pay_to_script_hash_32(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_script_verify(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_script_verify_simple(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_script_equals(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_script_is_valid(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_script_to_data(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_script_serialized_size(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_script_bytes(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_script_is_enabled(PyObject* self, PyObject* args, PyObject* kwds);

extern PyMethodDef kth_py_native_chain_script_methods[];

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_PY_NATIVE_CHAIN_SCRIPT_H_
