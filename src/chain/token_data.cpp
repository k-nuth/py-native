// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/py-native/chain/token_data.h>

#include <string.h>
#include <kth/capi.h>
#include <kth/capi/chain/token_data.h>
#include <kth/py-native/capsule_names.h>
#include <kth/py-native/utils.h>

#ifdef __cplusplus
extern "C" {
#endif

// PyCapsule destructor — released by GC when the capsule is
// collected. Explicit `destruct` calls set the capsule name to
// "kth.destroyed", so PyCapsule_IsValid returns false and this
// destructor becomes a no-op (no double-free).
void kth_py_native_chain_token_data_capsule_dtor(PyObject* capsule) {
    if ( ! PyCapsule_IsValid(capsule, KTH_PY_CAPSULE_CHAIN_TOKEN_DATA)) return;
    kth_token_data_mut_t handle = (kth_token_data_mut_t)PyCapsule_GetPointer(capsule, KTH_PY_CAPSULE_CHAIN_TOKEN_DATA);
    if (handle != NULL) kth_chain_token_data_destruct(handle);
}

PyObject*
kth_py_native_chain_token_data_construct_from_data(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"reader", NULL};
    char const* reader_buf = NULL;
    Py_ssize_t reader_size = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "y#", kwlist, &reader_buf, &reader_size)) {
        return NULL;
    }
    kth_token_data_mut_t out = NULL;
    kth_error_code_t result = kth_chain_token_construct_from_data((uint8_t const*)reader_buf, (kth_size_t)reader_size, &out);
    if (result != kth_ec_success) {
        PyErr_Format(PyExc_RuntimeError, "kth error code %d", (int)result);
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)out, KTH_PY_CAPSULE_CHAIN_TOKEN_DATA, kth_py_native_chain_token_data_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_token_data_destruct(out);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_token_data_copy(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_token_data_const_t self_handle = (kth_token_data_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_TOKEN_DATA);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_token_data_copy(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_TOKEN_DATA, kth_py_native_chain_token_data_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_token_data_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_token_data_destruct(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_token_data_mut_t self_handle = (kth_token_data_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_TOKEN_DATA);
    if (self_handle == NULL) return NULL;
    kth_chain_token_data_destruct(self_handle);
    PyCapsule_SetName(py_self, "kth.destroyed");
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_token_data_id(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_token_data_const_t self_handle = (kth_token_data_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_TOKEN_DATA);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_token_data_id(self_handle);
    return Py_BuildValue("y#", result.hash, (Py_ssize_t)KTH_BITCOIN_HASH_SIZE);
}

PyObject*
kth_py_native_chain_token_data_set_id(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    char const* value_buf = NULL;
    Py_ssize_t value_size = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Oy#", kwlist, &py_self, &value_buf, &value_size)) {
        return NULL;
    }
    kth_token_data_mut_t self_handle = (kth_token_data_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_TOKEN_DATA);
    if (self_handle == NULL) return NULL;
    if (value_size != (Py_ssize_t)KTH_BITCOIN_HASH_SIZE) {
        PyErr_Format(PyExc_ValueError, "expected %d-byte value, got %zd", (int)KTH_BITCOIN_HASH_SIZE, value_size);
        return NULL;
    }
    kth_hash_t value;
    memcpy(value.hash, value_buf, (size_t)KTH_BITCOIN_HASH_SIZE);
    kth_chain_token_data_set_id(self_handle, &value);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_token_data_equals(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"other", NULL};
    PyObject* py_self = NULL;
    PyObject* py_other = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_other)) {
        return NULL;
    }
    kth_token_data_const_t self_handle = (kth_token_data_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_TOKEN_DATA);
    if (self_handle == NULL) return NULL;
    kth_token_data_const_t other_handle = (kth_token_data_const_t)PyCapsule_GetPointer(py_other, KTH_PY_CAPSULE_CHAIN_TOKEN_DATA);
    if (other_handle == NULL) return NULL;
    auto const result = kth_chain_token_data_equals(self_handle, other_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_token_data_make_fungible(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"id", (char*)"amount", NULL};
    char const* id_buf = NULL;
    Py_ssize_t id_size = 0;
    unsigned long long amount = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "y#K", kwlist, &id_buf, &id_size, &amount)) {
        return NULL;
    }
    if (id_size != (Py_ssize_t)KTH_BITCOIN_HASH_SIZE) {
        PyErr_Format(PyExc_ValueError, "expected %d-byte id, got %zd", (int)KTH_BITCOIN_HASH_SIZE, id_size);
        return NULL;
    }
    kth_hash_t id;
    memcpy(id.hash, id_buf, (size_t)KTH_BITCOIN_HASH_SIZE);
    auto const result = kth_chain_token_make_fungible(&id, (uint64_t)amount);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_TOKEN_DATA, kth_py_native_chain_token_data_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_token_data_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_token_data_make_non_fungible(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"id", (char*)"capability", (char*)"commitment", NULL};
    char const* id_buf = NULL;
    Py_ssize_t id_size = 0;
    unsigned long long capability = 0;
    char const* commitment_buf = NULL;
    Py_ssize_t commitment_size = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "y#Ky#", kwlist, &id_buf, &id_size, &capability, &commitment_buf, &commitment_size)) {
        return NULL;
    }
    if (id_size != (Py_ssize_t)KTH_BITCOIN_HASH_SIZE) {
        PyErr_Format(PyExc_ValueError, "expected %d-byte id, got %zd", (int)KTH_BITCOIN_HASH_SIZE, id_size);
        return NULL;
    }
    kth_hash_t id;
    memcpy(id.hash, id_buf, (size_t)KTH_BITCOIN_HASH_SIZE);
    auto const result = kth_chain_token_make_non_fungible(&id, (kth_token_capability_t)capability, (uint8_t const*)commitment_buf, (kth_size_t)commitment_size);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_TOKEN_DATA, kth_py_native_chain_token_data_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_token_data_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_token_data_make_both(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"id", (char*)"amount", (char*)"capability", (char*)"commitment", NULL};
    char const* id_buf = NULL;
    Py_ssize_t id_size = 0;
    unsigned long long amount = 0;
    unsigned long long capability = 0;
    char const* commitment_buf = NULL;
    Py_ssize_t commitment_size = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "y#KKy#", kwlist, &id_buf, &id_size, &amount, &capability, &commitment_buf, &commitment_size)) {
        return NULL;
    }
    if (id_size != (Py_ssize_t)KTH_BITCOIN_HASH_SIZE) {
        PyErr_Format(PyExc_ValueError, "expected %d-byte id, got %zd", (int)KTH_BITCOIN_HASH_SIZE, id_size);
        return NULL;
    }
    kth_hash_t id;
    memcpy(id.hash, id_buf, (size_t)KTH_BITCOIN_HASH_SIZE);
    auto const result = kth_chain_token_make_both(&id, (uint64_t)amount, (kth_token_capability_t)capability, (uint8_t const*)commitment_buf, (kth_size_t)commitment_size);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_TOKEN_DATA, kth_py_native_chain_token_data_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_token_data_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_token_data_get_kind(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_token_data_const_t self_handle = (kth_token_data_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_TOKEN_DATA);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_token_data_get_kind(self_handle);
    return PyLong_FromLong((long)result);
}

PyObject*
kth_py_native_chain_token_data_is_valid(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_token_data_const_t self_handle = (kth_token_data_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_TOKEN_DATA);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_token_data_is_valid(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_token_data_get_amount(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_token_data_const_t self_handle = (kth_token_data_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_TOKEN_DATA);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_token_data_get_amount(self_handle);
    return PyLong_FromLongLong((long long)result);
}

PyObject*
kth_py_native_chain_token_data_has_nft(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_token_data_const_t self_handle = (kth_token_data_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_TOKEN_DATA);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_token_data_has_nft(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_token_data_is_fungible_only(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_token_data_const_t self_handle = (kth_token_data_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_TOKEN_DATA);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_token_data_is_fungible_only(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_token_data_get_nft_capability(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_token_data_const_t self_handle = (kth_token_data_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_TOKEN_DATA);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_token_data_get_nft_capability(self_handle);
    return PyLong_FromLong((long)result);
}

PyObject*
kth_py_native_chain_token_data_get_nft_commitment(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_token_data_const_t self_handle = (kth_token_data_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_TOKEN_DATA);
    if (self_handle == NULL) return NULL;
    kth_size_t out_size = 0;
    auto const result = kth_chain_token_data_get_nft_commitment(self_handle, &out_size);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: serialization failed");
        return NULL;
    }
    PyObject* py_result = Py_BuildValue("y#", result, (Py_ssize_t)out_size);
    kth_core_destruct_array(result);
    return py_result;
}

PyObject*
kth_py_native_chain_token_data_is_immutable_nft(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_token_data_const_t self_handle = (kth_token_data_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_TOKEN_DATA);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_token_data_is_immutable_nft(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_token_data_is_mutable_nft(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_token_data_const_t self_handle = (kth_token_data_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_TOKEN_DATA);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_token_data_is_mutable_nft(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_token_data_is_minting_nft(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_token_data_const_t self_handle = (kth_token_data_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_TOKEN_DATA);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_token_data_is_minting_nft(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_token_data_serialized_size(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_token_data_const_t self_handle = (kth_token_data_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_TOKEN_DATA);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_token_data_serialized_size(self_handle);
    return PyLong_FromSize_t((size_t)result);
}

PyObject*
kth_py_native_chain_token_data_bitfield(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_token_data_const_t self_handle = (kth_token_data_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_TOKEN_DATA);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_token_data_bitfield(self_handle);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyObject*
kth_py_native_chain_token_data_to_data(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_token_data_const_t self_handle = (kth_token_data_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_TOKEN_DATA);
    if (self_handle == NULL) return NULL;
    kth_size_t out_size = 0;
    auto const result = kth_chain_token_data_to_data(self_handle, &out_size);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: serialization failed");
        return NULL;
    }
    PyObject* py_result = Py_BuildValue("y#", result, (Py_ssize_t)out_size);
    kth_core_destruct_array(result);
    return py_result;
}

PyMethodDef kth_py_native_chain_token_data_methods[] = {
    {"chain_token_data_construct_from_data", (PyCFunction)kth_py_native_chain_token_data_construct_from_data, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_token_data_copy", (PyCFunction)kth_py_native_chain_token_data_copy, METH_O, NULL},
    {"chain_token_data_destruct", (PyCFunction)kth_py_native_chain_token_data_destruct, METH_O, NULL},
    {"chain_token_data_id", (PyCFunction)kth_py_native_chain_token_data_id, METH_O, NULL},
    {"chain_token_data_set_id", (PyCFunction)kth_py_native_chain_token_data_set_id, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_token_data_equals", (PyCFunction)kth_py_native_chain_token_data_equals, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_token_data_make_fungible", (PyCFunction)kth_py_native_chain_token_data_make_fungible, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_token_data_make_non_fungible", (PyCFunction)kth_py_native_chain_token_data_make_non_fungible, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_token_data_make_both", (PyCFunction)kth_py_native_chain_token_data_make_both, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_token_data_get_kind", (PyCFunction)kth_py_native_chain_token_data_get_kind, METH_O, NULL},
    {"chain_token_data_is_valid", (PyCFunction)kth_py_native_chain_token_data_is_valid, METH_O, NULL},
    {"chain_token_data_get_amount", (PyCFunction)kth_py_native_chain_token_data_get_amount, METH_O, NULL},
    {"chain_token_data_has_nft", (PyCFunction)kth_py_native_chain_token_data_has_nft, METH_O, NULL},
    {"chain_token_data_is_fungible_only", (PyCFunction)kth_py_native_chain_token_data_is_fungible_only, METH_O, NULL},
    {"chain_token_data_get_nft_capability", (PyCFunction)kth_py_native_chain_token_data_get_nft_capability, METH_O, NULL},
    {"chain_token_data_get_nft_commitment", (PyCFunction)kth_py_native_chain_token_data_get_nft_commitment, METH_O, NULL},
    {"chain_token_data_is_immutable_nft", (PyCFunction)kth_py_native_chain_token_data_is_immutable_nft, METH_O, NULL},
    {"chain_token_data_is_mutable_nft", (PyCFunction)kth_py_native_chain_token_data_is_mutable_nft, METH_O, NULL},
    {"chain_token_data_is_minting_nft", (PyCFunction)kth_py_native_chain_token_data_is_minting_nft, METH_O, NULL},
    {"chain_token_data_serialized_size", (PyCFunction)kth_py_native_chain_token_data_serialized_size, METH_O, NULL},
    {"chain_token_data_bitfield", (PyCFunction)kth_py_native_chain_token_data_bitfield, METH_O, NULL},
    {"chain_token_data_to_data", (PyCFunction)kth_py_native_chain_token_data_to_data, METH_O, NULL},
    {NULL, NULL, 0, NULL}  // sentinel
};

#ifdef __cplusplus
} // extern "C"
#endif
