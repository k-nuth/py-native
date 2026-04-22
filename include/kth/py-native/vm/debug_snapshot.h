// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_PY_NATIVE_VM_DEBUG_SNAPSHOT_H_
#define KTH_PY_NATIVE_VM_DEBUG_SNAPSHOT_H_

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#ifdef __cplusplus
extern "C" {
#endif

PyObject* kth_py_native_vm_debug_snapshot_construct_default(PyObject* self, PyObject* args);
PyObject* kth_py_native_vm_debug_snapshot_construct(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_debug_snapshot_copy(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_debug_snapshot_destruct(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_debug_snapshot_prog(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_debug_snapshot_step(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_debug_snapshot_last(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_debug_snapshot_done(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_debug_snapshot_control_stack(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_debug_snapshot_loop_stack(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_debug_snapshot_invoke_depth(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_debug_snapshot_outer_loop_depth(PyObject* self, PyObject* arg);

extern PyMethodDef kth_py_native_vm_debug_snapshot_methods[];

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_PY_NATIVE_VM_DEBUG_SNAPSHOT_H_
