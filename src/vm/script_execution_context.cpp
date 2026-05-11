// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/py-native/vm/script_execution_context.h>

#include <string.h>
#include <kth/capi.h>
#include <kth/capi/vm/script_execution_context.h>
#include <kth/py-native/capsule_names.h>
#include <kth/py-native/utils.h>

#ifdef __cplusplus
extern "C" {
#endif

// PyCapsule destructor — released by GC when the capsule is
// collected. Explicit `destruct` calls set the capsule name to
// "kth.destroyed", so PyCapsule_IsValid returns false and this
// destructor becomes a no-op (no double-free).
void kth_py_native_vm_script_execution_context_capsule_dtor(PyObject* capsule) {
    if ( ! PyCapsule_IsValid(capsule, KTH_PY_CAPSULE_VM_SCRIPT_EXECUTION_CONTEXT)) return;
    kth_script_execution_context_mut_t handle = (kth_script_execution_context_mut_t)PyCapsule_GetPointer(capsule, KTH_PY_CAPSULE_VM_SCRIPT_EXECUTION_CONTEXT);
    if (handle != NULL) kth_vm_script_execution_context_destruct(handle);
}

PyObject*
kth_py_native_vm_script_execution_context_construct(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"input_index", (char*)"transaction", NULL};
    unsigned int input_index = 0;
    PyObject* py_transaction = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "IO", kwlist, &input_index, &py_transaction)) {
        return NULL;
    }
    kth_transaction_const_t transaction_handle = (kth_transaction_const_t)PyCapsule_GetPointer(py_transaction, KTH_PY_CAPSULE_CHAIN_TRANSACTION);
    if (transaction_handle == NULL) return NULL;
    auto const result = kth_vm_script_execution_context_construct((uint32_t)input_index, transaction_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_VM_SCRIPT_EXECUTION_CONTEXT, kth_py_native_vm_script_execution_context_capsule_dtor);
    if (capsule == NULL) {
        kth_vm_script_execution_context_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_vm_script_execution_context_copy(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_script_execution_context_const_t self_handle = (kth_script_execution_context_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_SCRIPT_EXECUTION_CONTEXT);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_script_execution_context_copy(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_VM_SCRIPT_EXECUTION_CONTEXT, kth_py_native_vm_script_execution_context_capsule_dtor);
    if (capsule == NULL) {
        kth_vm_script_execution_context_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_vm_script_execution_context_destruct(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_script_execution_context_mut_t self_handle = (kth_script_execution_context_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_SCRIPT_EXECUTION_CONTEXT);
    if (self_handle == NULL) return NULL;
    kth_vm_script_execution_context_destruct(self_handle);
    PyCapsule_SetName(py_self, "kth.destroyed");
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_vm_script_execution_context_input_index(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_script_execution_context_const_t self_handle = (kth_script_execution_context_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_SCRIPT_EXECUTION_CONTEXT);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_script_execution_context_input_index(self_handle);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyObject*
kth_py_native_vm_script_execution_context_transaction(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_script_execution_context_const_t self_handle = (kth_script_execution_context_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_SCRIPT_EXECUTION_CONTEXT);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_script_execution_context_transaction(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_TRANSACTION, kth_py_native_borrowed_parent_dtor);
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
kth_py_native_vm_script_execution_context_input_count(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_script_execution_context_const_t self_handle = (kth_script_execution_context_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_SCRIPT_EXECUTION_CONTEXT);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_script_execution_context_input_count(self_handle);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyObject*
kth_py_native_vm_script_execution_context_output_count(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_script_execution_context_const_t self_handle = (kth_script_execution_context_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_SCRIPT_EXECUTION_CONTEXT);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_script_execution_context_output_count(self_handle);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyObject*
kth_py_native_vm_script_execution_context_tx_version(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_script_execution_context_const_t self_handle = (kth_script_execution_context_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_SCRIPT_EXECUTION_CONTEXT);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_script_execution_context_tx_version(self_handle);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyObject*
kth_py_native_vm_script_execution_context_tx_locktime(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_script_execution_context_const_t self_handle = (kth_script_execution_context_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_SCRIPT_EXECUTION_CONTEXT);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_script_execution_context_tx_locktime(self_handle);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyMethodDef kth_py_native_vm_script_execution_context_methods[] = {
    {"vm_script_execution_context_construct", (PyCFunction)kth_py_native_vm_script_execution_context_construct, METH_VARARGS | METH_KEYWORDS, NULL},
    {"vm_script_execution_context_copy", (PyCFunction)kth_py_native_vm_script_execution_context_copy, METH_O, NULL},
    {"vm_script_execution_context_destruct", (PyCFunction)kth_py_native_vm_script_execution_context_destruct, METH_O, NULL},
    {"vm_script_execution_context_input_index", (PyCFunction)kth_py_native_vm_script_execution_context_input_index, METH_O, NULL},
    {"vm_script_execution_context_transaction", (PyCFunction)kth_py_native_vm_script_execution_context_transaction, METH_O, NULL},
    {"vm_script_execution_context_input_count", (PyCFunction)kth_py_native_vm_script_execution_context_input_count, METH_O, NULL},
    {"vm_script_execution_context_output_count", (PyCFunction)kth_py_native_vm_script_execution_context_output_count, METH_O, NULL},
    {"vm_script_execution_context_tx_version", (PyCFunction)kth_py_native_vm_script_execution_context_tx_version, METH_O, NULL},
    {"vm_script_execution_context_tx_locktime", (PyCFunction)kth_py_native_vm_script_execution_context_tx_locktime, METH_O, NULL},
    {NULL, NULL, 0, NULL}  // sentinel
};

#ifdef __cplusplus
} // extern "C"
#endif
