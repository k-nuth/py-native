// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/py-native/chain/utxo_list.h>

#include <kth/capi.h>
#include <kth/capi/chain/utxo_list.h>
#include <kth/py-native/capsule_names.h>
#include <kth/py-native/utils.h>

#ifdef __cplusplus
extern "C" {
#endif

// PyCapsule destructor for this list type — GC-driven release.
void kth_py_native_chain_utxo_list_capsule_dtor(PyObject* capsule) {
    if ( ! PyCapsule_IsValid(capsule, KTH_PY_CAPSULE_CHAIN_UTXO_LIST)) return;
    kth_utxo_list_mut_t handle = (kth_utxo_list_mut_t)PyCapsule_GetPointer(capsule, KTH_PY_CAPSULE_CHAIN_UTXO_LIST);
    if (handle != NULL) kth_chain_utxo_list_destruct(handle);
}

PyObject* kth_py_native_chain_utxo_list_construct_default(PyObject* self, PyObject* Py_UNUSED(args)) {
    auto const result = kth_chain_utxo_list_construct_default();
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_UTXO_LIST, kth_py_native_chain_utxo_list_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_utxo_list_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject* kth_py_native_chain_utxo_list_push_back(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"list", (char*)"elem", NULL};
    PyObject* py_list = NULL;
    PyObject* py_elem = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_list, &py_elem)) {
        return NULL;
    }
    kth_utxo_list_mut_t list_handle = (kth_utxo_list_mut_t)PyCapsule_GetPointer(py_list, KTH_PY_CAPSULE_CHAIN_UTXO_LIST);
    if (list_handle == NULL) return NULL;
    kth_utxo_const_t elem_handle = (kth_utxo_const_t)PyCapsule_GetPointer(py_elem, KTH_PY_CAPSULE_CHAIN_UTXO);
    if (elem_handle == NULL) return NULL;
    kth_chain_utxo_list_push_back(list_handle, elem_handle);
    Py_RETURN_NONE;
}

PyObject* kth_py_native_chain_utxo_list_destruct(PyObject* self, PyObject* py_arg0) {
    kth_utxo_list_mut_t list_handle = (kth_utxo_list_mut_t)PyCapsule_GetPointer(py_arg0, KTH_PY_CAPSULE_CHAIN_UTXO_LIST);
    if (list_handle == NULL) return NULL;
    kth_chain_utxo_list_destruct(list_handle);
    PyCapsule_SetName(py_arg0, "kth.destroyed");
    Py_RETURN_NONE;
}

PyObject* kth_py_native_chain_utxo_list_count(PyObject* self, PyObject* py_arg0) {
    kth_utxo_list_const_t list_handle = (kth_utxo_list_const_t)PyCapsule_GetPointer(py_arg0, KTH_PY_CAPSULE_CHAIN_UTXO_LIST);
    if (list_handle == NULL) return NULL;
    auto const result = kth_chain_utxo_list_count(list_handle);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyObject* kth_py_native_chain_utxo_list_nth(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"list", (char*)"index", NULL};
    PyObject* py_list = NULL;
    unsigned long long index = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OK", kwlist, &py_list, &index)) {
        return NULL;
    }
    kth_utxo_list_const_t list_handle = (kth_utxo_list_const_t)PyCapsule_GetPointer(py_list, KTH_PY_CAPSULE_CHAIN_UTXO_LIST);
    if (list_handle == NULL) return NULL;
    kth_size_t const count = kth_chain_utxo_list_count(list_handle);
    if ((kth_size_t)index >= count) {
        PyErr_Format(PyExc_IndexError, "list index %llu out of range (size %llu)", index, (unsigned long long)count);
        return NULL;
    }
    auto const result = kth_chain_utxo_list_nth(list_handle, (kth_size_t)index);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned from list nth");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_UTXO, kth_py_native_borrowed_parent_dtor);
    if (capsule == NULL) return NULL;
    Py_INCREF(py_list);
    if (PyCapsule_SetContext(capsule, py_list) != 0) {
        Py_DECREF(py_list);
        Py_DECREF(capsule);
        return NULL;
    }
    return capsule;
}

PyObject* kth_py_native_chain_utxo_list_assign_at(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"list", (char*)"index", (char*)"elem", NULL};
    PyObject* py_list = NULL;
    unsigned long long index = 0;
    PyObject* py_elem = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OKO", kwlist, &py_list, &index, &py_elem)) {
        return NULL;
    }
    kth_utxo_list_mut_t list_handle = (kth_utxo_list_mut_t)PyCapsule_GetPointer(py_list, KTH_PY_CAPSULE_CHAIN_UTXO_LIST);
    if (list_handle == NULL) return NULL;
    kth_size_t const count = kth_chain_utxo_list_count(list_handle);
    if ((kth_size_t)index >= count) {
        PyErr_Format(PyExc_IndexError, "list index %llu out of range (size %llu)", index, (unsigned long long)count);
        return NULL;
    }
    kth_utxo_const_t elem_handle = (kth_utxo_const_t)PyCapsule_GetPointer(py_elem, KTH_PY_CAPSULE_CHAIN_UTXO);
    if (elem_handle == NULL) return NULL;
    kth_chain_utxo_list_assign_at(list_handle, (kth_size_t)index, elem_handle);
    Py_RETURN_NONE;
}

PyObject* kth_py_native_chain_utxo_list_erase(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"list", (char*)"index", NULL};
    PyObject* py_list = NULL;
    unsigned long long index = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OK", kwlist, &py_list, &index)) {
        return NULL;
    }
    kth_utxo_list_mut_t list_handle = (kth_utxo_list_mut_t)PyCapsule_GetPointer(py_list, KTH_PY_CAPSULE_CHAIN_UTXO_LIST);
    if (list_handle == NULL) return NULL;
    kth_size_t const count = kth_chain_utxo_list_count(list_handle);
    if ((kth_size_t)index >= count) {
        PyErr_Format(PyExc_IndexError, "list index %llu out of range (size %llu)", index, (unsigned long long)count);
        return NULL;
    }
    kth_chain_utxo_list_erase(list_handle, (kth_size_t)index);
    Py_RETURN_NONE;
}

PyMethodDef kth_py_native_chain_utxo_list_methods[] = {
    {"chain_utxo_list_construct_default", (PyCFunction)kth_py_native_chain_utxo_list_construct_default, METH_NOARGS, NULL},
    {"chain_utxo_list_push_back", (PyCFunction)kth_py_native_chain_utxo_list_push_back, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_utxo_list_destruct", (PyCFunction)kth_py_native_chain_utxo_list_destruct, METH_O, NULL},
    {"chain_utxo_list_count", (PyCFunction)kth_py_native_chain_utxo_list_count, METH_O, NULL},
    {"chain_utxo_list_nth", (PyCFunction)kth_py_native_chain_utxo_list_nth, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_utxo_list_assign_at", (PyCFunction)kth_py_native_chain_utxo_list_assign_at, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_utxo_list_erase", (PyCFunction)kth_py_native_chain_utxo_list_erase, METH_VARARGS | METH_KEYWORDS, NULL},
    {NULL, NULL, 0, NULL}  // sentinel
};

#ifdef __cplusplus
} // extern "C"
#endif
