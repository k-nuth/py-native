// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/py-native/chain/compact_block.h>

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
void kth_py_native_chain_compact_block_capsule_dtor(PyObject* capsule) {
    if ( ! PyCapsule_IsValid(capsule, KTH_PY_CAPSULE_CHAIN_COMPACT_BLOCK)) return;
    kth_compact_block_mut_t handle = (kth_compact_block_mut_t)PyCapsule_GetPointer(capsule, KTH_PY_CAPSULE_CHAIN_COMPACT_BLOCK);
    if (handle != NULL) kth_chain_compact_block_destruct(handle);
}

PyObject*
kth_py_native_chain_compact_block_construct_default(PyObject* self, PyObject* Py_UNUSED(args)) {
    auto const result = kth_chain_compact_block_construct_default();
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_COMPACT_BLOCK, kth_py_native_chain_compact_block_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_compact_block_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_compact_block_construct_from_data(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"reader", (char*)"version", NULL};
    char const* reader_buf = NULL;
    Py_ssize_t reader_size = 0;
    unsigned int version = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "y#I", kwlist, &reader_buf, &reader_size, &version)) {
        return NULL;
    }
    kth_compact_block_mut_t out = NULL;
    kth_error_code_t result = kth_chain_compact_block_construct_from_data((uint8_t const*)reader_buf, (kth_size_t)reader_size, (uint32_t)version, &out);
    if (result != kth_ec_success) {
        PyErr_Format(PyExc_RuntimeError, "kth error code %d", (int)result);
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)out, KTH_PY_CAPSULE_CHAIN_COMPACT_BLOCK, kth_py_native_chain_compact_block_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_compact_block_destruct(out);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_compact_block_construct(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"header", (char*)"nonce", (char*)"short_ids", (char*)"transactions", NULL};
    PyObject* py_header = NULL;
    unsigned long long nonce = 0;
    PyObject* py_short_ids = NULL;
    PyObject* py_transactions = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OKOO", kwlist, &py_header, &nonce, &py_short_ids, &py_transactions)) {
        return NULL;
    }
    kth_header_const_t header_handle = (kth_header_const_t)PyCapsule_GetPointer(py_header, KTH_PY_CAPSULE_CHAIN_HEADER);
    if (header_handle == NULL) return NULL;
    kth_u64_list_const_t short_ids_handle = (kth_u64_list_const_t)PyCapsule_GetPointer(py_short_ids, KTH_PY_CAPSULE_CORE_U64_LIST);
    if (short_ids_handle == NULL) return NULL;
    kth_prefilled_transaction_list_const_t transactions_handle = (kth_prefilled_transaction_list_const_t)PyCapsule_GetPointer(py_transactions, KTH_PY_CAPSULE_CHAIN_PREFILLED_TRANSACTION_LIST);
    if (transactions_handle == NULL) return NULL;
    auto const result = kth_chain_compact_block_construct(header_handle, (uint64_t)nonce, short_ids_handle, transactions_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_COMPACT_BLOCK, kth_py_native_chain_compact_block_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_compact_block_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_compact_block_copy(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_compact_block_const_t self_handle = (kth_compact_block_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_COMPACT_BLOCK);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_compact_block_copy(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_COMPACT_BLOCK, kth_py_native_chain_compact_block_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_compact_block_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_compact_block_destruct(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_compact_block_mut_t self_handle = (kth_compact_block_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_COMPACT_BLOCK);
    if (self_handle == NULL) return NULL;
    kth_chain_compact_block_destruct(self_handle);
    PyCapsule_SetName(py_self, "kth.destroyed");
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_compact_block_equals(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"other", NULL};
    PyObject* py_self = NULL;
    PyObject* py_other = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_other)) {
        return NULL;
    }
    kth_compact_block_const_t self_handle = (kth_compact_block_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_COMPACT_BLOCK);
    if (self_handle == NULL) return NULL;
    kth_compact_block_const_t other_handle = (kth_compact_block_const_t)PyCapsule_GetPointer(py_other, KTH_PY_CAPSULE_CHAIN_COMPACT_BLOCK);
    if (other_handle == NULL) return NULL;
    auto const result = kth_chain_compact_block_equals(self_handle, other_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_compact_block_header(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_compact_block_const_t self_handle = (kth_compact_block_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_COMPACT_BLOCK);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_compact_block_header(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_HEADER, kth_py_native_borrowed_parent_dtor);
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
kth_py_native_chain_compact_block_set_header(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    PyObject* py_value = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_value)) {
        return NULL;
    }
    kth_compact_block_mut_t self_handle = (kth_compact_block_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_COMPACT_BLOCK);
    if (self_handle == NULL) return NULL;
    kth_header_const_t value_handle = (kth_header_const_t)PyCapsule_GetPointer(py_value, KTH_PY_CAPSULE_CHAIN_HEADER);
    if (value_handle == NULL) return NULL;
    kth_chain_compact_block_set_header(self_handle, value_handle);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_compact_block_nonce(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_compact_block_const_t self_handle = (kth_compact_block_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_COMPACT_BLOCK);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_compact_block_nonce(self_handle);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyObject*
kth_py_native_chain_compact_block_set_nonce(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    unsigned long long value = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OK", kwlist, &py_self, &value)) {
        return NULL;
    }
    kth_compact_block_mut_t self_handle = (kth_compact_block_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_COMPACT_BLOCK);
    if (self_handle == NULL) return NULL;
    kth_chain_compact_block_set_nonce(self_handle, (uint64_t)value);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_compact_block_short_ids(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_compact_block_const_t self_handle = (kth_compact_block_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_COMPACT_BLOCK);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_compact_block_short_ids(self_handle);
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
kth_py_native_chain_compact_block_set_short_ids(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    PyObject* py_value = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_value)) {
        return NULL;
    }
    kth_compact_block_mut_t self_handle = (kth_compact_block_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_COMPACT_BLOCK);
    if (self_handle == NULL) return NULL;
    kth_u64_list_const_t value_handle = (kth_u64_list_const_t)PyCapsule_GetPointer(py_value, KTH_PY_CAPSULE_CORE_U64_LIST);
    if (value_handle == NULL) return NULL;
    kth_chain_compact_block_set_short_ids(self_handle, value_handle);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_compact_block_transactions(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_compact_block_const_t self_handle = (kth_compact_block_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_COMPACT_BLOCK);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_compact_block_transactions(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL list returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_PREFILLED_TRANSACTION_LIST, kth_py_native_borrowed_parent_dtor);
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
kth_py_native_chain_compact_block_set_transactions(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    PyObject* py_value = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_value)) {
        return NULL;
    }
    kth_compact_block_mut_t self_handle = (kth_compact_block_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_COMPACT_BLOCK);
    if (self_handle == NULL) return NULL;
    kth_prefilled_transaction_list_const_t value_handle = (kth_prefilled_transaction_list_const_t)PyCapsule_GetPointer(py_value, KTH_PY_CAPSULE_CHAIN_PREFILLED_TRANSACTION_LIST);
    if (value_handle == NULL) return NULL;
    kth_chain_compact_block_set_transactions(self_handle, value_handle);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_compact_block_to_data(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"version", NULL};
    PyObject* py_self = NULL;
    unsigned int version = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OI", kwlist, &py_self, &version)) {
        return NULL;
    }
    kth_compact_block_const_t self_handle = (kth_compact_block_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_COMPACT_BLOCK);
    if (self_handle == NULL) return NULL;
    kth_size_t out_size = 0;
    auto const result = kth_chain_compact_block_to_data(self_handle, (uint32_t)version, &out_size);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: serialization failed");
        return NULL;
    }
    PyObject* py_result = Py_BuildValue("y#", result, (Py_ssize_t)out_size);
    kth_core_destruct_array(result);
    return py_result;
}

PyObject*
kth_py_native_chain_compact_block_is_valid(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_compact_block_const_t self_handle = (kth_compact_block_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_COMPACT_BLOCK);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_compact_block_is_valid(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_compact_block_reset(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_compact_block_mut_t self_handle = (kth_compact_block_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_COMPACT_BLOCK);
    if (self_handle == NULL) return NULL;
    kth_chain_compact_block_reset(self_handle);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_compact_block_serialized_size(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"version", NULL};
    PyObject* py_self = NULL;
    unsigned int version = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OI", kwlist, &py_self, &version)) {
        return NULL;
    }
    kth_compact_block_const_t self_handle = (kth_compact_block_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_COMPACT_BLOCK);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_compact_block_serialized_size(self_handle, (uint32_t)version);
    return PyLong_FromSize_t((size_t)result);
}

PyMethodDef kth_py_native_chain_compact_block_methods[] = {
    {"chain_compact_block_construct_default", (PyCFunction)kth_py_native_chain_compact_block_construct_default, METH_NOARGS, NULL},
    {"chain_compact_block_construct_from_data", (PyCFunction)kth_py_native_chain_compact_block_construct_from_data, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_compact_block_construct", (PyCFunction)kth_py_native_chain_compact_block_construct, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_compact_block_copy", (PyCFunction)kth_py_native_chain_compact_block_copy, METH_O, NULL},
    {"chain_compact_block_destruct", (PyCFunction)kth_py_native_chain_compact_block_destruct, METH_O, NULL},
    {"chain_compact_block_equals", (PyCFunction)kth_py_native_chain_compact_block_equals, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_compact_block_header", (PyCFunction)kth_py_native_chain_compact_block_header, METH_O, NULL},
    {"chain_compact_block_set_header", (PyCFunction)kth_py_native_chain_compact_block_set_header, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_compact_block_nonce", (PyCFunction)kth_py_native_chain_compact_block_nonce, METH_O, NULL},
    {"chain_compact_block_set_nonce", (PyCFunction)kth_py_native_chain_compact_block_set_nonce, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_compact_block_short_ids", (PyCFunction)kth_py_native_chain_compact_block_short_ids, METH_O, NULL},
    {"chain_compact_block_set_short_ids", (PyCFunction)kth_py_native_chain_compact_block_set_short_ids, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_compact_block_transactions", (PyCFunction)kth_py_native_chain_compact_block_transactions, METH_O, NULL},
    {"chain_compact_block_set_transactions", (PyCFunction)kth_py_native_chain_compact_block_set_transactions, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_compact_block_to_data", (PyCFunction)kth_py_native_chain_compact_block_to_data, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_compact_block_is_valid", (PyCFunction)kth_py_native_chain_compact_block_is_valid, METH_O, NULL},
    {"chain_compact_block_reset", (PyCFunction)kth_py_native_chain_compact_block_reset, METH_O, NULL},
    {"chain_compact_block_serialized_size", (PyCFunction)kth_py_native_chain_compact_block_serialized_size, METH_VARARGS | METH_KEYWORDS, NULL},
    {NULL, NULL, 0, NULL}  // sentinel
};

#ifdef __cplusplus
} // extern "C"
#endif
