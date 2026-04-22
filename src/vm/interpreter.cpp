// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/py-native/vm/interpreter.h>

#include <string.h>
#include <kth/capi.h>
#include <kth/capi/vm/interpreter.h>
#include <kth/py-native/capsule_names.h>
#include <kth/py-native/utils.h>

#ifdef __cplusplus
extern "C" {
#endif

PyObject*
kth_py_native_vm_interpreter_run_simple(PyObject* self, PyObject* py_arg0) {
    PyObject* py_program = py_arg0;
    kth_program_mut_t program_handle = (kth_program_mut_t)PyCapsule_GetPointer(py_program, KTH_PY_CAPSULE_VM_PROGRAM);
    if (program_handle == NULL) return NULL;
    auto const result = kth_vm_interpreter_run_simple(program_handle);
    return PyLong_FromLong((long)result);
}

PyObject*
kth_py_native_vm_interpreter_run(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"op", (char*)"program", NULL};
    PyObject* py_op = NULL;
    PyObject* py_program = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_op, &py_program)) {
        return NULL;
    }
    kth_operation_const_t op_handle = (kth_operation_const_t)PyCapsule_GetPointer(py_op, KTH_PY_CAPSULE_CHAIN_OPERATION);
    if (op_handle == NULL) return NULL;
    kth_program_mut_t program_handle = (kth_program_mut_t)PyCapsule_GetPointer(py_program, KTH_PY_CAPSULE_VM_PROGRAM);
    if (program_handle == NULL) return NULL;
    auto const result = kth_vm_interpreter_run(op_handle, program_handle);
    return PyLong_FromLong((long)result);
}

PyObject*
kth_py_native_vm_interpreter_debug_begin(PyObject* self, PyObject* py_arg0) {
    PyObject* py_prog = py_arg0;
    kth_program_const_t prog_handle = (kth_program_const_t)PyCapsule_GetPointer(py_prog, KTH_PY_CAPSULE_VM_PROGRAM);
    if (prog_handle == NULL) return NULL;
    auto const result = kth_vm_interpreter_debug_begin(prog_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_VM_DEBUG_SNAPSHOT, kth_py_native_vm_debug_snapshot_capsule_dtor);
    if (capsule == NULL) {
        kth_vm_debug_snapshot_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_vm_interpreter_debug_step(PyObject* self, PyObject* py_arg0) {
    PyObject* py_snapshot = py_arg0;
    kth_debug_snapshot_const_t snapshot_handle = (kth_debug_snapshot_const_t)PyCapsule_GetPointer(py_snapshot, KTH_PY_CAPSULE_VM_DEBUG_SNAPSHOT);
    if (snapshot_handle == NULL) return NULL;
    auto const result = kth_vm_interpreter_debug_step(snapshot_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_VM_DEBUG_SNAPSHOT, kth_py_native_vm_debug_snapshot_capsule_dtor);
    if (capsule == NULL) {
        kth_vm_debug_snapshot_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_vm_interpreter_debug_step_n(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"snapshot", (char*)"n", NULL};
    PyObject* py_snapshot = NULL;
    Py_ssize_t n = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "On", kwlist, &py_snapshot, &n)) {
        return NULL;
    }
    kth_debug_snapshot_const_t snapshot_handle = (kth_debug_snapshot_const_t)PyCapsule_GetPointer(py_snapshot, KTH_PY_CAPSULE_VM_DEBUG_SNAPSHOT);
    if (snapshot_handle == NULL) return NULL;
    if (n < 0) {
        PyErr_Format(PyExc_ValueError, "n must be non-negative, got %zd", n);
        return NULL;
    }
    auto const result = kth_vm_interpreter_debug_step_n(snapshot_handle, (kth_size_t)n);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_VM_DEBUG_SNAPSHOT, kth_py_native_vm_debug_snapshot_capsule_dtor);
    if (capsule == NULL) {
        kth_vm_debug_snapshot_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_vm_interpreter_debug_run(PyObject* self, PyObject* py_arg0) {
    PyObject* py_snapshot = py_arg0;
    kth_debug_snapshot_const_t snapshot_handle = (kth_debug_snapshot_const_t)PyCapsule_GetPointer(py_snapshot, KTH_PY_CAPSULE_VM_DEBUG_SNAPSHOT);
    if (snapshot_handle == NULL) return NULL;
    auto const result = kth_vm_interpreter_debug_run(snapshot_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_VM_DEBUG_SNAPSHOT, kth_py_native_vm_debug_snapshot_capsule_dtor);
    if (capsule == NULL) {
        kth_vm_debug_snapshot_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_vm_interpreter_debug_run_traced(PyObject* self, PyObject* py_arg0) {
    PyObject* py_start = py_arg0;
    kth_debug_snapshot_const_t start_handle = (kth_debug_snapshot_const_t)PyCapsule_GetPointer(py_start, KTH_PY_CAPSULE_VM_DEBUG_SNAPSHOT);
    if (start_handle == NULL) return NULL;
    auto const result = kth_vm_interpreter_debug_run_traced(start_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL list returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_VM_DEBUG_SNAPSHOT_LIST, kth_py_native_vm_debug_snapshot_list_capsule_dtor);
    if (capsule == NULL) {
        kth_vm_debug_snapshot_list_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_vm_interpreter_debug_finalize(PyObject* self, PyObject* py_arg0) {
    PyObject* py_snapshot = py_arg0;
    kth_debug_snapshot_const_t snapshot_handle = (kth_debug_snapshot_const_t)PyCapsule_GetPointer(py_snapshot, KTH_PY_CAPSULE_VM_DEBUG_SNAPSHOT);
    if (snapshot_handle == NULL) return NULL;
    auto const result = kth_vm_interpreter_debug_finalize(snapshot_handle);
    return PyLong_FromLong((long)result);
}

PyMethodDef kth_py_native_vm_interpreter_methods[] = {
    {"vm_interpreter_run_simple", (PyCFunction)kth_py_native_vm_interpreter_run_simple, METH_O, NULL},
    {"vm_interpreter_run", (PyCFunction)kth_py_native_vm_interpreter_run, METH_VARARGS | METH_KEYWORDS, NULL},
    {"vm_interpreter_debug_begin", (PyCFunction)kth_py_native_vm_interpreter_debug_begin, METH_O, NULL},
    {"vm_interpreter_debug_step", (PyCFunction)kth_py_native_vm_interpreter_debug_step, METH_O, NULL},
    {"vm_interpreter_debug_step_n", (PyCFunction)kth_py_native_vm_interpreter_debug_step_n, METH_VARARGS | METH_KEYWORDS, NULL},
    {"vm_interpreter_debug_run", (PyCFunction)kth_py_native_vm_interpreter_debug_run, METH_O, NULL},
    {"vm_interpreter_debug_run_traced", (PyCFunction)kth_py_native_vm_interpreter_debug_run_traced, METH_O, NULL},
    {"vm_interpreter_debug_finalize", (PyCFunction)kth_py_native_vm_interpreter_debug_finalize, METH_O, NULL},
    {NULL, NULL, 0, NULL}  // sentinel
};

#ifdef __cplusplus
} // extern "C"
#endif
