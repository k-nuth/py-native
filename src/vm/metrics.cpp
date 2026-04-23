// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/py-native/vm/metrics.h>

#include <string.h>
#include <kth/capi.h>
#include <kth/capi/vm/metrics.h>
#include <kth/py-native/capsule_names.h>
#include <kth/py-native/utils.h>

#ifdef __cplusplus
extern "C" {
#endif

// PyCapsule destructor — released by GC when the capsule is
// collected. Explicit `destruct` calls set the capsule name to
// "kth.destroyed", so PyCapsule_IsValid returns false and this
// destructor becomes a no-op (no double-free).
void kth_py_native_vm_metrics_capsule_dtor(PyObject* capsule) {
    if ( ! PyCapsule_IsValid(capsule, KTH_PY_CAPSULE_VM_METRICS)) return;
    kth_metrics_mut_t handle = (kth_metrics_mut_t)PyCapsule_GetPointer(capsule, KTH_PY_CAPSULE_VM_METRICS);
    if (handle != NULL) kth_vm_metrics_destruct(handle);
}

PyObject*
kth_py_native_vm_metrics_copy(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_metrics_const_t self_handle = (kth_metrics_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_METRICS);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_metrics_copy(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_VM_METRICS, kth_py_native_vm_metrics_capsule_dtor);
    if (capsule == NULL) {
        kth_vm_metrics_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_vm_metrics_destruct(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_metrics_mut_t self_handle = (kth_metrics_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_METRICS);
    if (self_handle == NULL) return NULL;
    kth_vm_metrics_destruct(self_handle);
    PyCapsule_SetName(py_self, "kth.destroyed");
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_vm_metrics_sig_checks(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_metrics_const_t self_handle = (kth_metrics_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_METRICS);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_metrics_sig_checks(self_handle);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyObject*
kth_py_native_vm_metrics_op_cost(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_metrics_const_t self_handle = (kth_metrics_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_METRICS);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_metrics_op_cost(self_handle);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyObject*
kth_py_native_vm_metrics_hash_digest_iterations(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_metrics_const_t self_handle = (kth_metrics_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_METRICS);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_metrics_hash_digest_iterations(self_handle);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyObject*
kth_py_native_vm_metrics_add_op_cost(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"cost", NULL};
    PyObject* py_self = NULL;
    unsigned int cost = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OI", kwlist, &py_self, &cost)) {
        return NULL;
    }
    kth_metrics_mut_t self_handle = (kth_metrics_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_METRICS);
    if (self_handle == NULL) return NULL;
    kth_vm_metrics_add_op_cost(self_handle, (uint32_t)cost);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_vm_metrics_add_push_op(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"stack_item_length", NULL};
    PyObject* py_self = NULL;
    unsigned int stack_item_length = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OI", kwlist, &py_self, &stack_item_length)) {
        return NULL;
    }
    kth_metrics_mut_t self_handle = (kth_metrics_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_METRICS);
    if (self_handle == NULL) return NULL;
    kth_vm_metrics_add_push_op(self_handle, (uint32_t)stack_item_length);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_vm_metrics_add_hash_iterations(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"message_length", (char*)"is_two_round_hash", NULL};
    PyObject* py_self = NULL;
    unsigned int message_length = 0;
    int is_two_round_hash = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OIp", kwlist, &py_self, &message_length, &is_two_round_hash)) {
        return NULL;
    }
    kth_metrics_mut_t self_handle = (kth_metrics_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_METRICS);
    if (self_handle == NULL) return NULL;
    kth_vm_metrics_add_hash_iterations(self_handle, (uint32_t)message_length, (kth_bool_t)is_two_round_hash);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_vm_metrics_add_sig_checks(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"n_checks", NULL};
    PyObject* py_self = NULL;
    unsigned int n_checks = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OI", kwlist, &py_self, &n_checks)) {
        return NULL;
    }
    kth_metrics_mut_t self_handle = (kth_metrics_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_METRICS);
    if (self_handle == NULL) return NULL;
    kth_vm_metrics_add_sig_checks(self_handle, (uint32_t)n_checks);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_vm_metrics_is_over_op_cost_limit(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"flags", NULL};
    PyObject* py_self = NULL;
    unsigned long long flags = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OK", kwlist, &py_self, &flags)) {
        return NULL;
    }
    kth_metrics_const_t self_handle = (kth_metrics_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_METRICS);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_metrics_is_over_op_cost_limit(self_handle, (kth_script_flags_t)flags);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_vm_metrics_is_over_op_cost_limit_simple(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_metrics_const_t self_handle = (kth_metrics_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_METRICS);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_metrics_is_over_op_cost_limit_simple(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_vm_metrics_is_over_hash_iters_limit(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_metrics_const_t self_handle = (kth_metrics_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_METRICS);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_metrics_is_over_hash_iters_limit(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_vm_metrics_has_valid_script_limits(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_metrics_const_t self_handle = (kth_metrics_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_METRICS);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_metrics_has_valid_script_limits(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_vm_metrics_set_script_limits(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"flags", (char*)"script_sig_size", NULL};
    PyObject* py_self = NULL;
    unsigned long long flags = 0;
    unsigned long long script_sig_size = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OKK", kwlist, &py_self, &flags, &script_sig_size)) {
        return NULL;
    }
    kth_metrics_mut_t self_handle = (kth_metrics_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_METRICS);
    if (self_handle == NULL) return NULL;
    kth_vm_metrics_set_script_limits(self_handle, (kth_script_flags_t)flags, (uint64_t)script_sig_size);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_vm_metrics_set_native_script_limits(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"standard", (char*)"script_sig_size", NULL};
    PyObject* py_self = NULL;
    int standard = 0;
    unsigned long long script_sig_size = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OpK", kwlist, &py_self, &standard, &script_sig_size)) {
        return NULL;
    }
    kth_metrics_mut_t self_handle = (kth_metrics_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_METRICS);
    if (self_handle == NULL) return NULL;
    kth_vm_metrics_set_native_script_limits(self_handle, (kth_bool_t)standard, (uint64_t)script_sig_size);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_vm_metrics_composite_op_cost_script_flags(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"flags", NULL};
    PyObject* py_self = NULL;
    unsigned long long flags = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OK", kwlist, &py_self, &flags)) {
        return NULL;
    }
    kth_metrics_const_t self_handle = (kth_metrics_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_METRICS);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_metrics_composite_op_cost_script_flags(self_handle, (kth_script_flags_t)flags);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyObject*
kth_py_native_vm_metrics_composite_op_cost_bool(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"standard", NULL};
    PyObject* py_self = NULL;
    int standard = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Op", kwlist, &py_self, &standard)) {
        return NULL;
    }
    kth_metrics_const_t self_handle = (kth_metrics_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_METRICS);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_metrics_composite_op_cost_bool(self_handle, (kth_bool_t)standard);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyMethodDef kth_py_native_vm_metrics_methods[] = {
    {"vm_metrics_copy", (PyCFunction)kth_py_native_vm_metrics_copy, METH_O, NULL},
    {"vm_metrics_destruct", (PyCFunction)kth_py_native_vm_metrics_destruct, METH_O, NULL},
    {"vm_metrics_sig_checks", (PyCFunction)kth_py_native_vm_metrics_sig_checks, METH_O, NULL},
    {"vm_metrics_op_cost", (PyCFunction)kth_py_native_vm_metrics_op_cost, METH_O, NULL},
    {"vm_metrics_hash_digest_iterations", (PyCFunction)kth_py_native_vm_metrics_hash_digest_iterations, METH_O, NULL},
    {"vm_metrics_add_op_cost", (PyCFunction)kth_py_native_vm_metrics_add_op_cost, METH_VARARGS | METH_KEYWORDS, NULL},
    {"vm_metrics_add_push_op", (PyCFunction)kth_py_native_vm_metrics_add_push_op, METH_VARARGS | METH_KEYWORDS, NULL},
    {"vm_metrics_add_hash_iterations", (PyCFunction)kth_py_native_vm_metrics_add_hash_iterations, METH_VARARGS | METH_KEYWORDS, NULL},
    {"vm_metrics_add_sig_checks", (PyCFunction)kth_py_native_vm_metrics_add_sig_checks, METH_VARARGS | METH_KEYWORDS, NULL},
    {"vm_metrics_is_over_op_cost_limit", (PyCFunction)kth_py_native_vm_metrics_is_over_op_cost_limit, METH_VARARGS | METH_KEYWORDS, NULL},
    {"vm_metrics_is_over_op_cost_limit_simple", (PyCFunction)kth_py_native_vm_metrics_is_over_op_cost_limit_simple, METH_O, NULL},
    {"vm_metrics_is_over_hash_iters_limit", (PyCFunction)kth_py_native_vm_metrics_is_over_hash_iters_limit, METH_O, NULL},
    {"vm_metrics_has_valid_script_limits", (PyCFunction)kth_py_native_vm_metrics_has_valid_script_limits, METH_O, NULL},
    {"vm_metrics_set_script_limits", (PyCFunction)kth_py_native_vm_metrics_set_script_limits, METH_VARARGS | METH_KEYWORDS, NULL},
    {"vm_metrics_set_native_script_limits", (PyCFunction)kth_py_native_vm_metrics_set_native_script_limits, METH_VARARGS | METH_KEYWORDS, NULL},
    {"vm_metrics_composite_op_cost_script_flags", (PyCFunction)kth_py_native_vm_metrics_composite_op_cost_script_flags, METH_VARARGS | METH_KEYWORDS, NULL},
    {"vm_metrics_composite_op_cost_bool", (PyCFunction)kth_py_native_vm_metrics_composite_op_cost_bool, METH_VARARGS | METH_KEYWORDS, NULL},
    {NULL, NULL, 0, NULL}  // sentinel
};

#ifdef __cplusplus
} // extern "C"
#endif
