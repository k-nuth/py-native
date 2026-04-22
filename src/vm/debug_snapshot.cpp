// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/py-native/vm/debug_snapshot.h>

#include <string.h>
#include <kth/capi.h>
#include <kth/capi/vm/debug_snapshot.h>
#include <kth/py-native/capsule_names.h>
#include <kth/py-native/utils.h>

#ifdef __cplusplus
extern "C" {
#endif

// PyCapsule destructor — released by GC when the capsule is
// collected. Explicit `destruct` calls set the capsule name to
// "kth.destroyed", so PyCapsule_IsValid returns false and this
// destructor becomes a no-op (no double-free).
void kth_py_native_vm_debug_snapshot_capsule_dtor(PyObject* capsule) {
    if ( ! PyCapsule_IsValid(capsule, KTH_PY_CAPSULE_VM_DEBUG_SNAPSHOT)) return;
    kth_debug_snapshot_mut_t handle = (kth_debug_snapshot_mut_t)PyCapsule_GetPointer(capsule, KTH_PY_CAPSULE_VM_DEBUG_SNAPSHOT);
    if (handle != NULL) kth_vm_debug_snapshot_destruct(handle);
}

PyObject*
kth_py_native_vm_debug_snapshot_construct_default(PyObject* self, PyObject* Py_UNUSED(args)) {
    auto const result = kth_vm_debug_snapshot_construct_default();
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
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
kth_py_native_vm_debug_snapshot_construct(PyObject* self, PyObject* py_arg0) {
    PyObject* py_p = py_arg0;
    kth_program_const_t p_handle = (kth_program_const_t)PyCapsule_GetPointer(py_p, KTH_PY_CAPSULE_VM_PROGRAM);
    if (p_handle == NULL) return NULL;
    auto const result = kth_vm_debug_snapshot_construct(p_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
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
kth_py_native_vm_debug_snapshot_copy(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_debug_snapshot_const_t self_handle = (kth_debug_snapshot_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_DEBUG_SNAPSHOT);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_debug_snapshot_copy(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
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
kth_py_native_vm_debug_snapshot_destruct(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_debug_snapshot_mut_t self_handle = (kth_debug_snapshot_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_DEBUG_SNAPSHOT);
    if (self_handle == NULL) return NULL;
    kth_vm_debug_snapshot_destruct(self_handle);
    PyCapsule_SetName(py_self, "kth.destroyed");
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_vm_debug_snapshot_prog(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_debug_snapshot_const_t self_handle = (kth_debug_snapshot_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_DEBUG_SNAPSHOT);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_debug_snapshot_prog(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_VM_PROGRAM, kth_py_native_borrowed_parent_dtor);
    if (capsule == NULL) return NULL;
    Py_INCREF(py_self);
    if (PyCapsule_SetContext(capsule, py_self) != 0) {
        Py_DECREF(py_self);
        Py_DECREF(capsule);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_vm_debug_snapshot_step(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_debug_snapshot_const_t self_handle = (kth_debug_snapshot_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_DEBUG_SNAPSHOT);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_debug_snapshot_step(self_handle);
    return PyLong_FromSize_t((size_t)result);
}

PyObject*
kth_py_native_vm_debug_snapshot_last(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_debug_snapshot_const_t self_handle = (kth_debug_snapshot_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_DEBUG_SNAPSHOT);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_debug_snapshot_last(self_handle);
    return PyLong_FromLong((long)result);
}

PyObject*
kth_py_native_vm_debug_snapshot_done(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_debug_snapshot_const_t self_handle = (kth_debug_snapshot_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_DEBUG_SNAPSHOT);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_debug_snapshot_done(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_vm_debug_snapshot_control_stack(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_debug_snapshot_const_t self_handle = (kth_debug_snapshot_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_DEBUG_SNAPSHOT);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_debug_snapshot_control_stack(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL list returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CORE_BOOL_LIST, kth_py_native_borrowed_parent_dtor);
    if (capsule == NULL) return NULL;
    Py_INCREF(py_self);
    if (PyCapsule_SetContext(capsule, py_self) != 0) {
        Py_DECREF(py_self);
        Py_DECREF(capsule);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_vm_debug_snapshot_loop_stack(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_debug_snapshot_const_t self_handle = (kth_debug_snapshot_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_DEBUG_SNAPSHOT);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_debug_snapshot_loop_stack(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL list returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CORE_U64_LIST, kth_py_native_borrowed_parent_dtor);
    if (capsule == NULL) return NULL;
    Py_INCREF(py_self);
    if (PyCapsule_SetContext(capsule, py_self) != 0) {
        Py_DECREF(py_self);
        Py_DECREF(capsule);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_vm_debug_snapshot_invoke_depth(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_debug_snapshot_const_t self_handle = (kth_debug_snapshot_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_DEBUG_SNAPSHOT);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_debug_snapshot_invoke_depth(self_handle);
    return PyLong_FromSize_t((size_t)result);
}

PyObject*
kth_py_native_vm_debug_snapshot_outer_loop_depth(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_debug_snapshot_const_t self_handle = (kth_debug_snapshot_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_DEBUG_SNAPSHOT);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_debug_snapshot_outer_loop_depth(self_handle);
    return PyLong_FromSize_t((size_t)result);
}

PyMethodDef kth_py_native_vm_debug_snapshot_methods[] = {
    {"vm_debug_snapshot_construct_default", (PyCFunction)kth_py_native_vm_debug_snapshot_construct_default, METH_NOARGS, NULL},
    {"vm_debug_snapshot_construct", (PyCFunction)kth_py_native_vm_debug_snapshot_construct, METH_O, NULL},
    {"vm_debug_snapshot_copy", (PyCFunction)kth_py_native_vm_debug_snapshot_copy, METH_O, NULL},
    {"vm_debug_snapshot_destruct", (PyCFunction)kth_py_native_vm_debug_snapshot_destruct, METH_O, NULL},
    {"vm_debug_snapshot_prog", (PyCFunction)kth_py_native_vm_debug_snapshot_prog, METH_O, NULL},
    {"vm_debug_snapshot_step", (PyCFunction)kth_py_native_vm_debug_snapshot_step, METH_O, NULL},
    {"vm_debug_snapshot_last", (PyCFunction)kth_py_native_vm_debug_snapshot_last, METH_O, NULL},
    {"vm_debug_snapshot_done", (PyCFunction)kth_py_native_vm_debug_snapshot_done, METH_O, NULL},
    {"vm_debug_snapshot_control_stack", (PyCFunction)kth_py_native_vm_debug_snapshot_control_stack, METH_O, NULL},
    {"vm_debug_snapshot_loop_stack", (PyCFunction)kth_py_native_vm_debug_snapshot_loop_stack, METH_O, NULL},
    {"vm_debug_snapshot_invoke_depth", (PyCFunction)kth_py_native_vm_debug_snapshot_invoke_depth, METH_O, NULL},
    {"vm_debug_snapshot_outer_loop_depth", (PyCFunction)kth_py_native_vm_debug_snapshot_outer_loop_depth, METH_O, NULL},
    {NULL, NULL, 0, NULL}  // sentinel
};

#ifdef __cplusplus
} // extern "C"
#endif
