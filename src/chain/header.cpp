// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/py-native/chain/header.h>

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
void kth_py_native_chain_header_capsule_dtor(PyObject* capsule) {
    if ( ! PyCapsule_IsValid(capsule, KTH_PY_CAPSULE_CHAIN_HEADER)) return;
    kth_header_mut_t handle = (kth_header_mut_t)PyCapsule_GetPointer(capsule, KTH_PY_CAPSULE_CHAIN_HEADER);
    if (handle != NULL) kth_chain_header_destruct(handle);
}

PyObject*
kth_py_native_chain_header_construct_default(PyObject* self, PyObject* Py_UNUSED(args)) {
    auto const result = kth_chain_header_construct_default();
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_HEADER, kth_py_native_chain_header_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_header_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_header_construct_from_data(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"reader", (char*)"wire", NULL};
    char const* reader_buf = NULL;
    Py_ssize_t reader_size = 0;
    int wire = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "y#p", kwlist, &reader_buf, &reader_size, &wire)) {
        return NULL;
    }
    kth_header_mut_t out = NULL;
    kth_error_code_t result = kth_chain_header_construct_from_data((uint8_t const*)reader_buf, (kth_size_t)reader_size, (kth_bool_t)wire, &out);
    if (result != kth_ec_success) {
        PyErr_Format(PyExc_RuntimeError, "kth error code %d", (int)result);
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)out, KTH_PY_CAPSULE_CHAIN_HEADER, kth_py_native_chain_header_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_header_destruct(out);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_header_construct(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"version", (char*)"previous_block_hash", (char*)"merkle", (char*)"timestamp", (char*)"bits", (char*)"nonce", NULL};
    unsigned int version = 0;
    char const* previous_block_hash_buf = NULL;
    Py_ssize_t previous_block_hash_size = 0;
    char const* merkle_buf = NULL;
    Py_ssize_t merkle_size = 0;
    unsigned int timestamp = 0;
    unsigned int bits = 0;
    unsigned int nonce = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Iy#y#III", kwlist, &version, &previous_block_hash_buf, &previous_block_hash_size, &merkle_buf, &merkle_size, &timestamp, &bits, &nonce)) {
        return NULL;
    }
    if (previous_block_hash_size != (Py_ssize_t)KTH_BITCOIN_HASH_SIZE) {
        PyErr_Format(PyExc_ValueError, "expected %d-byte previous_block_hash, got %zd", (int)KTH_BITCOIN_HASH_SIZE, previous_block_hash_size);
        return NULL;
    }
    kth_hash_t previous_block_hash;
    memcpy(previous_block_hash.hash, previous_block_hash_buf, (size_t)KTH_BITCOIN_HASH_SIZE);
    if (merkle_size != (Py_ssize_t)KTH_BITCOIN_HASH_SIZE) {
        PyErr_Format(PyExc_ValueError, "expected %d-byte merkle, got %zd", (int)KTH_BITCOIN_HASH_SIZE, merkle_size);
        return NULL;
    }
    kth_hash_t merkle;
    memcpy(merkle.hash, merkle_buf, (size_t)KTH_BITCOIN_HASH_SIZE);
    auto const result = kth_chain_header_construct((uint32_t)version, &previous_block_hash, &merkle, (uint32_t)timestamp, (uint32_t)bits, (uint32_t)nonce);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_HEADER, kth_py_native_chain_header_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_header_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_header_copy(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_header_const_t self_handle = (kth_header_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_HEADER);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_header_copy(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_HEADER, kth_py_native_chain_header_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_header_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_header_destruct(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_header_mut_t self_handle = (kth_header_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_HEADER);
    if (self_handle == NULL) return NULL;
    kth_chain_header_destruct(self_handle);
    PyCapsule_SetName(py_self, "kth.destroyed");
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_header_to_data(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"wire", NULL};
    PyObject* py_self = NULL;
    int wire = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Op", kwlist, &py_self, &wire)) {
        return NULL;
    }
    kth_header_const_t self_handle = (kth_header_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_HEADER);
    if (self_handle == NULL) return NULL;
    kth_size_t out_size = 0;
    auto const result = kth_chain_header_to_data(self_handle, (kth_bool_t)wire, &out_size);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: serialization failed");
        return NULL;
    }
    PyObject* py_result = Py_BuildValue("y#", result, (Py_ssize_t)out_size);
    kth_core_destruct_array(result);
    return py_result;
}

PyObject*
kth_py_native_chain_header_serialized_size(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"wire", NULL};
    PyObject* py_self = NULL;
    int wire = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Op", kwlist, &py_self, &wire)) {
        return NULL;
    }
    kth_header_const_t self_handle = (kth_header_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_HEADER);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_header_serialized_size(self_handle, (kth_bool_t)wire);
    return PyLong_FromSize_t((size_t)result);
}

PyObject*
kth_py_native_chain_header_set_version(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    unsigned int value = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OI", kwlist, &py_self, &value)) {
        return NULL;
    }
    kth_header_mut_t self_handle = (kth_header_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_HEADER);
    if (self_handle == NULL) return NULL;
    kth_chain_header_set_version(self_handle, (uint32_t)value);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_header_set_previous_block_hash(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    char const* value_buf = NULL;
    Py_ssize_t value_size = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Oy#", kwlist, &py_self, &value_buf, &value_size)) {
        return NULL;
    }
    kth_header_mut_t self_handle = (kth_header_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_HEADER);
    if (self_handle == NULL) return NULL;
    if (value_size != (Py_ssize_t)KTH_BITCOIN_HASH_SIZE) {
        PyErr_Format(PyExc_ValueError, "expected %d-byte value, got %zd", (int)KTH_BITCOIN_HASH_SIZE, value_size);
        return NULL;
    }
    kth_hash_t value;
    memcpy(value.hash, value_buf, (size_t)KTH_BITCOIN_HASH_SIZE);
    kth_chain_header_set_previous_block_hash(self_handle, &value);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_header_set_merkle(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    char const* value_buf = NULL;
    Py_ssize_t value_size = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Oy#", kwlist, &py_self, &value_buf, &value_size)) {
        return NULL;
    }
    kth_header_mut_t self_handle = (kth_header_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_HEADER);
    if (self_handle == NULL) return NULL;
    if (value_size != (Py_ssize_t)KTH_BITCOIN_HASH_SIZE) {
        PyErr_Format(PyExc_ValueError, "expected %d-byte value, got %zd", (int)KTH_BITCOIN_HASH_SIZE, value_size);
        return NULL;
    }
    kth_hash_t value;
    memcpy(value.hash, value_buf, (size_t)KTH_BITCOIN_HASH_SIZE);
    kth_chain_header_set_merkle(self_handle, &value);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_header_set_timestamp(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    unsigned int value = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OI", kwlist, &py_self, &value)) {
        return NULL;
    }
    kth_header_mut_t self_handle = (kth_header_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_HEADER);
    if (self_handle == NULL) return NULL;
    kth_chain_header_set_timestamp(self_handle, (uint32_t)value);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_header_set_bits(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    unsigned int value = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OI", kwlist, &py_self, &value)) {
        return NULL;
    }
    kth_header_mut_t self_handle = (kth_header_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_HEADER);
    if (self_handle == NULL) return NULL;
    kth_chain_header_set_bits(self_handle, (uint32_t)value);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_header_set_nonce(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    unsigned int value = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OI", kwlist, &py_self, &value)) {
        return NULL;
    }
    kth_header_mut_t self_handle = (kth_header_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_HEADER);
    if (self_handle == NULL) return NULL;
    kth_chain_header_set_nonce(self_handle, (uint32_t)value);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_header_hash_pow(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_header_const_t self_handle = (kth_header_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_HEADER);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_header_hash_pow(self_handle);
    return Py_BuildValue("y#", result.hash, (Py_ssize_t)KTH_BITCOIN_HASH_SIZE);
}

PyObject*
kth_py_native_chain_header_is_valid_proof_of_work(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"retarget", NULL};
    PyObject* py_self = NULL;
    int retarget = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Op", kwlist, &py_self, &retarget)) {
        return NULL;
    }
    kth_header_const_t self_handle = (kth_header_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_HEADER);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_header_is_valid_proof_of_work(self_handle, (kth_bool_t)retarget);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_header_check(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"retarget", NULL};
    PyObject* py_self = NULL;
    int retarget = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Op", kwlist, &py_self, &retarget)) {
        return NULL;
    }
    kth_header_const_t self_handle = (kth_header_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_HEADER);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_header_check(self_handle, (kth_bool_t)retarget);
    return PyLong_FromLong((long)result);
}

PyObject*
kth_py_native_chain_header_accept(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"state", NULL};
    PyObject* py_self = NULL;
    PyObject* py_state = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_state)) {
        return NULL;
    }
    kth_header_const_t self_handle = (kth_header_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_HEADER);
    if (self_handle == NULL) return NULL;
    kth_chain_state_const_t state_handle = (kth_chain_state_const_t)PyCapsule_GetPointer(py_state, KTH_PY_CAPSULE_CHAIN_CHAIN_STATE);
    if (state_handle == NULL) return NULL;
    auto const result = kth_chain_header_accept(self_handle, state_handle);
    return PyLong_FromLong((long)result);
}

PyObject*
kth_py_native_chain_header_reset(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_header_mut_t self_handle = (kth_header_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_HEADER);
    if (self_handle == NULL) return NULL;
    kth_chain_header_reset(self_handle);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_header_equals(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"other", NULL};
    PyObject* py_self = NULL;
    PyObject* py_other = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_other)) {
        return NULL;
    }
    kth_header_const_t self_handle = (kth_header_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_HEADER);
    if (self_handle == NULL) return NULL;
    kth_header_const_t other_handle = (kth_header_const_t)PyCapsule_GetPointer(py_other, KTH_PY_CAPSULE_CHAIN_HEADER);
    if (other_handle == NULL) return NULL;
    auto const result = kth_chain_header_equals(self_handle, other_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_header_is_valid(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_header_const_t self_handle = (kth_header_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_HEADER);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_header_is_valid(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_header_satoshi_fixed_size(PyObject* self, PyObject* Py_UNUSED(args)) {
    auto const result = kth_chain_header_satoshi_fixed_size();
    return PyLong_FromSize_t((size_t)result);
}

PyObject*
kth_py_native_chain_header_version(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_header_const_t self_handle = (kth_header_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_HEADER);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_header_version(self_handle);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyObject*
kth_py_native_chain_header_previous_block_hash(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_header_const_t self_handle = (kth_header_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_HEADER);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_header_previous_block_hash(self_handle);
    return Py_BuildValue("y#", result.hash, (Py_ssize_t)KTH_BITCOIN_HASH_SIZE);
}

PyObject*
kth_py_native_chain_header_merkle(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_header_const_t self_handle = (kth_header_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_HEADER);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_header_merkle(self_handle);
    return Py_BuildValue("y#", result.hash, (Py_ssize_t)KTH_BITCOIN_HASH_SIZE);
}

PyObject*
kth_py_native_chain_header_timestamp(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_header_const_t self_handle = (kth_header_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_HEADER);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_header_timestamp(self_handle);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyObject*
kth_py_native_chain_header_bits(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_header_const_t self_handle = (kth_header_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_HEADER);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_header_bits(self_handle);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyObject*
kth_py_native_chain_header_nonce(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_header_const_t self_handle = (kth_header_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_HEADER);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_header_nonce(self_handle);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyObject*
kth_py_native_chain_header_is_valid_timestamp(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_header_const_t self_handle = (kth_header_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_HEADER);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_header_is_valid_timestamp(self_handle);
    return PyBool_FromLong((long)result);
}

PyMethodDef kth_py_native_chain_header_methods[] = {
    {"chain_header_construct_default", (PyCFunction)kth_py_native_chain_header_construct_default, METH_NOARGS, NULL},
    {"chain_header_construct_from_data", (PyCFunction)kth_py_native_chain_header_construct_from_data, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_header_construct", (PyCFunction)kth_py_native_chain_header_construct, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_header_copy", (PyCFunction)kth_py_native_chain_header_copy, METH_O, NULL},
    {"chain_header_destruct", (PyCFunction)kth_py_native_chain_header_destruct, METH_O, NULL},
    {"chain_header_to_data", (PyCFunction)kth_py_native_chain_header_to_data, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_header_serialized_size", (PyCFunction)kth_py_native_chain_header_serialized_size, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_header_set_version", (PyCFunction)kth_py_native_chain_header_set_version, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_header_set_previous_block_hash", (PyCFunction)kth_py_native_chain_header_set_previous_block_hash, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_header_set_merkle", (PyCFunction)kth_py_native_chain_header_set_merkle, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_header_set_timestamp", (PyCFunction)kth_py_native_chain_header_set_timestamp, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_header_set_bits", (PyCFunction)kth_py_native_chain_header_set_bits, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_header_set_nonce", (PyCFunction)kth_py_native_chain_header_set_nonce, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_header_hash_pow", (PyCFunction)kth_py_native_chain_header_hash_pow, METH_O, NULL},
    {"chain_header_is_valid_proof_of_work", (PyCFunction)kth_py_native_chain_header_is_valid_proof_of_work, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_header_check", (PyCFunction)kth_py_native_chain_header_check, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_header_accept", (PyCFunction)kth_py_native_chain_header_accept, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_header_reset", (PyCFunction)kth_py_native_chain_header_reset, METH_O, NULL},
    {"chain_header_equals", (PyCFunction)kth_py_native_chain_header_equals, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_header_is_valid", (PyCFunction)kth_py_native_chain_header_is_valid, METH_O, NULL},
    {"chain_header_satoshi_fixed_size", (PyCFunction)kth_py_native_chain_header_satoshi_fixed_size, METH_NOARGS, NULL},
    {"chain_header_version", (PyCFunction)kth_py_native_chain_header_version, METH_O, NULL},
    {"chain_header_previous_block_hash", (PyCFunction)kth_py_native_chain_header_previous_block_hash, METH_O, NULL},
    {"chain_header_merkle", (PyCFunction)kth_py_native_chain_header_merkle, METH_O, NULL},
    {"chain_header_timestamp", (PyCFunction)kth_py_native_chain_header_timestamp, METH_O, NULL},
    {"chain_header_bits", (PyCFunction)kth_py_native_chain_header_bits, METH_O, NULL},
    {"chain_header_nonce", (PyCFunction)kth_py_native_chain_header_nonce, METH_O, NULL},
    {"chain_header_is_valid_timestamp", (PyCFunction)kth_py_native_chain_header_is_valid_timestamp, METH_O, NULL},
    {NULL, NULL, 0, NULL}  // sentinel
};

#ifdef __cplusplus
} // extern "C"
#endif
