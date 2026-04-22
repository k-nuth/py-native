// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/py-native/chain/merkle_block.h>

#include <string.h>
#include <kth/capi.h>
#include <kth/capi/chain/merkle_block.h>
#include <kth/py-native/capsule_names.h>
#include <kth/py-native/utils.h>

#ifdef __cplusplus
extern "C" {
#endif

// PyCapsule destructor — released by GC when the capsule is
// collected. Explicit `destruct` calls set the capsule name to
// "kth.destroyed", so PyCapsule_IsValid returns false and this
// destructor becomes a no-op (no double-free).
void kth_py_native_chain_merkle_block_capsule_dtor(PyObject* capsule) {
    if ( ! PyCapsule_IsValid(capsule, KTH_PY_CAPSULE_CHAIN_MERKLE_BLOCK)) return;
    kth_merkle_block_mut_t handle = (kth_merkle_block_mut_t)PyCapsule_GetPointer(capsule, KTH_PY_CAPSULE_CHAIN_MERKLE_BLOCK);
    if (handle != NULL) kth_chain_merkle_block_destruct(handle);
}

PyObject*
kth_py_native_chain_merkle_block_construct_default(PyObject* self, PyObject* Py_UNUSED(args)) {
    auto const result = kth_chain_merkle_block_construct_default();
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_MERKLE_BLOCK, kth_py_native_chain_merkle_block_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_merkle_block_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_merkle_block_construct_from_data(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"reader", (char*)"version", NULL};
    char const* reader_buf = NULL;
    Py_ssize_t reader_size = 0;
    unsigned int version = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "y#I", kwlist, &reader_buf, &reader_size, &version)) {
        return NULL;
    }
    kth_merkle_block_mut_t out = NULL;
    kth_error_code_t result = kth_chain_merkle_block_construct_from_data((uint8_t const*)reader_buf, (kth_size_t)reader_size, (uint32_t)version, &out);
    if (result != kth_ec_success) {
        PyErr_Format(PyExc_RuntimeError, "kth error code %d", (int)result);
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)out, KTH_PY_CAPSULE_CHAIN_MERKLE_BLOCK, kth_py_native_chain_merkle_block_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_merkle_block_destruct(out);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_merkle_block_construct_from_header_total_transactions_hashes_flags(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"header", (char*)"total_transactions", (char*)"hashes", (char*)"flags", NULL};
    PyObject* py_header = NULL;
    Py_ssize_t total_transactions = 0;
    PyObject* py_hashes = NULL;
    char const* flags_buf = NULL;
    Py_ssize_t flags_size = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OnOy#", kwlist, &py_header, &total_transactions, &py_hashes, &flags_buf, &flags_size)) {
        return NULL;
    }
    kth_header_const_t header_handle = (kth_header_const_t)PyCapsule_GetPointer(py_header, KTH_PY_CAPSULE_CHAIN_HEADER);
    if (header_handle == NULL) return NULL;
    if (total_transactions < 0) {
        PyErr_Format(PyExc_ValueError, "total_transactions must be non-negative, got %zd", total_transactions);
        return NULL;
    }
    kth_hash_list_const_t hashes_handle = (kth_hash_list_const_t)PyCapsule_GetPointer(py_hashes, KTH_PY_CAPSULE_CORE_HASH_LIST);
    if (hashes_handle == NULL) return NULL;
    auto const result = kth_chain_merkle_block_construct_from_header_total_transactions_hashes_flags(header_handle, (kth_size_t)total_transactions, hashes_handle, (uint8_t const*)flags_buf, (kth_size_t)flags_size);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_MERKLE_BLOCK, kth_py_native_chain_merkle_block_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_merkle_block_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_merkle_block_construct_from_block(PyObject* self, PyObject* py_arg0) {
    PyObject* py_block = py_arg0;
    kth_block_const_t block_handle = (kth_block_const_t)PyCapsule_GetPointer(py_block, KTH_PY_CAPSULE_CHAIN_BLOCK);
    if (block_handle == NULL) return NULL;
    auto const result = kth_chain_merkle_block_construct_from_block(block_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_MERKLE_BLOCK, kth_py_native_chain_merkle_block_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_merkle_block_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_merkle_block_copy(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_merkle_block_const_t self_handle = (kth_merkle_block_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_MERKLE_BLOCK);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_merkle_block_copy(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_MERKLE_BLOCK, kth_py_native_chain_merkle_block_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_merkle_block_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_merkle_block_destruct(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_merkle_block_mut_t self_handle = (kth_merkle_block_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_MERKLE_BLOCK);
    if (self_handle == NULL) return NULL;
    kth_chain_merkle_block_destruct(self_handle);
    PyCapsule_SetName(py_self, "kth.destroyed");
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_merkle_block_equals(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"other", NULL};
    PyObject* py_self = NULL;
    PyObject* py_other = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_other)) {
        return NULL;
    }
    kth_merkle_block_const_t self_handle = (kth_merkle_block_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_MERKLE_BLOCK);
    if (self_handle == NULL) return NULL;
    kth_merkle_block_const_t other_handle = (kth_merkle_block_const_t)PyCapsule_GetPointer(py_other, KTH_PY_CAPSULE_CHAIN_MERKLE_BLOCK);
    if (other_handle == NULL) return NULL;
    auto const result = kth_chain_merkle_block_equals(self_handle, other_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_merkle_block_header(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_merkle_block_const_t self_handle = (kth_merkle_block_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_MERKLE_BLOCK);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_merkle_block_header(self_handle);
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
kth_py_native_chain_merkle_block_set_header(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    PyObject* py_value = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_value)) {
        return NULL;
    }
    kth_merkle_block_mut_t self_handle = (kth_merkle_block_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_MERKLE_BLOCK);
    if (self_handle == NULL) return NULL;
    kth_header_const_t value_handle = (kth_header_const_t)PyCapsule_GetPointer(py_value, KTH_PY_CAPSULE_CHAIN_HEADER);
    if (value_handle == NULL) return NULL;
    kth_chain_merkle_block_set_header(self_handle, value_handle);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_merkle_block_total_transactions(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_merkle_block_const_t self_handle = (kth_merkle_block_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_MERKLE_BLOCK);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_merkle_block_total_transactions(self_handle);
    return PyLong_FromSize_t((size_t)result);
}

PyObject*
kth_py_native_chain_merkle_block_set_total_transactions(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    Py_ssize_t value = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "On", kwlist, &py_self, &value)) {
        return NULL;
    }
    kth_merkle_block_mut_t self_handle = (kth_merkle_block_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_MERKLE_BLOCK);
    if (self_handle == NULL) return NULL;
    if (value < 0) {
        PyErr_Format(PyExc_ValueError, "value must be non-negative, got %zd", value);
        return NULL;
    }
    kth_chain_merkle_block_set_total_transactions(self_handle, (kth_size_t)value);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_merkle_block_hashes(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_merkle_block_const_t self_handle = (kth_merkle_block_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_MERKLE_BLOCK);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_merkle_block_hashes(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL list returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CORE_HASH_LIST, kth_py_native_borrowed_parent_dtor);
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
kth_py_native_chain_merkle_block_set_hashes(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    PyObject* py_value = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_value)) {
        return NULL;
    }
    kth_merkle_block_mut_t self_handle = (kth_merkle_block_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_MERKLE_BLOCK);
    if (self_handle == NULL) return NULL;
    kth_hash_list_const_t value_handle = (kth_hash_list_const_t)PyCapsule_GetPointer(py_value, KTH_PY_CAPSULE_CORE_HASH_LIST);
    if (value_handle == NULL) return NULL;
    kth_chain_merkle_block_set_hashes(self_handle, value_handle);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_merkle_block_flags(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_merkle_block_const_t self_handle = (kth_merkle_block_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_MERKLE_BLOCK);
    if (self_handle == NULL) return NULL;
    kth_size_t out_size = 0;
    auto const result = kth_chain_merkle_block_flags(self_handle, &out_size);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: serialization failed");
        return NULL;
    }
    PyObject* py_result = Py_BuildValue("y#", result, (Py_ssize_t)out_size);
    kth_core_destruct_array(result);
    return py_result;
}

PyObject*
kth_py_native_chain_merkle_block_set_flags(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    char const* value_buf = NULL;
    Py_ssize_t value_size = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Oy#", kwlist, &py_self, &value_buf, &value_size)) {
        return NULL;
    }
    kth_merkle_block_mut_t self_handle = (kth_merkle_block_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_MERKLE_BLOCK);
    if (self_handle == NULL) return NULL;
    kth_chain_merkle_block_set_flags(self_handle, (uint8_t const*)value_buf, (kth_size_t)value_size);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_merkle_block_to_data(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"version", NULL};
    PyObject* py_self = NULL;
    unsigned int version = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OI", kwlist, &py_self, &version)) {
        return NULL;
    }
    kth_merkle_block_const_t self_handle = (kth_merkle_block_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_MERKLE_BLOCK);
    if (self_handle == NULL) return NULL;
    kth_size_t out_size = 0;
    auto const result = kth_chain_merkle_block_to_data(self_handle, (uint32_t)version, &out_size);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: serialization failed");
        return NULL;
    }
    PyObject* py_result = Py_BuildValue("y#", result, (Py_ssize_t)out_size);
    kth_core_destruct_array(result);
    return py_result;
}

PyObject*
kth_py_native_chain_merkle_block_is_valid(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_merkle_block_const_t self_handle = (kth_merkle_block_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_MERKLE_BLOCK);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_merkle_block_is_valid(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_merkle_block_reset(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_merkle_block_mut_t self_handle = (kth_merkle_block_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_MERKLE_BLOCK);
    if (self_handle == NULL) return NULL;
    kth_chain_merkle_block_reset(self_handle);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_merkle_block_serialized_size(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"version", NULL};
    PyObject* py_self = NULL;
    unsigned int version = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OI", kwlist, &py_self, &version)) {
        return NULL;
    }
    kth_merkle_block_const_t self_handle = (kth_merkle_block_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_MERKLE_BLOCK);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_merkle_block_serialized_size(self_handle, (uint32_t)version);
    return PyLong_FromSize_t((size_t)result);
}

PyMethodDef kth_py_native_chain_merkle_block_methods[] = {
    {"chain_merkle_block_construct_default", (PyCFunction)kth_py_native_chain_merkle_block_construct_default, METH_NOARGS, NULL},
    {"chain_merkle_block_construct_from_data", (PyCFunction)kth_py_native_chain_merkle_block_construct_from_data, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_merkle_block_construct_from_header_total_transactions_hashes_flags", (PyCFunction)kth_py_native_chain_merkle_block_construct_from_header_total_transactions_hashes_flags, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_merkle_block_construct_from_block", (PyCFunction)kth_py_native_chain_merkle_block_construct_from_block, METH_O, NULL},
    {"chain_merkle_block_copy", (PyCFunction)kth_py_native_chain_merkle_block_copy, METH_O, NULL},
    {"chain_merkle_block_destruct", (PyCFunction)kth_py_native_chain_merkle_block_destruct, METH_O, NULL},
    {"chain_merkle_block_equals", (PyCFunction)kth_py_native_chain_merkle_block_equals, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_merkle_block_header", (PyCFunction)kth_py_native_chain_merkle_block_header, METH_O, NULL},
    {"chain_merkle_block_set_header", (PyCFunction)kth_py_native_chain_merkle_block_set_header, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_merkle_block_total_transactions", (PyCFunction)kth_py_native_chain_merkle_block_total_transactions, METH_O, NULL},
    {"chain_merkle_block_set_total_transactions", (PyCFunction)kth_py_native_chain_merkle_block_set_total_transactions, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_merkle_block_hashes", (PyCFunction)kth_py_native_chain_merkle_block_hashes, METH_O, NULL},
    {"chain_merkle_block_set_hashes", (PyCFunction)kth_py_native_chain_merkle_block_set_hashes, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_merkle_block_flags", (PyCFunction)kth_py_native_chain_merkle_block_flags, METH_O, NULL},
    {"chain_merkle_block_set_flags", (PyCFunction)kth_py_native_chain_merkle_block_set_flags, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_merkle_block_to_data", (PyCFunction)kth_py_native_chain_merkle_block_to_data, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_merkle_block_is_valid", (PyCFunction)kth_py_native_chain_merkle_block_is_valid, METH_O, NULL},
    {"chain_merkle_block_reset", (PyCFunction)kth_py_native_chain_merkle_block_reset, METH_O, NULL},
    {"chain_merkle_block_serialized_size", (PyCFunction)kth_py_native_chain_merkle_block_serialized_size, METH_VARARGS | METH_KEYWORDS, NULL},
    {NULL, NULL, 0, NULL}  // sentinel
};

#ifdef __cplusplus
} // extern "C"
#endif
