// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_PY_NATIVE_CHAIN_DOUBLE_SPEND_PROOF_SPENDER_H_
#define KTH_PY_NATIVE_CHAIN_DOUBLE_SPEND_PROOF_SPENDER_H_

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#ifdef __cplusplus
extern "C" {
#endif

PyObject* kth_py_native_chain_double_spend_proof_spender_construct_from_data(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_double_spend_proof_spender_copy(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_double_spend_proof_spender_destruct(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_double_spend_proof_spender_version(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_double_spend_proof_spender_set_version(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_double_spend_proof_spender_out_sequence(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_double_spend_proof_spender_set_out_sequence(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_double_spend_proof_spender_locktime(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_double_spend_proof_spender_set_locktime(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_double_spend_proof_spender_prev_outs_hash(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_double_spend_proof_spender_set_prev_outs_hash(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_double_spend_proof_spender_sequence_hash(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_double_spend_proof_spender_set_sequence_hash(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_double_spend_proof_spender_outputs_hash(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_double_spend_proof_spender_set_outputs_hash(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_double_spend_proof_spender_push_data(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_double_spend_proof_spender_set_push_data(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_double_spend_proof_spender_is_valid(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_double_spend_proof_spender_reset(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_double_spend_proof_spender_equals(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_double_spend_proof_spender_serialized_size(PyObject* self, PyObject* arg);

extern PyMethodDef kth_py_native_chain_double_spend_proof_spender_methods[];

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_PY_NATIVE_CHAIN_DOUBLE_SPEND_PROOF_SPENDER_H_
