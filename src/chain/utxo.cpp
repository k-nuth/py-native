// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/py-native/chain/utxo.h>

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
void kth_py_native_chain_utxo_capsule_dtor(PyObject* capsule) {
    if ( ! PyCapsule_IsValid(capsule, KTH_PY_CAPSULE_CHAIN_UTXO)) return;
    kth_utxo_mut_t handle = (kth_utxo_mut_t)PyCapsule_GetPointer(capsule, KTH_PY_CAPSULE_CHAIN_UTXO);
    if (handle != NULL) kth_chain_utxo_destruct(handle);
}

PyObject*
kth_py_native_chain_utxo_construct_default(PyObject* self, PyObject* Py_UNUSED(args)) {
    auto const result = kth_chain_utxo_construct_default();
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_UTXO, kth_py_native_chain_utxo_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_utxo_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_utxo_copy(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_utxo_const_t self_handle = (kth_utxo_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_UTXO);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_utxo_copy(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_UTXO, kth_py_native_chain_utxo_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_utxo_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_utxo_destruct(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_utxo_mut_t self_handle = (kth_utxo_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_UTXO);
    if (self_handle == NULL) return NULL;
    kth_chain_utxo_destruct(self_handle);
    PyCapsule_SetName(py_self, "kth.destroyed");
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_utxo_equals(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"other", NULL};
    PyObject* py_self = NULL;
    PyObject* py_other = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_other)) {
        return NULL;
    }
    kth_utxo_const_t self_handle = (kth_utxo_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_UTXO);
    if (self_handle == NULL) return NULL;
    kth_utxo_const_t other_handle = (kth_utxo_const_t)PyCapsule_GetPointer(py_other, KTH_PY_CAPSULE_CHAIN_UTXO);
    if (other_handle == NULL) return NULL;
    auto const result = kth_chain_utxo_equals(self_handle, other_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_utxo_height(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_utxo_const_t self_handle = (kth_utxo_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_UTXO);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_utxo_height(self_handle);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyObject*
kth_py_native_chain_utxo_point(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_utxo_const_t self_handle = (kth_utxo_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_UTXO);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_utxo_point(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_OUTPUT_POINT, kth_py_native_borrowed_parent_dtor);
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
kth_py_native_chain_utxo_amount(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_utxo_const_t self_handle = (kth_utxo_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_UTXO);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_utxo_amount(self_handle);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyObject*
kth_py_native_chain_utxo_set_height(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"height", NULL};
    PyObject* py_self = NULL;
    unsigned int height = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OI", kwlist, &py_self, &height)) {
        return NULL;
    }
    kth_utxo_mut_t self_handle = (kth_utxo_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_UTXO);
    if (self_handle == NULL) return NULL;
    kth_chain_utxo_set_height(self_handle, (uint32_t)height);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_utxo_set_point(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"point", NULL};
    PyObject* py_self = NULL;
    PyObject* py_point = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_point)) {
        return NULL;
    }
    kth_utxo_mut_t self_handle = (kth_utxo_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_UTXO);
    if (self_handle == NULL) return NULL;
    kth_output_point_const_t point_handle = (kth_output_point_const_t)PyCapsule_GetPointer(py_point, KTH_PY_CAPSULE_CHAIN_OUTPUT_POINT);
    if (point_handle == NULL) return NULL;
    kth_chain_utxo_set_point(self_handle, point_handle);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_utxo_set_amount(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"amount", NULL};
    PyObject* py_self = NULL;
    unsigned long long amount = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OK", kwlist, &py_self, &amount)) {
        return NULL;
    }
    kth_utxo_mut_t self_handle = (kth_utxo_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_UTXO);
    if (self_handle == NULL) return NULL;
    kth_chain_utxo_set_amount(self_handle, (uint64_t)amount);
    Py_RETURN_NONE;
}

PyMethodDef kth_py_native_chain_utxo_methods[] = {
    {"chain_utxo_construct_default", (PyCFunction)kth_py_native_chain_utxo_construct_default, METH_NOARGS, NULL},
    {"chain_utxo_copy", (PyCFunction)kth_py_native_chain_utxo_copy, METH_O, NULL},
    {"chain_utxo_destruct", (PyCFunction)kth_py_native_chain_utxo_destruct, METH_O, NULL},
    {"chain_utxo_equals", (PyCFunction)kth_py_native_chain_utxo_equals, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_utxo_height", (PyCFunction)kth_py_native_chain_utxo_height, METH_O, NULL},
    {"chain_utxo_point", (PyCFunction)kth_py_native_chain_utxo_point, METH_O, NULL},
    {"chain_utxo_amount", (PyCFunction)kth_py_native_chain_utxo_amount, METH_O, NULL},
    {"chain_utxo_set_height", (PyCFunction)kth_py_native_chain_utxo_set_height, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_utxo_set_point", (PyCFunction)kth_py_native_chain_utxo_set_point, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_utxo_set_amount", (PyCFunction)kth_py_native_chain_utxo_set_amount, METH_VARARGS | METH_KEYWORDS, NULL},
    {NULL, NULL, 0, NULL}  // sentinel
};

#ifdef __cplusplus
} // extern "C"
#endif
