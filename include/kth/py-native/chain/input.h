// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_PY_NATIVE_CHAIN_INPUT_H_
#define KTH_PY_NATIVE_CHAIN_INPUT_H_

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#ifdef __cplusplus
extern "C" {
#endif

PyObject* kth_py_native_chain_input_construct_default(PyObject* self, PyObject* args);
PyObject* kth_py_native_chain_input_construct_from_data(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_input_construct(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_input_copy(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_input_destruct(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_input_set_script(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_input_address(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_input_addresses(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_input_reset(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_input_equals(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_input_is_valid(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_input_to_data(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_input_serialized_size(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_input_previous_output(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_input_set_previous_output(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_input_script(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_input_sequence(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_input_set_sequence(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_input_is_final(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_input_is_locked(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_input_signature_operations(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_input_extract_embedded_script(PyObject* self, PyObject* arg);

extern PyMethodDef kth_py_native_chain_input_methods[];

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_PY_NATIVE_CHAIN_INPUT_H_
