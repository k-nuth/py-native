// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/py-native/wallet/stealth_sender.h>

#include <string.h>
#include <kth/capi.h>
#include <kth/capi/wallet/stealth_sender.h>
#include <kth/py-native/capsule_names.h>
#include <kth/py-native/utils.h>

#ifdef __cplusplus
extern "C" {
#endif

// PyCapsule destructor — released by GC when the capsule is
// collected. Explicit `destruct` calls set the capsule name to
// "kth.destroyed", so PyCapsule_IsValid returns false and this
// destructor becomes a no-op (no double-free).
void kth_py_native_wallet_stealth_sender_capsule_dtor(PyObject* capsule) {
    if ( ! PyCapsule_IsValid(capsule, KTH_PY_CAPSULE_WALLET_STEALTH_SENDER)) return;
    kth_stealth_sender_mut_t handle = (kth_stealth_sender_mut_t)PyCapsule_GetPointer(capsule, KTH_PY_CAPSULE_WALLET_STEALTH_SENDER);
    if (handle != NULL) kth_wallet_stealth_sender_destruct(handle);
}

PyObject*
kth_py_native_wallet_stealth_sender_construct_from_stealth_address_seed_binary_version(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"address", (char*)"seed", (char*)"filter", (char*)"version", NULL};
    PyObject* py_address = NULL;
    char const* seed_buf = NULL;
    Py_ssize_t seed_size = 0;
    PyObject* py_filter = NULL;
    unsigned char version = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Oy#OB", kwlist, &py_address, &seed_buf, &seed_size, &py_filter, &version)) {
        return NULL;
    }
    kth_stealth_address_const_t address_handle = (kth_stealth_address_const_t)PyCapsule_GetPointer(py_address, KTH_PY_CAPSULE_WALLET_STEALTH_ADDRESS);
    if (address_handle == NULL) return NULL;
    kth_binary_const_t filter_handle = (kth_binary_const_t)PyCapsule_GetPointer(py_filter, KTH_PY_CAPSULE_CORE_BINARY);
    if (filter_handle == NULL) return NULL;
    auto const result = kth_wallet_stealth_sender_construct_from_stealth_address_seed_binary_version(address_handle, (uint8_t const*)seed_buf, (kth_size_t)seed_size, filter_handle, (uint8_t)version);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_STEALTH_SENDER, kth_py_native_wallet_stealth_sender_capsule_dtor);
    if (capsule == NULL) {
        kth_wallet_stealth_sender_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_wallet_stealth_sender_construct_from_ephemeral_private_stealth_address_seed_binary_version(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"ephemeral_private", (char*)"address", (char*)"seed", (char*)"filter", (char*)"version", NULL};
    char const* ephemeral_private_buf = NULL;
    Py_ssize_t ephemeral_private_size = 0;
    PyObject* py_address = NULL;
    char const* seed_buf = NULL;
    Py_ssize_t seed_size = 0;
    PyObject* py_filter = NULL;
    unsigned char version = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "y#Oy#OB", kwlist, &ephemeral_private_buf, &ephemeral_private_size, &py_address, &seed_buf, &seed_size, &py_filter, &version)) {
        return NULL;
    }
    if (ephemeral_private_size != (Py_ssize_t)KTH_BITCOIN_HASH_SIZE) {
        PyErr_Format(PyExc_ValueError, "expected %d-byte ephemeral_private, got %zd", (int)KTH_BITCOIN_HASH_SIZE, ephemeral_private_size);
        return NULL;
    }
    kth_hash_t ephemeral_private;
    memcpy(ephemeral_private.hash, ephemeral_private_buf, (size_t)KTH_BITCOIN_HASH_SIZE);
    kth_stealth_address_const_t address_handle = (kth_stealth_address_const_t)PyCapsule_GetPointer(py_address, KTH_PY_CAPSULE_WALLET_STEALTH_ADDRESS);
    if (address_handle == NULL) return NULL;
    kth_binary_const_t filter_handle = (kth_binary_const_t)PyCapsule_GetPointer(py_filter, KTH_PY_CAPSULE_CORE_BINARY);
    if (filter_handle == NULL) return NULL;
    auto const result = kth_wallet_stealth_sender_construct_from_ephemeral_private_stealth_address_seed_binary_version(&ephemeral_private, address_handle, (uint8_t const*)seed_buf, (kth_size_t)seed_size, filter_handle, (uint8_t)version);
    kth_core_secure_zero((void*)&ephemeral_private, sizeof(kth_hash_t));
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_STEALTH_SENDER, kth_py_native_wallet_stealth_sender_capsule_dtor);
    if (capsule == NULL) {
        kth_wallet_stealth_sender_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_wallet_stealth_sender_copy(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_stealth_sender_const_t self_handle = (kth_stealth_sender_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_STEALTH_SENDER);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_stealth_sender_copy(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_STEALTH_SENDER, kth_py_native_wallet_stealth_sender_capsule_dtor);
    if (capsule == NULL) {
        kth_wallet_stealth_sender_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_wallet_stealth_sender_destruct(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_stealth_sender_mut_t self_handle = (kth_stealth_sender_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_STEALTH_SENDER);
    if (self_handle == NULL) return NULL;
    kth_wallet_stealth_sender_destruct(self_handle);
    PyCapsule_SetName(py_self, "kth.destroyed");
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_wallet_stealth_sender_valid(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_stealth_sender_const_t self_handle = (kth_stealth_sender_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_STEALTH_SENDER);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_stealth_sender_valid(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_wallet_stealth_sender_stealth_script(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_stealth_sender_const_t self_handle = (kth_stealth_sender_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_STEALTH_SENDER);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_stealth_sender_stealth_script(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_SCRIPT, kth_py_native_borrowed_parent_dtor);
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
kth_py_native_wallet_stealth_sender_payment_address(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_stealth_sender_const_t self_handle = (kth_stealth_sender_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_STEALTH_SENDER);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_stealth_sender_payment_address(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_PAYMENT_ADDRESS, kth_py_native_borrowed_parent_dtor);
    if (capsule == NULL) return NULL;
    Py_INCREF(py_self);
    if (PyCapsule_SetContext(capsule, py_self) != 0) {
        Py_DECREF(py_self);
        Py_DECREF(capsule);
        return NULL;
    }
    return capsule;
}

PyMethodDef kth_py_native_wallet_stealth_sender_methods[] = {
    {"wallet_stealth_sender_construct_from_stealth_address_seed_binary_version", (PyCFunction)kth_py_native_wallet_stealth_sender_construct_from_stealth_address_seed_binary_version, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_stealth_sender_construct_from_ephemeral_private_stealth_address_seed_binary_version", (PyCFunction)kth_py_native_wallet_stealth_sender_construct_from_ephemeral_private_stealth_address_seed_binary_version, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_stealth_sender_copy", (PyCFunction)kth_py_native_wallet_stealth_sender_copy, METH_O, NULL},
    {"wallet_stealth_sender_destruct", (PyCFunction)kth_py_native_wallet_stealth_sender_destruct, METH_O, NULL},
    {"wallet_stealth_sender_valid", (PyCFunction)kth_py_native_wallet_stealth_sender_valid, METH_O, NULL},
    {"wallet_stealth_sender_stealth_script", (PyCFunction)kth_py_native_wallet_stealth_sender_stealth_script, METH_O, NULL},
    {"wallet_stealth_sender_payment_address", (PyCFunction)kth_py_native_wallet_stealth_sender_payment_address, METH_O, NULL},
    {NULL, NULL, 0, NULL}  // sentinel
};

#ifdef __cplusplus
} // extern "C"
#endif
