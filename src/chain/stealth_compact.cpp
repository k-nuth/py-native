// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/py-native/chain/stealth_compact.h>

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
void kth_py_native_chain_stealth_compact_capsule_dtor(PyObject* capsule) {
    if ( ! PyCapsule_IsValid(capsule, KTH_PY_CAPSULE_CHAIN_STEALTH_COMPACT)) return;
    kth_stealth_compact_mut_t handle = (kth_stealth_compact_mut_t)PyCapsule_GetPointer(capsule, KTH_PY_CAPSULE_CHAIN_STEALTH_COMPACT);
    if (handle != NULL) kth_chain_stealth_compact_destruct(handle);
}

PyObject*
kth_py_native_chain_stealth_compact_copy(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_stealth_compact_const_t self_handle = (kth_stealth_compact_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_STEALTH_COMPACT);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_stealth_compact_copy(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_STEALTH_COMPACT, kth_py_native_chain_stealth_compact_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_stealth_compact_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_stealth_compact_destruct(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_stealth_compact_mut_t self_handle = (kth_stealth_compact_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_STEALTH_COMPACT);
    if (self_handle == NULL) return NULL;
    kth_chain_stealth_compact_destruct(self_handle);
    PyCapsule_SetName(py_self, "kth.destroyed");
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_stealth_compact_ephemeral_public_key_hash(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_stealth_compact_const_t self_handle = (kth_stealth_compact_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_STEALTH_COMPACT);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_stealth_compact_ephemeral_public_key_hash(self_handle);
    return Py_BuildValue("y#", result.hash, (Py_ssize_t)KTH_BITCOIN_HASH_SIZE);
}

PyObject*
kth_py_native_chain_stealth_compact_set_ephemeral_public_key_hash(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    char const* value_buf = NULL;
    Py_ssize_t value_size = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Oy#", kwlist, &py_self, &value_buf, &value_size)) {
        return NULL;
    }
    kth_stealth_compact_mut_t self_handle = (kth_stealth_compact_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_STEALTH_COMPACT);
    if (self_handle == NULL) return NULL;
    if (value_size != (Py_ssize_t)KTH_BITCOIN_HASH_SIZE) {
        PyErr_Format(PyExc_ValueError, "expected %d-byte value, got %zd", (int)KTH_BITCOIN_HASH_SIZE, value_size);
        return NULL;
    }
    kth_hash_t value;
    memcpy(value.hash, value_buf, (size_t)KTH_BITCOIN_HASH_SIZE);
    kth_chain_stealth_compact_set_ephemeral_public_key_hash(self_handle, &value);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_stealth_compact_public_key_hash(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_stealth_compact_const_t self_handle = (kth_stealth_compact_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_STEALTH_COMPACT);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_stealth_compact_public_key_hash(self_handle);
    return Py_BuildValue("y#", result.hash, (Py_ssize_t)KTH_BITCOIN_SHORT_HASH_SIZE);
}

PyObject*
kth_py_native_chain_stealth_compact_set_public_key_hash(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    char const* value_buf = NULL;
    Py_ssize_t value_size = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Oy#", kwlist, &py_self, &value_buf, &value_size)) {
        return NULL;
    }
    kth_stealth_compact_mut_t self_handle = (kth_stealth_compact_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_STEALTH_COMPACT);
    if (self_handle == NULL) return NULL;
    if (value_size != (Py_ssize_t)KTH_BITCOIN_SHORT_HASH_SIZE) {
        PyErr_Format(PyExc_ValueError, "expected %d-byte value, got %zd", (int)KTH_BITCOIN_SHORT_HASH_SIZE, value_size);
        return NULL;
    }
    kth_shorthash_t value;
    memcpy(value.hash, value_buf, (size_t)KTH_BITCOIN_SHORT_HASH_SIZE);
    kth_chain_stealth_compact_set_public_key_hash(self_handle, &value);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_stealth_compact_transaction_hash(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_stealth_compact_const_t self_handle = (kth_stealth_compact_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_STEALTH_COMPACT);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_stealth_compact_transaction_hash(self_handle);
    return Py_BuildValue("y#", result.hash, (Py_ssize_t)KTH_BITCOIN_HASH_SIZE);
}

PyObject*
kth_py_native_chain_stealth_compact_set_transaction_hash(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    char const* value_buf = NULL;
    Py_ssize_t value_size = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Oy#", kwlist, &py_self, &value_buf, &value_size)) {
        return NULL;
    }
    kth_stealth_compact_mut_t self_handle = (kth_stealth_compact_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_STEALTH_COMPACT);
    if (self_handle == NULL) return NULL;
    if (value_size != (Py_ssize_t)KTH_BITCOIN_HASH_SIZE) {
        PyErr_Format(PyExc_ValueError, "expected %d-byte value, got %zd", (int)KTH_BITCOIN_HASH_SIZE, value_size);
        return NULL;
    }
    kth_hash_t value;
    memcpy(value.hash, value_buf, (size_t)KTH_BITCOIN_HASH_SIZE);
    kth_chain_stealth_compact_set_transaction_hash(self_handle, &value);
    Py_RETURN_NONE;
}

PyMethodDef kth_py_native_chain_stealth_compact_methods[] = {
    {"chain_stealth_compact_copy", (PyCFunction)kth_py_native_chain_stealth_compact_copy, METH_O, NULL},
    {"chain_stealth_compact_destruct", (PyCFunction)kth_py_native_chain_stealth_compact_destruct, METH_O, NULL},
    {"chain_stealth_compact_ephemeral_public_key_hash", (PyCFunction)kth_py_native_chain_stealth_compact_ephemeral_public_key_hash, METH_O, NULL},
    {"chain_stealth_compact_set_ephemeral_public_key_hash", (PyCFunction)kth_py_native_chain_stealth_compact_set_ephemeral_public_key_hash, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_stealth_compact_public_key_hash", (PyCFunction)kth_py_native_chain_stealth_compact_public_key_hash, METH_O, NULL},
    {"chain_stealth_compact_set_public_key_hash", (PyCFunction)kth_py_native_chain_stealth_compact_set_public_key_hash, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_stealth_compact_transaction_hash", (PyCFunction)kth_py_native_chain_stealth_compact_transaction_hash, METH_O, NULL},
    {"chain_stealth_compact_set_transaction_hash", (PyCFunction)kth_py_native_chain_stealth_compact_set_transaction_hash, METH_VARARGS | METH_KEYWORDS, NULL},
    {NULL, NULL, 0, NULL}  // sentinel
};

#ifdef __cplusplus
} // extern "C"
#endif
