// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/py-native/chain/history_compact.h>

#include <string.h>
#include <kth/capi.h>
#include <kth/py-native/capsule_names.h>
#include <kth/py-native/utils.h>

#ifdef __cplusplus
extern "C" {
#endif

// PyCapsule destructor — released by GC when the capsule is
// collected. Explicit `destruct` calls set the capsule name to
// "kth.destroyed", so PyCapsule_IsValid returns false and this
// destructor becomes a no-op (no double-free).
void kth_py_native_chain_history_compact_capsule_dtor(PyObject* capsule) {
    if ( ! PyCapsule_IsValid(capsule, KTH_PY_CAPSULE_CHAIN_HISTORY_COMPACT)) return;
    kth_history_compact_mut_t handle = (kth_history_compact_mut_t)PyCapsule_GetPointer(capsule, KTH_PY_CAPSULE_CHAIN_HISTORY_COMPACT);
    if (handle != NULL) kth_chain_history_compact_destruct(handle);
}

PyObject*
kth_py_native_chain_history_compact_copy(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_history_compact_const_t self_handle = (kth_history_compact_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_HISTORY_COMPACT);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_history_compact_copy(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_HISTORY_COMPACT, kth_py_native_chain_history_compact_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_history_compact_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_history_compact_destruct(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_history_compact_mut_t self_handle = (kth_history_compact_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_HISTORY_COMPACT);
    if (self_handle == NULL) return NULL;
    kth_chain_history_compact_destruct(self_handle);
    PyCapsule_SetName(py_self, "kth.destroyed");
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_history_compact_kind(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_history_compact_const_t self_handle = (kth_history_compact_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_HISTORY_COMPACT);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_history_compact_kind(self_handle);
    return PyLong_FromLong((long)result);
}

PyObject*
kth_py_native_chain_history_compact_set_kind(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    unsigned long long value = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OK", kwlist, &py_self, &value)) {
        return NULL;
    }
    kth_history_compact_mut_t self_handle = (kth_history_compact_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_HISTORY_COMPACT);
    if (self_handle == NULL) return NULL;
    kth_chain_history_compact_set_kind(self_handle, (kth_point_kind_t)value);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_history_compact_point(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_history_compact_const_t self_handle = (kth_history_compact_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_HISTORY_COMPACT);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_history_compact_point(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_POINT, kth_py_native_borrowed_parent_dtor);
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
kth_py_native_chain_history_compact_set_point(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    PyObject* py_value = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_value)) {
        return NULL;
    }
    kth_history_compact_mut_t self_handle = (kth_history_compact_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_HISTORY_COMPACT);
    if (self_handle == NULL) return NULL;
    kth_point_const_t value_handle = (kth_point_const_t)PyCapsule_GetPointer(py_value, KTH_PY_CAPSULE_CHAIN_POINT);
    if (value_handle == NULL) return NULL;
    kth_chain_history_compact_set_point(self_handle, value_handle);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_history_compact_height(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_history_compact_const_t self_handle = (kth_history_compact_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_HISTORY_COMPACT);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_history_compact_height(self_handle);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyObject*
kth_py_native_chain_history_compact_set_height(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    unsigned int value = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OI", kwlist, &py_self, &value)) {
        return NULL;
    }
    kth_history_compact_mut_t self_handle = (kth_history_compact_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_HISTORY_COMPACT);
    if (self_handle == NULL) return NULL;
    kth_chain_history_compact_set_height(self_handle, (uint32_t)value);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_history_compact_value_or_previous_checksum(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_history_compact_const_t self_handle = (kth_history_compact_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_HISTORY_COMPACT);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_history_compact_value_or_previous_checksum(self_handle);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyObject*
kth_py_native_chain_history_compact_set_value_or_previous_checksum(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    unsigned long long value = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OK", kwlist, &py_self, &value)) {
        return NULL;
    }
    kth_history_compact_mut_t self_handle = (kth_history_compact_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_HISTORY_COMPACT);
    if (self_handle == NULL) return NULL;
    kth_chain_history_compact_set_value_or_previous_checksum(self_handle, (uint64_t)value);
    Py_RETURN_NONE;
}

PyMethodDef kth_py_native_chain_history_compact_methods[] = {
    {"chain_history_compact_copy", (PyCFunction)kth_py_native_chain_history_compact_copy, METH_O, NULL},
    {"chain_history_compact_destruct", (PyCFunction)kth_py_native_chain_history_compact_destruct, METH_O, NULL},
    {"chain_history_compact_kind", (PyCFunction)kth_py_native_chain_history_compact_kind, METH_O, NULL},
    {"chain_history_compact_set_kind", (PyCFunction)kth_py_native_chain_history_compact_set_kind, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_history_compact_point", (PyCFunction)kth_py_native_chain_history_compact_point, METH_O, NULL},
    {"chain_history_compact_set_point", (PyCFunction)kth_py_native_chain_history_compact_set_point, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_history_compact_height", (PyCFunction)kth_py_native_chain_history_compact_height, METH_O, NULL},
    {"chain_history_compact_set_height", (PyCFunction)kth_py_native_chain_history_compact_set_height, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_history_compact_value_or_previous_checksum", (PyCFunction)kth_py_native_chain_history_compact_value_or_previous_checksum, METH_O, NULL},
    {"chain_history_compact_set_value_or_previous_checksum", (PyCFunction)kth_py_native_chain_history_compact_set_value_or_previous_checksum, METH_VARARGS | METH_KEYWORDS, NULL},
    {NULL, NULL, 0, NULL}  // sentinel
};

#ifdef __cplusplus
} // extern "C"
#endif
