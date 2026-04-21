// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_PY_NATIVE_CHAIN_TRANSACTION_H_
#define KTH_PY_NATIVE_CHAIN_TRANSACTION_H_

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#ifdef __cplusplus
extern "C" {
#endif

PyObject* kth_py_native_chain_transaction_construct_default(PyObject* self, PyObject* args);
PyObject* kth_py_native_chain_transaction_construct_from_data(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_transaction_construct_from_version_locktime_inputs_outputs(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_transaction_construct_from_transaction_hash(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_transaction_copy(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_transaction_destruct(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_transaction_to_data(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_transaction_serialized_size(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_transaction_set_version(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_transaction_set_locktime(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_transaction_set_inputs(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_transaction_set_outputs(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_transaction_outputs_hash(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_transaction_inpoints_hash(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_transaction_sequences_hash(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_transaction_utxos_hash(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_transaction_hash(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_transaction_recompute_hash(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_transaction_fees(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_transaction_total_input_value(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_transaction_total_output_value(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_transaction_signature_operations_simple(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_transaction_is_overspent(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_transaction_check(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_transaction_accept(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_transaction_connect_simple(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_transaction_connect(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_transaction_connect_input(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_transaction_reset(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_transaction_equals(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_transaction_is_valid(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_transaction_version(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_transaction_locktime(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_transaction_inputs(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_transaction_outputs(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_transaction_previous_outputs(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_transaction_missing_previous_outputs(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_transaction_missing_previous_transactions(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_transaction_signature_operations(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_transaction_is_coinbase(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_transaction_is_null_non_coinbase(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_transaction_is_oversized_coinbase(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_transaction_is_mature(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_transaction_is_internal_double_spend(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_transaction_is_double_spend(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_transaction_is_dusty(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_transaction_is_missing_previous_outputs(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_transaction_is_final(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_transaction_is_locked(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_transaction_is_locktime_conflict(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_transaction_min_tx_size(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_transaction_is_standard_simple(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_transaction_is_standard(PyObject* self, PyObject* args, PyObject* kwds);

extern PyMethodDef kth_py_native_chain_transaction_methods[];

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_PY_NATIVE_CHAIN_TRANSACTION_H_
