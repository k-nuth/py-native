// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/py-native/chain/get_blocks.h>

#include <string.h>
#include <kth/capi.h>
#include <kth/capi/chain/get_blocks.h>
#include <kth/py-native/capsule_names.h>
#include <kth/py-native/utils.h>

#ifdef __cplusplus
extern "C" {
#endif

// PyCapsule destructor — released by GC when the capsule is
// collected. Explicit `destruct` calls set the capsule name to
// "kth.destroyed", so PyCapsule_IsValid returns false and this
// destructor becomes a no-op (no double-free).
void kth_py_native_chain_get_blocks_capsule_dtor(PyObject* capsule) {
    if ( ! PyCapsule_IsValid(capsule, KTH_PY_CAPSULE_CHAIN_GET_BLOCKS)) return;
    kth_get_blocks_mut_t handle = (kth_get_blocks_mut_t)PyCapsule_GetPointer(capsule, KTH_PY_CAPSULE_CHAIN_GET_BLOCKS);
    if (handle != NULL) kth_chain_get_blocks_destruct(handle);
}

PyObject*
kth_py_native_chain_get_blocks_construct_default(PyObject* self, PyObject* Py_UNUSED(args)) {
    auto const result = kth_chain_get_blocks_construct_default();
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_GET_BLOCKS, kth_py_native_chain_get_blocks_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_get_blocks_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_get_blocks_construct_from_data(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"reader", (char*)"version", NULL};
    char const* reader_buf = NULL;
    Py_ssize_t reader_size = 0;
    unsigned int version = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "y#I", kwlist, &reader_buf, &reader_size, &version)) {
        return NULL;
    }
    kth_get_blocks_mut_t out = NULL;
    kth_error_code_t result = kth_chain_get_blocks_construct_from_data((uint8_t const*)reader_buf, (kth_size_t)reader_size, (uint32_t)version, &out);
    if (result != kth_ec_success) {
        PyErr_Format(PyExc_RuntimeError, "kth error code %d", (int)result);
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)out, KTH_PY_CAPSULE_CHAIN_GET_BLOCKS, kth_py_native_chain_get_blocks_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_get_blocks_destruct(out);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_get_blocks_construct(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"start", (char*)"stop", NULL};
    PyObject* py_start = NULL;
    char const* stop_buf = NULL;
    Py_ssize_t stop_size = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Oy#", kwlist, &py_start, &stop_buf, &stop_size)) {
        return NULL;
    }
    kth_hash_list_const_t start_handle = (kth_hash_list_const_t)PyCapsule_GetPointer(py_start, KTH_PY_CAPSULE_CORE_HASH_LIST);
    if (start_handle == NULL) return NULL;
    if (stop_size != (Py_ssize_t)KTH_BITCOIN_HASH_SIZE) {
        PyErr_Format(PyExc_ValueError, "expected %d-byte stop, got %zd", (int)KTH_BITCOIN_HASH_SIZE, stop_size);
        return NULL;
    }
    kth_hash_t stop;
    memcpy(stop.hash, stop_buf, (size_t)KTH_BITCOIN_HASH_SIZE);
    auto const result = kth_chain_get_blocks_construct(start_handle, &stop);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_GET_BLOCKS, kth_py_native_chain_get_blocks_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_get_blocks_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_get_blocks_copy(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_get_blocks_const_t self_handle = (kth_get_blocks_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_GET_BLOCKS);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_get_blocks_copy(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_GET_BLOCKS, kth_py_native_chain_get_blocks_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_get_blocks_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_get_blocks_destruct(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_get_blocks_mut_t self_handle = (kth_get_blocks_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_GET_BLOCKS);
    if (self_handle == NULL) return NULL;
    kth_chain_get_blocks_destruct(self_handle);
    PyCapsule_SetName(py_self, "kth.destroyed");
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_get_blocks_equals(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"other", NULL};
    PyObject* py_self = NULL;
    PyObject* py_other = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_other)) {
        return NULL;
    }
    kth_get_blocks_const_t self_handle = (kth_get_blocks_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_GET_BLOCKS);
    if (self_handle == NULL) return NULL;
    kth_get_blocks_const_t other_handle = (kth_get_blocks_const_t)PyCapsule_GetPointer(py_other, KTH_PY_CAPSULE_CHAIN_GET_BLOCKS);
    if (other_handle == NULL) return NULL;
    auto const result = kth_chain_get_blocks_equals(self_handle, other_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_get_blocks_start_hashes(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_get_blocks_const_t self_handle = (kth_get_blocks_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_GET_BLOCKS);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_get_blocks_start_hashes(self_handle);
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
kth_py_native_chain_get_blocks_set_start_hashes(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    PyObject* py_value = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_value)) {
        return NULL;
    }
    kth_get_blocks_mut_t self_handle = (kth_get_blocks_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_GET_BLOCKS);
    if (self_handle == NULL) return NULL;
    kth_hash_list_const_t value_handle = (kth_hash_list_const_t)PyCapsule_GetPointer(py_value, KTH_PY_CAPSULE_CORE_HASH_LIST);
    if (value_handle == NULL) return NULL;
    kth_chain_get_blocks_set_start_hashes(self_handle, value_handle);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_get_blocks_stop_hash(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_get_blocks_const_t self_handle = (kth_get_blocks_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_GET_BLOCKS);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_get_blocks_stop_hash(self_handle);
    return Py_BuildValue("y#", result.hash, (Py_ssize_t)KTH_BITCOIN_HASH_SIZE);
}

PyObject*
kth_py_native_chain_get_blocks_set_stop_hash(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    char const* value_buf = NULL;
    Py_ssize_t value_size = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Oy#", kwlist, &py_self, &value_buf, &value_size)) {
        return NULL;
    }
    kth_get_blocks_mut_t self_handle = (kth_get_blocks_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_GET_BLOCKS);
    if (self_handle == NULL) return NULL;
    if (value_size != (Py_ssize_t)KTH_BITCOIN_HASH_SIZE) {
        PyErr_Format(PyExc_ValueError, "expected %d-byte value, got %zd", (int)KTH_BITCOIN_HASH_SIZE, value_size);
        return NULL;
    }
    kth_hash_t value;
    memcpy(value.hash, value_buf, (size_t)KTH_BITCOIN_HASH_SIZE);
    kth_chain_get_blocks_set_stop_hash(self_handle, &value);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_get_blocks_to_data(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"version", NULL};
    PyObject* py_self = NULL;
    unsigned int version = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OI", kwlist, &py_self, &version)) {
        return NULL;
    }
    kth_get_blocks_const_t self_handle = (kth_get_blocks_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_GET_BLOCKS);
    if (self_handle == NULL) return NULL;
    kth_size_t out_size = 0;
    auto const result = kth_chain_get_blocks_to_data(self_handle, (uint32_t)version, &out_size);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: serialization failed");
        return NULL;
    }
    PyObject* py_result = Py_BuildValue("y#", result, (Py_ssize_t)out_size);
    kth_core_destruct_array(result);
    return py_result;
}

PyObject*
kth_py_native_chain_get_blocks_is_valid(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_get_blocks_const_t self_handle = (kth_get_blocks_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_GET_BLOCKS);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_get_blocks_is_valid(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_get_blocks_reset(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_get_blocks_mut_t self_handle = (kth_get_blocks_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_GET_BLOCKS);
    if (self_handle == NULL) return NULL;
    kth_chain_get_blocks_reset(self_handle);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_get_blocks_serialized_size(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"version", NULL};
    PyObject* py_self = NULL;
    unsigned int version = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OI", kwlist, &py_self, &version)) {
        return NULL;
    }
    kth_get_blocks_const_t self_handle = (kth_get_blocks_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_GET_BLOCKS);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_get_blocks_serialized_size(self_handle, (uint32_t)version);
    return PyLong_FromSize_t((size_t)result);
}

PyMethodDef kth_py_native_chain_get_blocks_methods[] = {
    {"chain_get_blocks_construct_default", (PyCFunction)kth_py_native_chain_get_blocks_construct_default, METH_NOARGS, NULL},
    {"chain_get_blocks_construct_from_data", (PyCFunction)kth_py_native_chain_get_blocks_construct_from_data, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_get_blocks_construct", (PyCFunction)kth_py_native_chain_get_blocks_construct, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_get_blocks_copy", (PyCFunction)kth_py_native_chain_get_blocks_copy, METH_O, NULL},
    {"chain_get_blocks_destruct", (PyCFunction)kth_py_native_chain_get_blocks_destruct, METH_O, NULL},
    {"chain_get_blocks_equals", (PyCFunction)kth_py_native_chain_get_blocks_equals, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_get_blocks_start_hashes", (PyCFunction)kth_py_native_chain_get_blocks_start_hashes, METH_O, NULL},
    {"chain_get_blocks_set_start_hashes", (PyCFunction)kth_py_native_chain_get_blocks_set_start_hashes, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_get_blocks_stop_hash", (PyCFunction)kth_py_native_chain_get_blocks_stop_hash, METH_O, NULL},
    {"chain_get_blocks_set_stop_hash", (PyCFunction)kth_py_native_chain_get_blocks_set_stop_hash, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_get_blocks_to_data", (PyCFunction)kth_py_native_chain_get_blocks_to_data, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_get_blocks_is_valid", (PyCFunction)kth_py_native_chain_get_blocks_is_valid, METH_O, NULL},
    {"chain_get_blocks_reset", (PyCFunction)kth_py_native_chain_get_blocks_reset, METH_O, NULL},
    {"chain_get_blocks_serialized_size", (PyCFunction)kth_py_native_chain_get_blocks_serialized_size, METH_VARARGS | METH_KEYWORDS, NULL},
    {NULL, NULL, 0, NULL}  // sentinel
};

#ifdef __cplusplus
} // extern "C"
#endif
