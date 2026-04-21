// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_PY_NATIVE_CHAIN_OPERATION_H_
#define KTH_PY_NATIVE_CHAIN_OPERATION_H_

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#ifdef __cplusplus
extern "C" {
#endif

PyObject* kth_py_native_chain_operation_construct_default(PyObject* self, PyObject* args);
PyObject* kth_py_native_chain_operation_construct_from_data(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_operation_construct_from_uncoded_minimal(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_operation_construct_from_code(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_operation_copy(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_operation_destruct(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_operation_equals(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_operation_from_string(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_operation_is_valid(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_operation_to_data(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_operation_to_string(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_operation_serialized_size(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_operation_code(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_operation_data(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_operation_opcode_from_size(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_operation_minimal_opcode_from_data(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_operation_nominal_opcode_from_data(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_operation_opcode_from_positive(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_operation_opcode_to_positive(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_operation_is_push(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_operation_is_payload(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_operation_is_counted(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_operation_is_version(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_operation_is_numeric(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_operation_is_positive(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_operation_is_reserved(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_operation_is_disabled(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_operation_is_conditional(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_operation_is_relaxed_push(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_operation_is_push_simple(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_operation_is_counted_simple(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_operation_is_version_simple(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_operation_is_positive_simple(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_operation_is_disabled_simple(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_operation_is_conditional_simple(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_operation_is_relaxed_push_simple(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_operation_is_oversized(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_operation_is_minimal_push(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_operation_is_nominal_push(PyObject* self, PyObject* arg);

extern PyMethodDef kth_py_native_chain_operation_methods[];

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_PY_NATIVE_CHAIN_OPERATION_H_
