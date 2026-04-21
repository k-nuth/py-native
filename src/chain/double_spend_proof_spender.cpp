// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/py-native/chain/double_spend_proof_spender.h>

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
void kth_py_native_chain_double_spend_proof_spender_capsule_dtor(PyObject* capsule) {
    if ( ! PyCapsule_IsValid(capsule, KTH_PY_CAPSULE_CHAIN_DOUBLE_SPEND_PROOF_SPENDER)) return;
    kth_double_spend_proof_spender_mut_t handle = (kth_double_spend_proof_spender_mut_t)PyCapsule_GetPointer(capsule, KTH_PY_CAPSULE_CHAIN_DOUBLE_SPEND_PROOF_SPENDER);
    if (handle != NULL) kth_chain_double_spend_proof_spender_destruct(handle);
}

PyObject*
kth_py_native_chain_double_spend_proof_spender_construct_from_data(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"reader", (char*)"version", NULL};
    char const* reader_buf = NULL;
    Py_ssize_t reader_size = 0;
    unsigned int version = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "y#I", kwlist, &reader_buf, &reader_size, &version)) {
        return NULL;
    }
    kth_double_spend_proof_spender_mut_t out = NULL;
    kth_error_code_t result = kth_chain_double_spend_proof_spender_construct_from_data((uint8_t const*)reader_buf, (kth_size_t)reader_size, (uint32_t)version, &out);
    if (result != kth_ec_success) {
        PyErr_Format(PyExc_RuntimeError, "kth error code %d", (int)result);
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)out, KTH_PY_CAPSULE_CHAIN_DOUBLE_SPEND_PROOF_SPENDER, kth_py_native_chain_double_spend_proof_spender_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_double_spend_proof_spender_destruct(out);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_double_spend_proof_spender_copy(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_double_spend_proof_spender_const_t self_handle = (kth_double_spend_proof_spender_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_DOUBLE_SPEND_PROOF_SPENDER);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_double_spend_proof_spender_copy(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_DOUBLE_SPEND_PROOF_SPENDER, kth_py_native_chain_double_spend_proof_spender_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_double_spend_proof_spender_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_double_spend_proof_spender_destruct(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_double_spend_proof_spender_mut_t self_handle = (kth_double_spend_proof_spender_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_DOUBLE_SPEND_PROOF_SPENDER);
    if (self_handle == NULL) return NULL;
    kth_chain_double_spend_proof_spender_destruct(self_handle);
    PyCapsule_SetName(py_self, "kth.destroyed");
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_double_spend_proof_spender_version(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_double_spend_proof_spender_const_t self_handle = (kth_double_spend_proof_spender_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_DOUBLE_SPEND_PROOF_SPENDER);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_double_spend_proof_spender_version(self_handle);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyObject*
kth_py_native_chain_double_spend_proof_spender_set_version(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    unsigned int value = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OI", kwlist, &py_self, &value)) {
        return NULL;
    }
    kth_double_spend_proof_spender_mut_t self_handle = (kth_double_spend_proof_spender_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_DOUBLE_SPEND_PROOF_SPENDER);
    if (self_handle == NULL) return NULL;
    kth_chain_double_spend_proof_spender_set_version(self_handle, (uint32_t)value);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_double_spend_proof_spender_out_sequence(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_double_spend_proof_spender_const_t self_handle = (kth_double_spend_proof_spender_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_DOUBLE_SPEND_PROOF_SPENDER);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_double_spend_proof_spender_out_sequence(self_handle);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyObject*
kth_py_native_chain_double_spend_proof_spender_set_out_sequence(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    unsigned int value = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OI", kwlist, &py_self, &value)) {
        return NULL;
    }
    kth_double_spend_proof_spender_mut_t self_handle = (kth_double_spend_proof_spender_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_DOUBLE_SPEND_PROOF_SPENDER);
    if (self_handle == NULL) return NULL;
    kth_chain_double_spend_proof_spender_set_out_sequence(self_handle, (uint32_t)value);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_double_spend_proof_spender_locktime(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_double_spend_proof_spender_const_t self_handle = (kth_double_spend_proof_spender_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_DOUBLE_SPEND_PROOF_SPENDER);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_double_spend_proof_spender_locktime(self_handle);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyObject*
kth_py_native_chain_double_spend_proof_spender_set_locktime(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    unsigned int value = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OI", kwlist, &py_self, &value)) {
        return NULL;
    }
    kth_double_spend_proof_spender_mut_t self_handle = (kth_double_spend_proof_spender_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_DOUBLE_SPEND_PROOF_SPENDER);
    if (self_handle == NULL) return NULL;
    kth_chain_double_spend_proof_spender_set_locktime(self_handle, (uint32_t)value);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_double_spend_proof_spender_prev_outs_hash(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_double_spend_proof_spender_const_t self_handle = (kth_double_spend_proof_spender_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_DOUBLE_SPEND_PROOF_SPENDER);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_double_spend_proof_spender_prev_outs_hash(self_handle);
    return Py_BuildValue("y#", result.hash, (Py_ssize_t)KTH_BITCOIN_HASH_SIZE);
}

PyObject*
kth_py_native_chain_double_spend_proof_spender_set_prev_outs_hash(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    char const* value_buf = NULL;
    Py_ssize_t value_size = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Oy#", kwlist, &py_self, &value_buf, &value_size)) {
        return NULL;
    }
    kth_double_spend_proof_spender_mut_t self_handle = (kth_double_spend_proof_spender_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_DOUBLE_SPEND_PROOF_SPENDER);
    if (self_handle == NULL) return NULL;
    if (value_size != (Py_ssize_t)KTH_BITCOIN_HASH_SIZE) {
        PyErr_Format(PyExc_ValueError, "expected %d-byte value, got %zd", (int)KTH_BITCOIN_HASH_SIZE, value_size);
        return NULL;
    }
    kth_hash_t value;
    memcpy(value.hash, value_buf, (size_t)KTH_BITCOIN_HASH_SIZE);
    kth_chain_double_spend_proof_spender_set_prev_outs_hash(self_handle, value);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_double_spend_proof_spender_sequence_hash(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_double_spend_proof_spender_const_t self_handle = (kth_double_spend_proof_spender_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_DOUBLE_SPEND_PROOF_SPENDER);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_double_spend_proof_spender_sequence_hash(self_handle);
    return Py_BuildValue("y#", result.hash, (Py_ssize_t)KTH_BITCOIN_HASH_SIZE);
}

PyObject*
kth_py_native_chain_double_spend_proof_spender_set_sequence_hash(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    char const* value_buf = NULL;
    Py_ssize_t value_size = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Oy#", kwlist, &py_self, &value_buf, &value_size)) {
        return NULL;
    }
    kth_double_spend_proof_spender_mut_t self_handle = (kth_double_spend_proof_spender_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_DOUBLE_SPEND_PROOF_SPENDER);
    if (self_handle == NULL) return NULL;
    if (value_size != (Py_ssize_t)KTH_BITCOIN_HASH_SIZE) {
        PyErr_Format(PyExc_ValueError, "expected %d-byte value, got %zd", (int)KTH_BITCOIN_HASH_SIZE, value_size);
        return NULL;
    }
    kth_hash_t value;
    memcpy(value.hash, value_buf, (size_t)KTH_BITCOIN_HASH_SIZE);
    kth_chain_double_spend_proof_spender_set_sequence_hash(self_handle, value);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_double_spend_proof_spender_outputs_hash(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_double_spend_proof_spender_const_t self_handle = (kth_double_spend_proof_spender_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_DOUBLE_SPEND_PROOF_SPENDER);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_double_spend_proof_spender_outputs_hash(self_handle);
    return Py_BuildValue("y#", result.hash, (Py_ssize_t)KTH_BITCOIN_HASH_SIZE);
}

PyObject*
kth_py_native_chain_double_spend_proof_spender_set_outputs_hash(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    char const* value_buf = NULL;
    Py_ssize_t value_size = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Oy#", kwlist, &py_self, &value_buf, &value_size)) {
        return NULL;
    }
    kth_double_spend_proof_spender_mut_t self_handle = (kth_double_spend_proof_spender_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_DOUBLE_SPEND_PROOF_SPENDER);
    if (self_handle == NULL) return NULL;
    if (value_size != (Py_ssize_t)KTH_BITCOIN_HASH_SIZE) {
        PyErr_Format(PyExc_ValueError, "expected %d-byte value, got %zd", (int)KTH_BITCOIN_HASH_SIZE, value_size);
        return NULL;
    }
    kth_hash_t value;
    memcpy(value.hash, value_buf, (size_t)KTH_BITCOIN_HASH_SIZE);
    kth_chain_double_spend_proof_spender_set_outputs_hash(self_handle, value);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_double_spend_proof_spender_push_data(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_double_spend_proof_spender_const_t self_handle = (kth_double_spend_proof_spender_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_DOUBLE_SPEND_PROOF_SPENDER);
    if (self_handle == NULL) return NULL;
    kth_size_t out_size = 0;
    auto const result = kth_chain_double_spend_proof_spender_push_data(self_handle, &out_size);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: serialization failed");
        return NULL;
    }
    PyObject* py_result = Py_BuildValue("y#", result, (Py_ssize_t)out_size);
    kth_core_destruct_array(result);
    return py_result;
}

PyObject*
kth_py_native_chain_double_spend_proof_spender_set_push_data(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    char const* value_buf = NULL;
    Py_ssize_t value_size = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Oy#", kwlist, &py_self, &value_buf, &value_size)) {
        return NULL;
    }
    kth_double_spend_proof_spender_mut_t self_handle = (kth_double_spend_proof_spender_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_DOUBLE_SPEND_PROOF_SPENDER);
    if (self_handle == NULL) return NULL;
    kth_chain_double_spend_proof_spender_set_push_data(self_handle, (uint8_t const*)value_buf, (kth_size_t)value_size);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_double_spend_proof_spender_is_valid(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_double_spend_proof_spender_const_t self_handle = (kth_double_spend_proof_spender_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_DOUBLE_SPEND_PROOF_SPENDER);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_double_spend_proof_spender_is_valid(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_double_spend_proof_spender_reset(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_double_spend_proof_spender_mut_t self_handle = (kth_double_spend_proof_spender_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_DOUBLE_SPEND_PROOF_SPENDER);
    if (self_handle == NULL) return NULL;
    kth_chain_double_spend_proof_spender_reset(self_handle);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_double_spend_proof_spender_equals(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"other", NULL};
    PyObject* py_self = NULL;
    PyObject* py_other = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_other)) {
        return NULL;
    }
    kth_double_spend_proof_spender_const_t self_handle = (kth_double_spend_proof_spender_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_DOUBLE_SPEND_PROOF_SPENDER);
    if (self_handle == NULL) return NULL;
    kth_double_spend_proof_spender_const_t other_handle = (kth_double_spend_proof_spender_const_t)PyCapsule_GetPointer(py_other, KTH_PY_CAPSULE_CHAIN_DOUBLE_SPEND_PROOF_SPENDER);
    if (other_handle == NULL) return NULL;
    auto const result = kth_chain_double_spend_proof_spender_equals(self_handle, other_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_double_spend_proof_spender_serialized_size(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_double_spend_proof_spender_const_t self_handle = (kth_double_spend_proof_spender_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_DOUBLE_SPEND_PROOF_SPENDER);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_double_spend_proof_spender_serialized_size(self_handle);
    return PyLong_FromSize_t((size_t)result);
}

PyMethodDef kth_py_native_chain_double_spend_proof_spender_methods[] = {
    {"chain_double_spend_proof_spender_construct_from_data", (PyCFunction)kth_py_native_chain_double_spend_proof_spender_construct_from_data, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_double_spend_proof_spender_copy", (PyCFunction)kth_py_native_chain_double_spend_proof_spender_copy, METH_O, NULL},
    {"chain_double_spend_proof_spender_destruct", (PyCFunction)kth_py_native_chain_double_spend_proof_spender_destruct, METH_O, NULL},
    {"chain_double_spend_proof_spender_version", (PyCFunction)kth_py_native_chain_double_spend_proof_spender_version, METH_O, NULL},
    {"chain_double_spend_proof_spender_set_version", (PyCFunction)kth_py_native_chain_double_spend_proof_spender_set_version, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_double_spend_proof_spender_out_sequence", (PyCFunction)kth_py_native_chain_double_spend_proof_spender_out_sequence, METH_O, NULL},
    {"chain_double_spend_proof_spender_set_out_sequence", (PyCFunction)kth_py_native_chain_double_spend_proof_spender_set_out_sequence, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_double_spend_proof_spender_locktime", (PyCFunction)kth_py_native_chain_double_spend_proof_spender_locktime, METH_O, NULL},
    {"chain_double_spend_proof_spender_set_locktime", (PyCFunction)kth_py_native_chain_double_spend_proof_spender_set_locktime, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_double_spend_proof_spender_prev_outs_hash", (PyCFunction)kth_py_native_chain_double_spend_proof_spender_prev_outs_hash, METH_O, NULL},
    {"chain_double_spend_proof_spender_set_prev_outs_hash", (PyCFunction)kth_py_native_chain_double_spend_proof_spender_set_prev_outs_hash, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_double_spend_proof_spender_sequence_hash", (PyCFunction)kth_py_native_chain_double_spend_proof_spender_sequence_hash, METH_O, NULL},
    {"chain_double_spend_proof_spender_set_sequence_hash", (PyCFunction)kth_py_native_chain_double_spend_proof_spender_set_sequence_hash, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_double_spend_proof_spender_outputs_hash", (PyCFunction)kth_py_native_chain_double_spend_proof_spender_outputs_hash, METH_O, NULL},
    {"chain_double_spend_proof_spender_set_outputs_hash", (PyCFunction)kth_py_native_chain_double_spend_proof_spender_set_outputs_hash, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_double_spend_proof_spender_push_data", (PyCFunction)kth_py_native_chain_double_spend_proof_spender_push_data, METH_O, NULL},
    {"chain_double_spend_proof_spender_set_push_data", (PyCFunction)kth_py_native_chain_double_spend_proof_spender_set_push_data, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_double_spend_proof_spender_is_valid", (PyCFunction)kth_py_native_chain_double_spend_proof_spender_is_valid, METH_O, NULL},
    {"chain_double_spend_proof_spender_reset", (PyCFunction)kth_py_native_chain_double_spend_proof_spender_reset, METH_O, NULL},
    {"chain_double_spend_proof_spender_equals", (PyCFunction)kth_py_native_chain_double_spend_proof_spender_equals, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_double_spend_proof_spender_serialized_size", (PyCFunction)kth_py_native_chain_double_spend_proof_spender_serialized_size, METH_O, NULL},
    {NULL, NULL, 0, NULL}  // sentinel
};

#ifdef __cplusplus
} // extern "C"
#endif
