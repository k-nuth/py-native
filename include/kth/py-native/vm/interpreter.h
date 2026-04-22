// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_PY_NATIVE_VM_INTERPRETER_H_
#define KTH_PY_NATIVE_VM_INTERPRETER_H_

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#ifdef __cplusplus
extern "C" {
#endif

PyObject* kth_py_native_vm_interpreter_run_simple(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_interpreter_run(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_vm_interpreter_debug_begin(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_interpreter_debug_step(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_interpreter_debug_step_n(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_vm_interpreter_debug_run(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_interpreter_debug_run_traced(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_interpreter_debug_finalize(PyObject* self, PyObject* arg);

extern PyMethodDef kth_py_native_vm_interpreter_methods[];

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_PY_NATIVE_VM_INTERPRETER_H_
