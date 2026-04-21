// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/py-native/chain/prefilled_transaction.h>

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
void kth_py_native_chain_prefilled_transaction_capsule_dtor(PyObject* capsule) {
    if ( ! PyCapsule_IsValid(capsule, KTH_PY_CAPSULE_CHAIN_PREFILLED_TRANSACTION)) return;
    kth_prefilled_transaction_mut_t handle = (kth_prefilled_transaction_mut_t)PyCapsule_GetPointer(capsule, KTH_PY_CAPSULE_CHAIN_PREFILLED_TRANSACTION);
    if (handle != NULL) kth_chain_prefilled_transaction_destruct(handle);
}

PyObject*
kth_py_native_chain_prefilled_transaction_construct_default(PyObject* self, PyObject* Py_UNUSED(args)) {
    auto const result = kth_chain_prefilled_transaction_construct_default();
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_PREFILLED_TRANSACTION, kth_py_native_chain_prefilled_transaction_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_prefilled_transaction_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_prefilled_transaction_construct_from_data(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"reader", (char*)"version", NULL};
    char const* reader_buf = NULL;
    Py_ssize_t reader_size = 0;
    unsigned int version = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "y#I", kwlist, &reader_buf, &reader_size, &version)) {
        return NULL;
    }
    kth_prefilled_transaction_mut_t out = NULL;
    kth_error_code_t result = kth_chain_prefilled_transaction_construct_from_data((uint8_t const*)reader_buf, (kth_size_t)reader_size, (uint32_t)version, &out);
    if (result != kth_ec_success) {
        PyErr_Format(PyExc_RuntimeError, "kth error code %d", (int)result);
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)out, KTH_PY_CAPSULE_CHAIN_PREFILLED_TRANSACTION, kth_py_native_chain_prefilled_transaction_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_prefilled_transaction_destruct(out);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_prefilled_transaction_construct(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"index", (char*)"tx", NULL};
    unsigned long long index = 0;
    PyObject* py_tx = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "KO", kwlist, &index, &py_tx)) {
        return NULL;
    }
    kth_transaction_const_t tx_handle = (kth_transaction_const_t)PyCapsule_GetPointer(py_tx, KTH_PY_CAPSULE_CHAIN_TRANSACTION);
    if (tx_handle == NULL) return NULL;
    auto const result = kth_chain_prefilled_transaction_construct((uint64_t)index, tx_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_PREFILLED_TRANSACTION, kth_py_native_chain_prefilled_transaction_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_prefilled_transaction_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_prefilled_transaction_copy(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_prefilled_transaction_const_t self_handle = (kth_prefilled_transaction_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_PREFILLED_TRANSACTION);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_prefilled_transaction_copy(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_PREFILLED_TRANSACTION, kth_py_native_chain_prefilled_transaction_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_prefilled_transaction_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_prefilled_transaction_destruct(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_prefilled_transaction_mut_t self_handle = (kth_prefilled_transaction_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_PREFILLED_TRANSACTION);
    if (self_handle == NULL) return NULL;
    kth_chain_prefilled_transaction_destruct(self_handle);
    PyCapsule_SetName(py_self, "kth.destroyed");
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_prefilled_transaction_equals(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"other", NULL};
    PyObject* py_self = NULL;
    PyObject* py_other = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_other)) {
        return NULL;
    }
    kth_prefilled_transaction_const_t self_handle = (kth_prefilled_transaction_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_PREFILLED_TRANSACTION);
    if (self_handle == NULL) return NULL;
    kth_prefilled_transaction_const_t other_handle = (kth_prefilled_transaction_const_t)PyCapsule_GetPointer(py_other, KTH_PY_CAPSULE_CHAIN_PREFILLED_TRANSACTION);
    if (other_handle == NULL) return NULL;
    auto const result = kth_chain_prefilled_transaction_equals(self_handle, other_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_prefilled_transaction_index(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_prefilled_transaction_const_t self_handle = (kth_prefilled_transaction_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_PREFILLED_TRANSACTION);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_prefilled_transaction_index(self_handle);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyObject*
kth_py_native_chain_prefilled_transaction_set_index(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    unsigned long long value = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OK", kwlist, &py_self, &value)) {
        return NULL;
    }
    kth_prefilled_transaction_mut_t self_handle = (kth_prefilled_transaction_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_PREFILLED_TRANSACTION);
    if (self_handle == NULL) return NULL;
    kth_chain_prefilled_transaction_set_index(self_handle, (uint64_t)value);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_prefilled_transaction_transaction(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_prefilled_transaction_const_t self_handle = (kth_prefilled_transaction_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_PREFILLED_TRANSACTION);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_prefilled_transaction_transaction(self_handle);
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
kth_py_native_chain_prefilled_transaction_set_transaction(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"tx", NULL};
    PyObject* py_self = NULL;
    PyObject* py_tx = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_tx)) {
        return NULL;
    }
    kth_prefilled_transaction_mut_t self_handle = (kth_prefilled_transaction_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_PREFILLED_TRANSACTION);
    if (self_handle == NULL) return NULL;
    kth_transaction_const_t tx_handle = (kth_transaction_const_t)PyCapsule_GetPointer(py_tx, KTH_PY_CAPSULE_CHAIN_TRANSACTION);
    if (tx_handle == NULL) return NULL;
    kth_chain_prefilled_transaction_set_transaction(self_handle, tx_handle);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_prefilled_transaction_to_data(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"version", NULL};
    PyObject* py_self = NULL;
    unsigned int version = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OI", kwlist, &py_self, &version)) {
        return NULL;
    }
    kth_prefilled_transaction_const_t self_handle = (kth_prefilled_transaction_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_PREFILLED_TRANSACTION);
    if (self_handle == NULL) return NULL;
    kth_size_t out_size = 0;
    auto const result = kth_chain_prefilled_transaction_to_data(self_handle, (uint32_t)version, &out_size);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: serialization failed");
        return NULL;
    }
    PyObject* py_result = Py_BuildValue("y#", result, (Py_ssize_t)out_size);
    kth_core_destruct_array(result);
    return py_result;
}

PyObject*
kth_py_native_chain_prefilled_transaction_is_valid(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_prefilled_transaction_const_t self_handle = (kth_prefilled_transaction_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_PREFILLED_TRANSACTION);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_prefilled_transaction_is_valid(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_prefilled_transaction_reset(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_prefilled_transaction_mut_t self_handle = (kth_prefilled_transaction_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_PREFILLED_TRANSACTION);
    if (self_handle == NULL) return NULL;
    kth_chain_prefilled_transaction_reset(self_handle);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_prefilled_transaction_serialized_size(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"version", NULL};
    PyObject* py_self = NULL;
    unsigned int version = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OI", kwlist, &py_self, &version)) {
        return NULL;
    }
    kth_prefilled_transaction_const_t self_handle = (kth_prefilled_transaction_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_PREFILLED_TRANSACTION);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_prefilled_transaction_serialized_size(self_handle, (uint32_t)version);
    return PyLong_FromSize_t((size_t)result);
}

PyMethodDef kth_py_native_chain_prefilled_transaction_methods[] = {
    {"chain_prefilled_transaction_construct_default", (PyCFunction)kth_py_native_chain_prefilled_transaction_construct_default, METH_NOARGS, NULL},
    {"chain_prefilled_transaction_construct_from_data", (PyCFunction)kth_py_native_chain_prefilled_transaction_construct_from_data, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_prefilled_transaction_construct", (PyCFunction)kth_py_native_chain_prefilled_transaction_construct, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_prefilled_transaction_copy", (PyCFunction)kth_py_native_chain_prefilled_transaction_copy, METH_O, NULL},
    {"chain_prefilled_transaction_destruct", (PyCFunction)kth_py_native_chain_prefilled_transaction_destruct, METH_O, NULL},
    {"chain_prefilled_transaction_equals", (PyCFunction)kth_py_native_chain_prefilled_transaction_equals, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_prefilled_transaction_index", (PyCFunction)kth_py_native_chain_prefilled_transaction_index, METH_O, NULL},
    {"chain_prefilled_transaction_set_index", (PyCFunction)kth_py_native_chain_prefilled_transaction_set_index, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_prefilled_transaction_transaction", (PyCFunction)kth_py_native_chain_prefilled_transaction_transaction, METH_O, NULL},
    {"chain_prefilled_transaction_set_transaction", (PyCFunction)kth_py_native_chain_prefilled_transaction_set_transaction, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_prefilled_transaction_to_data", (PyCFunction)kth_py_native_chain_prefilled_transaction_to_data, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_prefilled_transaction_is_valid", (PyCFunction)kth_py_native_chain_prefilled_transaction_is_valid, METH_O, NULL},
    {"chain_prefilled_transaction_reset", (PyCFunction)kth_py_native_chain_prefilled_transaction_reset, METH_O, NULL},
    {"chain_prefilled_transaction_serialized_size", (PyCFunction)kth_py_native_chain_prefilled_transaction_serialized_size, METH_VARARGS | METH_KEYWORDS, NULL},
    {NULL, NULL, 0, NULL}  // sentinel
};

#ifdef __cplusplus
} // extern "C"
#endif
