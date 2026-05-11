// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_PY_NATIVE_VM_SCRIPT_EXECUTION_CONTEXT_H_
#define KTH_PY_NATIVE_VM_SCRIPT_EXECUTION_CONTEXT_H_

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#ifdef __cplusplus
extern "C" {
#endif

PyObject* kth_py_native_vm_script_execution_context_construct(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_vm_script_execution_context_copy(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_script_execution_context_destruct(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_script_execution_context_input_index(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_script_execution_context_transaction(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_script_execution_context_input_count(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_script_execution_context_output_count(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_script_execution_context_tx_version(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_script_execution_context_tx_locktime(PyObject* self, PyObject* arg);

extern PyMethodDef kth_py_native_vm_script_execution_context_methods[];

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_PY_NATIVE_VM_SCRIPT_EXECUTION_CONTEXT_H_
