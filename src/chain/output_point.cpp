// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/py-native/chain/output_point.h>

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
void kth_py_native_chain_output_point_capsule_dtor(PyObject* capsule) {
    if ( ! PyCapsule_IsValid(capsule, KTH_PY_CAPSULE_CHAIN_OUTPUT_POINT)) return;
    kth_output_point_mut_t handle = (kth_output_point_mut_t)PyCapsule_GetPointer(capsule, KTH_PY_CAPSULE_CHAIN_OUTPUT_POINT);
    if (handle != NULL) kth_chain_output_point_destruct(handle);
}

PyObject*
kth_py_native_chain_output_point_construct_default(PyObject* self, PyObject* Py_UNUSED(args)) {
    auto result = kth_chain_output_point_construct_default();
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    return PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_OUTPUT_POINT, kth_py_native_chain_output_point_capsule_dtor);
}

PyObject*
kth_py_native_chain_output_point_construct_from_data(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"reader", (char*)"wire", NULL};
    char const* reader_buf = NULL;
    Py_ssize_t reader_size = 0;
    int wire = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "y#p", kwlist, &reader_buf, &reader_size, &wire)) {
        return NULL;
    }
    kth_output_point_mut_t out = NULL;
    kth_error_code_t result = kth_chain_output_point_construct_from_data((uint8_t const*)reader_buf, (kth_size_t)reader_size, (kth_bool_t)wire, &out);
    if (result != kth_ec_success) {
        PyErr_Format(PyExc_RuntimeError, "kth error code %d", (int)result);
        return NULL;
    }
    return PyCapsule_New((void*)out, KTH_PY_CAPSULE_CHAIN_OUTPUT_POINT, kth_py_native_chain_output_point_capsule_dtor);
}

PyObject*
kth_py_native_chain_output_point_construct_from_hash_index(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"hash", (char*)"index", NULL};
    char const* hash_buf = NULL;
    Py_ssize_t hash_size = 0;
    unsigned int index = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "y#I", kwlist, &hash_buf, &hash_size, &index)) {
        return NULL;
    }
    if (hash_size != (Py_ssize_t)KTH_BITCOIN_HASH_SIZE) {
        PyErr_Format(PyExc_ValueError, "expected %d-byte hash, got %zd", (int)KTH_BITCOIN_HASH_SIZE, hash_size);
        return NULL;
    }
    kth_hash_t hash;
    memcpy(hash.hash, hash_buf, (size_t)KTH_BITCOIN_HASH_SIZE);
    auto result = kth_chain_output_point_construct_from_hash_index(hash, (uint32_t)index);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    return PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_OUTPUT_POINT, kth_py_native_chain_output_point_capsule_dtor);
}

PyObject*
kth_py_native_chain_output_point_construct_from_point(PyObject* self, PyObject* py_arg0) {
    PyObject* py_x = py_arg0;
    kth_point_const_t x_handle = (kth_point_const_t)PyCapsule_GetPointer(py_x, KTH_PY_CAPSULE_CHAIN_POINT);
    if (x_handle == NULL) return NULL;
    auto result = kth_chain_output_point_construct_from_point(x_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    return PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_OUTPUT_POINT, kth_py_native_chain_output_point_capsule_dtor);
}

PyObject*
kth_py_native_chain_output_point_copy(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_output_point_const_t self_handle = (kth_output_point_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_OUTPUT_POINT);
    if (self_handle == NULL) return NULL;
    auto result = kth_chain_output_point_copy(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    return PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_OUTPUT_POINT, kth_py_native_chain_output_point_capsule_dtor);
}

PyObject*
kth_py_native_chain_output_point_destruct(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_output_point_mut_t self_handle = (kth_output_point_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_OUTPUT_POINT);
    if (self_handle == NULL) return NULL;
    kth_chain_output_point_destruct(self_handle);
    PyCapsule_SetName(py_self, "kth.destroyed");
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_output_point_equals(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"other", NULL};
    PyObject* py_self = NULL;
    PyObject* py_other = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_other)) {
        return NULL;
    }
    kth_output_point_const_t self_handle = (kth_output_point_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_OUTPUT_POINT);
    if (self_handle == NULL) return NULL;
    kth_output_point_const_t other_handle = (kth_output_point_const_t)PyCapsule_GetPointer(py_other, KTH_PY_CAPSULE_CHAIN_OUTPUT_POINT);
    if (other_handle == NULL) return NULL;
    auto result = kth_chain_output_point_equals(self_handle, other_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_output_point_is_mature(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"height", NULL};
    PyObject* py_self = NULL;
    Py_ssize_t height = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "On", kwlist, &py_self, &height)) {
        return NULL;
    }
    kth_output_point_const_t self_handle = (kth_output_point_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_OUTPUT_POINT);
    if (self_handle == NULL) return NULL;
    if (height < 0) {
        PyErr_Format(PyExc_ValueError, "height must be non-negative, got %zd", height);
        return NULL;
    }
    auto result = kth_chain_output_point_is_mature(self_handle, (kth_size_t)height);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_output_point_is_valid(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_output_point_const_t self_handle = (kth_output_point_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_OUTPUT_POINT);
    if (self_handle == NULL) return NULL;
    auto result = kth_chain_output_point_is_valid(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_output_point_to_data(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"wire", NULL};
    PyObject* py_self = NULL;
    int wire = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Op", kwlist, &py_self, &wire)) {
        return NULL;
    }
    kth_output_point_const_t self_handle = (kth_output_point_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_OUTPUT_POINT);
    if (self_handle == NULL) return NULL;
    kth_size_t out_size = 0;
    auto result = kth_chain_output_point_to_data(self_handle, (kth_bool_t)wire, &out_size);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: serialization failed");
        return NULL;
    }
    PyObject* py_result = Py_BuildValue("y#", result, (Py_ssize_t)out_size);
    kth_core_destruct_array(result);
    return py_result;
}

PyObject*
kth_py_native_chain_output_point_satoshi_fixed_size(PyObject* self, PyObject* Py_UNUSED(args)) {
    auto result = kth_chain_output_point_satoshi_fixed_size();
    return PyLong_FromSize_t((size_t)result);
}

PyObject*
kth_py_native_chain_output_point_serialized_size(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"wire", NULL};
    PyObject* py_self = NULL;
    int wire = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Op", kwlist, &py_self, &wire)) {
        return NULL;
    }
    kth_output_point_const_t self_handle = (kth_output_point_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_OUTPUT_POINT);
    if (self_handle == NULL) return NULL;
    auto result = kth_chain_output_point_serialized_size(self_handle, (kth_bool_t)wire);
    return PyLong_FromSize_t((size_t)result);
}

PyObject*
kth_py_native_chain_output_point_hash(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_output_point_const_t self_handle = (kth_output_point_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_OUTPUT_POINT);
    if (self_handle == NULL) return NULL;
    auto result = kth_chain_output_point_hash(self_handle);
    return Py_BuildValue("y#", result.hash, (Py_ssize_t)KTH_BITCOIN_HASH_SIZE);
}

PyObject*
kth_py_native_chain_output_point_set_hash(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    char const* value_buf = NULL;
    Py_ssize_t value_size = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Oy#", kwlist, &py_self, &value_buf, &value_size)) {
        return NULL;
    }
    kth_output_point_mut_t self_handle = (kth_output_point_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_OUTPUT_POINT);
    if (self_handle == NULL) return NULL;
    if (value_size != (Py_ssize_t)KTH_BITCOIN_HASH_SIZE) {
        PyErr_Format(PyExc_ValueError, "expected %d-byte value, got %zd", (int)KTH_BITCOIN_HASH_SIZE, value_size);
        return NULL;
    }
    kth_hash_t value;
    memcpy(value.hash, value_buf, (size_t)KTH_BITCOIN_HASH_SIZE);
    kth_chain_output_point_set_hash(self_handle, value);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_output_point_index(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_output_point_const_t self_handle = (kth_output_point_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_OUTPUT_POINT);
    if (self_handle == NULL) return NULL;
    auto result = kth_chain_output_point_index(self_handle);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyObject*
kth_py_native_chain_output_point_set_index(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    unsigned int value = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OI", kwlist, &py_self, &value)) {
        return NULL;
    }
    kth_output_point_mut_t self_handle = (kth_output_point_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_OUTPUT_POINT);
    if (self_handle == NULL) return NULL;
    kth_chain_output_point_set_index(self_handle, (uint32_t)value);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_output_point_checksum(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_output_point_const_t self_handle = (kth_output_point_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_OUTPUT_POINT);
    if (self_handle == NULL) return NULL;
    auto result = kth_chain_output_point_checksum(self_handle);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyObject*
kth_py_native_chain_output_point_is_null(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_output_point_const_t self_handle = (kth_output_point_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_OUTPUT_POINT);
    if (self_handle == NULL) return NULL;
    auto result = kth_chain_output_point_is_null(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_output_point_reset(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_output_point_mut_t self_handle = (kth_output_point_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_OUTPUT_POINT);
    if (self_handle == NULL) return NULL;
    kth_chain_output_point_reset(self_handle);
    Py_RETURN_NONE;
}

PyMethodDef kth_py_native_chain_output_point_methods[] = {
    {"chain_output_point_construct_default", (PyCFunction)kth_py_native_chain_output_point_construct_default, METH_NOARGS, NULL},
    {"chain_output_point_construct_from_data", (PyCFunction)kth_py_native_chain_output_point_construct_from_data, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_output_point_construct_from_hash_index", (PyCFunction)kth_py_native_chain_output_point_construct_from_hash_index, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_output_point_construct_from_point", (PyCFunction)kth_py_native_chain_output_point_construct_from_point, METH_O, NULL},
    {"chain_output_point_copy", (PyCFunction)kth_py_native_chain_output_point_copy, METH_O, NULL},
    {"chain_output_point_destruct", (PyCFunction)kth_py_native_chain_output_point_destruct, METH_O, NULL},
    {"chain_output_point_equals", (PyCFunction)kth_py_native_chain_output_point_equals, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_output_point_is_mature", (PyCFunction)kth_py_native_chain_output_point_is_mature, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_output_point_is_valid", (PyCFunction)kth_py_native_chain_output_point_is_valid, METH_O, NULL},
    {"chain_output_point_to_data", (PyCFunction)kth_py_native_chain_output_point_to_data, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_output_point_satoshi_fixed_size", (PyCFunction)kth_py_native_chain_output_point_satoshi_fixed_size, METH_NOARGS, NULL},
    {"chain_output_point_serialized_size", (PyCFunction)kth_py_native_chain_output_point_serialized_size, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_output_point_hash", (PyCFunction)kth_py_native_chain_output_point_hash, METH_O, NULL},
    {"chain_output_point_set_hash", (PyCFunction)kth_py_native_chain_output_point_set_hash, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_output_point_index", (PyCFunction)kth_py_native_chain_output_point_index, METH_O, NULL},
    {"chain_output_point_set_index", (PyCFunction)kth_py_native_chain_output_point_set_index, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_output_point_checksum", (PyCFunction)kth_py_native_chain_output_point_checksum, METH_O, NULL},
    {"chain_output_point_is_null", (PyCFunction)kth_py_native_chain_output_point_is_null, METH_O, NULL},
    {"chain_output_point_reset", (PyCFunction)kth_py_native_chain_output_point_reset, METH_O, NULL},
    {NULL, NULL, 0, NULL}  // sentinel
};

#ifdef __cplusplus
} // extern "C"
#endif
