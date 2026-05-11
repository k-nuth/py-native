// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/py-native/wallet/stealth_receiver.h>

#include <string.h>
#include <kth/capi.h>
#include <kth/capi/wallet/stealth_receiver.h>
#include <kth/py-native/capsule_names.h>
#include <kth/py-native/utils.h>

#ifdef __cplusplus
extern "C" {
#endif

// PyCapsule destructor — released by GC when the capsule is
// collected. Explicit `destruct` calls set the capsule name to
// "kth.destroyed", so PyCapsule_IsValid returns false and this
// destructor becomes a no-op (no double-free).
void kth_py_native_wallet_stealth_receiver_capsule_dtor(PyObject* capsule) {
    if ( ! PyCapsule_IsValid(capsule, KTH_PY_CAPSULE_WALLET_STEALTH_RECEIVER)) return;
    kth_stealth_receiver_mut_t handle = (kth_stealth_receiver_mut_t)PyCapsule_GetPointer(capsule, KTH_PY_CAPSULE_WALLET_STEALTH_RECEIVER);
    if (handle != NULL) kth_wallet_stealth_receiver_destruct(handle);
}

PyObject*
kth_py_native_wallet_stealth_receiver_construct(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"scan_private", (char*)"spend_private", (char*)"filter", (char*)"version", NULL};
    char const* scan_private_buf = NULL;
    Py_ssize_t scan_private_size = 0;
    char const* spend_private_buf = NULL;
    Py_ssize_t spend_private_size = 0;
    PyObject* py_filter = NULL;
    unsigned char version = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "y#y#OB", kwlist, &scan_private_buf, &scan_private_size, &spend_private_buf, &spend_private_size, &py_filter, &version)) {
        return NULL;
    }
    if (scan_private_size != (Py_ssize_t)KTH_BITCOIN_HASH_SIZE) {
        PyErr_Format(PyExc_ValueError, "expected %d-byte scan_private, got %zd", (int)KTH_BITCOIN_HASH_SIZE, scan_private_size);
        return NULL;
    }
    kth_hash_t scan_private;
    memcpy(scan_private.hash, scan_private_buf, (size_t)KTH_BITCOIN_HASH_SIZE);
    if (spend_private_size != (Py_ssize_t)KTH_BITCOIN_HASH_SIZE) {
        PyErr_Format(PyExc_ValueError, "expected %d-byte spend_private, got %zd", (int)KTH_BITCOIN_HASH_SIZE, spend_private_size);
        return NULL;
    }
    kth_hash_t spend_private;
    memcpy(spend_private.hash, spend_private_buf, (size_t)KTH_BITCOIN_HASH_SIZE);
    kth_binary_const_t filter_handle = (kth_binary_const_t)PyCapsule_GetPointer(py_filter, KTH_PY_CAPSULE_CORE_BINARY);
    if (filter_handle == NULL) return NULL;
    auto const result = kth_wallet_stealth_receiver_construct(&scan_private, &spend_private, filter_handle, (uint8_t)version);
    kth_core_secure_zero((void*)&scan_private, sizeof(kth_hash_t));
    kth_core_secure_zero((void*)&spend_private, sizeof(kth_hash_t));
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_STEALTH_RECEIVER, kth_py_native_wallet_stealth_receiver_capsule_dtor);
    if (capsule == NULL) {
        kth_wallet_stealth_receiver_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_wallet_stealth_receiver_copy(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_stealth_receiver_const_t self_handle = (kth_stealth_receiver_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_STEALTH_RECEIVER);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_stealth_receiver_copy(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_STEALTH_RECEIVER, kth_py_native_wallet_stealth_receiver_capsule_dtor);
    if (capsule == NULL) {
        kth_wallet_stealth_receiver_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_wallet_stealth_receiver_destruct(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_stealth_receiver_mut_t self_handle = (kth_stealth_receiver_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_STEALTH_RECEIVER);
    if (self_handle == NULL) return NULL;
    kth_wallet_stealth_receiver_destruct(self_handle);
    PyCapsule_SetName(py_self, "kth.destroyed");
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_wallet_stealth_receiver_valid(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_stealth_receiver_const_t self_handle = (kth_stealth_receiver_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_STEALTH_RECEIVER);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_stealth_receiver_valid(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_wallet_stealth_receiver_stealth_address(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_stealth_receiver_const_t self_handle = (kth_stealth_receiver_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_STEALTH_RECEIVER);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_stealth_receiver_stealth_address(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_STEALTH_ADDRESS, kth_py_native_borrowed_parent_dtor);
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
kth_py_native_wallet_stealth_receiver_derive_address(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"out_address", (char*)"ephemeral_public", NULL};
    PyObject* py_self = NULL;
    PyObject* py_out_address = NULL;
    char const* ephemeral_public_buf = NULL;
    Py_ssize_t ephemeral_public_size = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OOy#", kwlist, &py_self, &py_out_address, &ephemeral_public_buf, &ephemeral_public_size)) {
        return NULL;
    }
    kth_stealth_receiver_const_t self_handle = (kth_stealth_receiver_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_STEALTH_RECEIVER);
    if (self_handle == NULL) return NULL;
    kth_payment_address_mut_t out_address_handle = (kth_payment_address_mut_t)PyCapsule_GetPointer(py_out_address, KTH_PY_CAPSULE_WALLET_PAYMENT_ADDRESS);
    if (out_address_handle == NULL) return NULL;
    if (ephemeral_public_size != (Py_ssize_t)KTH_EC_COMPRESSED_SIZE) {
        PyErr_Format(PyExc_ValueError, "expected %d-byte ephemeral_public, got %zd", (int)KTH_EC_COMPRESSED_SIZE, ephemeral_public_size);
        return NULL;
    }
    kth_ec_compressed_t ephemeral_public;
    memcpy(ephemeral_public.data, ephemeral_public_buf, (size_t)KTH_EC_COMPRESSED_SIZE);
    auto const result = kth_wallet_stealth_receiver_derive_address(self_handle, out_address_handle, &ephemeral_public);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_wallet_stealth_receiver_derive_private(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"out_private", (char*)"ephemeral_public", NULL};
    PyObject* py_self = NULL;
    char const* out_private_buf = NULL;
    Py_ssize_t out_private_size = 0;
    char const* ephemeral_public_buf = NULL;
    Py_ssize_t ephemeral_public_size = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Oy#y#", kwlist, &py_self, &out_private_buf, &out_private_size, &ephemeral_public_buf, &ephemeral_public_size)) {
        return NULL;
    }
    kth_stealth_receiver_const_t self_handle = (kth_stealth_receiver_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_STEALTH_RECEIVER);
    if (self_handle == NULL) return NULL;
    if (out_private_size != (Py_ssize_t)KTH_BITCOIN_HASH_SIZE) {
        PyErr_Format(PyExc_ValueError, "expected %d-byte out_private, got %zd", (int)KTH_BITCOIN_HASH_SIZE, out_private_size);
        return NULL;
    }
    kth_hash_t out_private;
    memcpy(out_private.hash, out_private_buf, (size_t)KTH_BITCOIN_HASH_SIZE);
    if (ephemeral_public_size != (Py_ssize_t)KTH_EC_COMPRESSED_SIZE) {
        PyErr_Format(PyExc_ValueError, "expected %d-byte ephemeral_public, got %zd", (int)KTH_EC_COMPRESSED_SIZE, ephemeral_public_size);
        return NULL;
    }
    kth_ec_compressed_t ephemeral_public;
    memcpy(ephemeral_public.data, ephemeral_public_buf, (size_t)KTH_EC_COMPRESSED_SIZE);
    auto const result = kth_wallet_stealth_receiver_derive_private(self_handle, &out_private, &ephemeral_public);
    kth_core_secure_zero((void*)&out_private, sizeof(kth_hash_t));
    return PyBool_FromLong((long)result);
}

PyMethodDef kth_py_native_wallet_stealth_receiver_methods[] = {
    {"wallet_stealth_receiver_construct", (PyCFunction)kth_py_native_wallet_stealth_receiver_construct, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_stealth_receiver_copy", (PyCFunction)kth_py_native_wallet_stealth_receiver_copy, METH_O, NULL},
    {"wallet_stealth_receiver_destruct", (PyCFunction)kth_py_native_wallet_stealth_receiver_destruct, METH_O, NULL},
    {"wallet_stealth_receiver_valid", (PyCFunction)kth_py_native_wallet_stealth_receiver_valid, METH_O, NULL},
    {"wallet_stealth_receiver_stealth_address", (PyCFunction)kth_py_native_wallet_stealth_receiver_stealth_address, METH_O, NULL},
    {"wallet_stealth_receiver_derive_address", (PyCFunction)kth_py_native_wallet_stealth_receiver_derive_address, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_stealth_receiver_derive_private", (PyCFunction)kth_py_native_wallet_stealth_receiver_derive_private, METH_VARARGS | METH_KEYWORDS, NULL},
    {NULL, NULL, 0, NULL}  // sentinel
};

#ifdef __cplusplus
} // extern "C"
#endif
