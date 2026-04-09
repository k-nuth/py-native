// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_PY_NATIVE_CHAIN_BLOCK_H_
#define KTH_PY_NATIVE_CHAIN_BLOCK_H_

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#ifdef __cplusplus
extern "C" {
#endif

PyObject* kth_py_native_chain_block_construct_default(PyObject* self, PyObject* args);
PyObject* kth_py_native_chain_block_construct_from_data(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_block_construct(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_block_copy(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_block_destruct(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_block_to_data_simple(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_block_serialized_size(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_block_set_transactions(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_block_genesis_mainnet(PyObject* self, PyObject* args);
PyObject* kth_py_native_chain_block_genesis_testnet(PyObject* self, PyObject* args);
PyObject* kth_py_native_chain_block_genesis_regtest(PyObject* self, PyObject* args);
PyObject* kth_py_native_chain_block_genesis_testnet4(PyObject* self, PyObject* args);
PyObject* kth_py_native_chain_block_genesis_scalenet(PyObject* self, PyObject* args);
PyObject* kth_py_native_chain_block_genesis_chipnet(PyObject* self, PyObject* args);
PyObject* kth_py_native_chain_block_locator_size(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_block_locator_heights(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_block_signature_operations_simple(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_block_total_inputs(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_block_check(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_block_accept(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_block_connect(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_block_equals(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_block_is_valid(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_block_to_data(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_block_to_hashes(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_block_header(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_block_set_header(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_block_transactions(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_block_hash(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_block_subsidy(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_block_fees(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_block_claim(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_block_reward(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_block_generate_merkle_root(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_block_signature_operations(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_block_is_extra_coinbases(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_block_is_final(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_block_is_distinct_transaction_set(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_block_is_valid_coinbase_claim(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_block_is_valid_coinbase_script(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_block_is_forward_reference(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_block_is_canonical_ordered(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_block_is_internal_double_spend(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_block_is_valid_merkle_root(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_block_check_transactions(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_block_accept_transactions(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_block_connect_transactions(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_block_reset(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_block_non_coinbase_input_count(PyObject* self, PyObject* arg);

extern PyMethodDef kth_py_native_chain_block_methods[];

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_PY_NATIVE_CHAIN_BLOCK_H_
