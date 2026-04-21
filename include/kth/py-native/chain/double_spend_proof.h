// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_PY_NATIVE_CHAIN_DOUBLE_SPEND_PROOF_H_
#define KTH_PY_NATIVE_CHAIN_DOUBLE_SPEND_PROOF_H_

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#ifdef __cplusplus
extern "C" {
#endif

PyObject* kth_py_native_chain_double_spend_proof_construct_default(PyObject* self, PyObject* args);
PyObject* kth_py_native_chain_double_spend_proof_construct_from_data(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_double_spend_proof_construct(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_double_spend_proof_copy(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_double_spend_proof_destruct(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_double_spend_proof_equals(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_double_spend_proof_out_point(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_double_spend_proof_set_out_point(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_double_spend_proof_spender1(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_double_spend_proof_set_spender1(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_double_spend_proof_spender2(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_double_spend_proof_set_spender2(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_double_spend_proof_to_data(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_double_spend_proof_is_valid(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_double_spend_proof_reset(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_double_spend_proof_serialized_size(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_double_spend_proof_hash(PyObject* self, PyObject* arg);

extern PyMethodDef kth_py_native_chain_double_spend_proof_methods[];

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_PY_NATIVE_CHAIN_DOUBLE_SPEND_PROOF_H_
