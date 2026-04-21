// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/py-native/wallet/ec_private.h>

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
void kth_py_native_wallet_ec_private_capsule_dtor(PyObject* capsule) {
    if ( ! PyCapsule_IsValid(capsule, KTH_PY_CAPSULE_WALLET_EC_PRIVATE)) return;
    kth_ec_private_mut_t handle = (kth_ec_private_mut_t)PyCapsule_GetPointer(capsule, KTH_PY_CAPSULE_WALLET_EC_PRIVATE);
    if (handle != NULL) kth_wallet_ec_private_destruct(handle);
}

PyObject*
kth_py_native_wallet_ec_private_construct_default(PyObject* self, PyObject* Py_UNUSED(args)) {
    auto const result = kth_wallet_ec_private_construct_default();
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_EC_PRIVATE, kth_py_native_wallet_ec_private_capsule_dtor);
    if (capsule == NULL) {
        kth_wallet_ec_private_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_wallet_ec_private_construct_from_wif_version(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"wif", (char*)"version", NULL};
    char const* wif = NULL;
    unsigned char version = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "sB", kwlist, &wif, &version)) {
        return NULL;
    }
    auto const result = kth_wallet_ec_private_construct_from_wif_version(wif, (uint8_t)version);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_EC_PRIVATE, kth_py_native_wallet_ec_private_capsule_dtor);
    if (capsule == NULL) {
        kth_wallet_ec_private_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_wallet_ec_private_construct_from_wif_compressed_version(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"wif_compressed", (char*)"version", NULL};
    char const* wif_compressed_buf = NULL;
    Py_ssize_t wif_compressed_size = 0;
    unsigned char version = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "y#B", kwlist, &wif_compressed_buf, &wif_compressed_size, &version)) {
        return NULL;
    }
    if (wif_compressed_size != (Py_ssize_t)KTH_WIF_COMPRESSED_SIZE) {
        PyErr_Format(PyExc_ValueError, "expected %d-byte wif_compressed, got %zd", (int)KTH_WIF_COMPRESSED_SIZE, wif_compressed_size);
        return NULL;
    }
    kth_wif_compressed_t wif_compressed;
    memcpy(wif_compressed.data, wif_compressed_buf, (size_t)KTH_WIF_COMPRESSED_SIZE);
    auto const result = kth_wallet_ec_private_construct_from_wif_compressed_version(wif_compressed, (uint8_t)version);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_EC_PRIVATE, kth_py_native_wallet_ec_private_capsule_dtor);
    if (capsule == NULL) {
        kth_wallet_ec_private_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_wallet_ec_private_construct_from_wif_uncompressed_version(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"wif_uncompressed", (char*)"version", NULL};
    char const* wif_uncompressed_buf = NULL;
    Py_ssize_t wif_uncompressed_size = 0;
    unsigned char version = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "y#B", kwlist, &wif_uncompressed_buf, &wif_uncompressed_size, &version)) {
        return NULL;
    }
    if (wif_uncompressed_size != (Py_ssize_t)KTH_WIF_UNCOMPRESSED_SIZE) {
        PyErr_Format(PyExc_ValueError, "expected %d-byte wif_uncompressed, got %zd", (int)KTH_WIF_UNCOMPRESSED_SIZE, wif_uncompressed_size);
        return NULL;
    }
    kth_wif_uncompressed_t wif_uncompressed;
    memcpy(wif_uncompressed.data, wif_uncompressed_buf, (size_t)KTH_WIF_UNCOMPRESSED_SIZE);
    auto const result = kth_wallet_ec_private_construct_from_wif_uncompressed_version(wif_uncompressed, (uint8_t)version);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_EC_PRIVATE, kth_py_native_wallet_ec_private_capsule_dtor);
    if (capsule == NULL) {
        kth_wallet_ec_private_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_wallet_ec_private_construct_from_secret_version_compress(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"secret", (char*)"version", (char*)"compress", NULL};
    char const* secret_buf = NULL;
    Py_ssize_t secret_size = 0;
    unsigned short version = 0;
    int compress = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "y#Hp", kwlist, &secret_buf, &secret_size, &version, &compress)) {
        return NULL;
    }
    if (secret_size != (Py_ssize_t)KTH_BITCOIN_HASH_SIZE) {
        PyErr_Format(PyExc_ValueError, "expected %d-byte secret, got %zd", (int)KTH_BITCOIN_HASH_SIZE, secret_size);
        return NULL;
    }
    kth_hash_t secret;
    memcpy(secret.hash, secret_buf, (size_t)KTH_BITCOIN_HASH_SIZE);
    auto const result = kth_wallet_ec_private_construct_from_secret_version_compress(secret, (uint16_t)version, (kth_bool_t)compress);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_EC_PRIVATE, kth_py_native_wallet_ec_private_capsule_dtor);
    if (capsule == NULL) {
        kth_wallet_ec_private_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_wallet_ec_private_copy(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_ec_private_const_t self_handle = (kth_ec_private_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_EC_PRIVATE);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_ec_private_copy(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_EC_PRIVATE, kth_py_native_wallet_ec_private_capsule_dtor);
    if (capsule == NULL) {
        kth_wallet_ec_private_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_wallet_ec_private_destruct(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_ec_private_mut_t self_handle = (kth_ec_private_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_EC_PRIVATE);
    if (self_handle == NULL) return NULL;
    kth_wallet_ec_private_destruct(self_handle);
    PyCapsule_SetName(py_self, "kth.destroyed");
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_wallet_ec_private_to_address_prefix(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"version", NULL};
    unsigned short version = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "H", kwlist, &version)) {
        return NULL;
    }
    auto const result = kth_wallet_ec_private_to_address_prefix((uint16_t)version);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyObject*
kth_py_native_wallet_ec_private_to_wif_prefix(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"version", NULL};
    unsigned short version = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "H", kwlist, &version)) {
        return NULL;
    }
    auto const result = kth_wallet_ec_private_to_wif_prefix((uint16_t)version);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyObject*
kth_py_native_wallet_ec_private_to_version(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"address", (char*)"wif", NULL};
    unsigned char address = 0;
    unsigned char wif = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "BB", kwlist, &address, &wif)) {
        return NULL;
    }
    auto const result = kth_wallet_ec_private_to_version((uint8_t)address, (uint8_t)wif);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyObject*
kth_py_native_wallet_ec_private_equals(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"other", NULL};
    PyObject* py_self = NULL;
    PyObject* py_other = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_other)) {
        return NULL;
    }
    kth_ec_private_const_t self_handle = (kth_ec_private_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_EC_PRIVATE);
    if (self_handle == NULL) return NULL;
    kth_ec_private_const_t other_handle = (kth_ec_private_const_t)PyCapsule_GetPointer(py_other, KTH_PY_CAPSULE_WALLET_EC_PRIVATE);
    if (other_handle == NULL) return NULL;
    auto const result = kth_wallet_ec_private_equals(self_handle, other_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_wallet_ec_private_less(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"x", NULL};
    PyObject* py_self = NULL;
    PyObject* py_x = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_x)) {
        return NULL;
    }
    kth_ec_private_const_t self_handle = (kth_ec_private_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_EC_PRIVATE);
    if (self_handle == NULL) return NULL;
    kth_ec_private_const_t x_handle = (kth_ec_private_const_t)PyCapsule_GetPointer(py_x, KTH_PY_CAPSULE_WALLET_EC_PRIVATE);
    if (x_handle == NULL) return NULL;
    auto const result = kth_wallet_ec_private_less(self_handle, x_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_wallet_ec_private_valid(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_ec_private_const_t self_handle = (kth_ec_private_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_EC_PRIVATE);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_ec_private_valid(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_wallet_ec_private_encoded(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_ec_private_const_t self_handle = (kth_ec_private_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_EC_PRIVATE);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_ec_private_encoded(self_handle);
    if (result == NULL) Py_RETURN_NONE;
    PyObject* py_result = Py_BuildValue("s", result);
    kth_core_destruct_string(result);
    return py_result;
}

PyObject*
kth_py_native_wallet_ec_private_secret(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_ec_private_const_t self_handle = (kth_ec_private_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_EC_PRIVATE);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_ec_private_secret(self_handle);
    return Py_BuildValue("y#", result.hash, (Py_ssize_t)KTH_BITCOIN_HASH_SIZE);
}

PyObject*
kth_py_native_wallet_ec_private_version(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_ec_private_const_t self_handle = (kth_ec_private_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_EC_PRIVATE);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_ec_private_version(self_handle);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyObject*
kth_py_native_wallet_ec_private_payment_version(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_ec_private_const_t self_handle = (kth_ec_private_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_EC_PRIVATE);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_ec_private_payment_version(self_handle);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyObject*
kth_py_native_wallet_ec_private_wif_version(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_ec_private_const_t self_handle = (kth_ec_private_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_EC_PRIVATE);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_ec_private_wif_version(self_handle);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyObject*
kth_py_native_wallet_ec_private_compressed(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_ec_private_const_t self_handle = (kth_ec_private_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_EC_PRIVATE);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_ec_private_compressed(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_wallet_ec_private_to_public(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_ec_private_const_t self_handle = (kth_ec_private_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_EC_PRIVATE);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_ec_private_to_public(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_EC_PUBLIC, kth_py_native_wallet_ec_public_capsule_dtor);
    if (capsule == NULL) {
        kth_wallet_ec_public_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_wallet_ec_private_to_payment_address(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_ec_private_const_t self_handle = (kth_ec_private_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_EC_PRIVATE);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_ec_private_to_payment_address(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_PAYMENT_ADDRESS, kth_py_native_wallet_payment_address_capsule_dtor);
    if (capsule == NULL) {
        kth_wallet_payment_address_destruct(result);
        return NULL;
    }
    return capsule;
}

PyMethodDef kth_py_native_wallet_ec_private_methods[] = {
    {"wallet_ec_private_construct_default", (PyCFunction)kth_py_native_wallet_ec_private_construct_default, METH_NOARGS, NULL},
    {"wallet_ec_private_construct_from_wif_version", (PyCFunction)kth_py_native_wallet_ec_private_construct_from_wif_version, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_ec_private_construct_from_wif_compressed_version", (PyCFunction)kth_py_native_wallet_ec_private_construct_from_wif_compressed_version, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_ec_private_construct_from_wif_uncompressed_version", (PyCFunction)kth_py_native_wallet_ec_private_construct_from_wif_uncompressed_version, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_ec_private_construct_from_secret_version_compress", (PyCFunction)kth_py_native_wallet_ec_private_construct_from_secret_version_compress, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_ec_private_copy", (PyCFunction)kth_py_native_wallet_ec_private_copy, METH_O, NULL},
    {"wallet_ec_private_destruct", (PyCFunction)kth_py_native_wallet_ec_private_destruct, METH_O, NULL},
    {"wallet_ec_private_to_address_prefix", (PyCFunction)kth_py_native_wallet_ec_private_to_address_prefix, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_ec_private_to_wif_prefix", (PyCFunction)kth_py_native_wallet_ec_private_to_wif_prefix, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_ec_private_to_version", (PyCFunction)kth_py_native_wallet_ec_private_to_version, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_ec_private_equals", (PyCFunction)kth_py_native_wallet_ec_private_equals, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_ec_private_less", (PyCFunction)kth_py_native_wallet_ec_private_less, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_ec_private_valid", (PyCFunction)kth_py_native_wallet_ec_private_valid, METH_O, NULL},
    {"wallet_ec_private_encoded", (PyCFunction)kth_py_native_wallet_ec_private_encoded, METH_O, NULL},
    {"wallet_ec_private_secret", (PyCFunction)kth_py_native_wallet_ec_private_secret, METH_O, NULL},
    {"wallet_ec_private_version", (PyCFunction)kth_py_native_wallet_ec_private_version, METH_O, NULL},
    {"wallet_ec_private_payment_version", (PyCFunction)kth_py_native_wallet_ec_private_payment_version, METH_O, NULL},
    {"wallet_ec_private_wif_version", (PyCFunction)kth_py_native_wallet_ec_private_wif_version, METH_O, NULL},
    {"wallet_ec_private_compressed", (PyCFunction)kth_py_native_wallet_ec_private_compressed, METH_O, NULL},
    {"wallet_ec_private_to_public", (PyCFunction)kth_py_native_wallet_ec_private_to_public, METH_O, NULL},
    {"wallet_ec_private_to_payment_address", (PyCFunction)kth_py_native_wallet_ec_private_to_payment_address, METH_O, NULL},
    {NULL, NULL, 0, NULL}  // sentinel
};

#ifdef __cplusplus
} // extern "C"
#endif
