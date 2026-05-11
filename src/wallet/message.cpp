// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/py-native/wallet/message.h>

#include <string.h>
#include <kth/capi.h>
#include <kth/capi/wallet/message.h>
#include <kth/py-native/capsule_names.h>
#include <kth/py-native/utils.h>

#ifdef __cplusplus
extern "C" {
#endif

PyObject*
kth_py_native_wallet_message_hash_message(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"message", NULL};
    char const* message_buf = NULL;
    Py_ssize_t message_size = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "y#", kwlist, &message_buf, &message_size)) {
        return NULL;
    }
    auto const result = kth_wallet_message_hash_message((uint8_t const*)message_buf, (kth_size_t)message_size);
    return Py_BuildValue("y#", result.hash, (Py_ssize_t)KTH_BITCOIN_HASH_SIZE);
}

PyObject*
kth_py_native_wallet_message_sign_message_ec_private(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"out_signature", (char*)"message", (char*)"secret", NULL};
    char const* out_signature_buf = NULL;
    Py_ssize_t out_signature_size = 0;
    char const* message_buf = NULL;
    Py_ssize_t message_size = 0;
    PyObject* py_secret = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "y#y#O", kwlist, &out_signature_buf, &out_signature_size, &message_buf, &message_size, &py_secret)) {
        return NULL;
    }
    if (out_signature_size != (Py_ssize_t)KTH_BITCOIN_EC_UNCOMPRESSED_SIZE) {
        PyErr_Format(PyExc_ValueError, "expected %d-byte out_signature, got %zd", (int)KTH_BITCOIN_EC_UNCOMPRESSED_SIZE, out_signature_size);
        return NULL;
    }
    kth_message_signature_t out_signature;
    memcpy(out_signature.data, out_signature_buf, (size_t)KTH_BITCOIN_EC_UNCOMPRESSED_SIZE);
    kth_ec_private_const_t secret_handle = (kth_ec_private_const_t)PyCapsule_GetPointer(py_secret, KTH_PY_CAPSULE_WALLET_EC_PRIVATE);
    if (secret_handle == NULL) return NULL;
    auto const result = kth_wallet_message_sign_message_ec_private(&out_signature, (uint8_t const*)message_buf, (kth_size_t)message_size, secret_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_wallet_message_sign_message_string(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"out_signature", (char*)"message", (char*)"wif", NULL};
    char const* out_signature_buf = NULL;
    Py_ssize_t out_signature_size = 0;
    char const* message_buf = NULL;
    Py_ssize_t message_size = 0;
    char const* wif = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "y#y#s", kwlist, &out_signature_buf, &out_signature_size, &message_buf, &message_size, &wif)) {
        return NULL;
    }
    if (out_signature_size != (Py_ssize_t)KTH_BITCOIN_EC_UNCOMPRESSED_SIZE) {
        PyErr_Format(PyExc_ValueError, "expected %d-byte out_signature, got %zd", (int)KTH_BITCOIN_EC_UNCOMPRESSED_SIZE, out_signature_size);
        return NULL;
    }
    kth_message_signature_t out_signature;
    memcpy(out_signature.data, out_signature_buf, (size_t)KTH_BITCOIN_EC_UNCOMPRESSED_SIZE);
    auto const result = kth_wallet_message_sign_message_string(&out_signature, (uint8_t const*)message_buf, (kth_size_t)message_size, wif);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_wallet_message_sign_message_hash(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"out_signature", (char*)"message", (char*)"secret", (char*)"compressed", NULL};
    char const* out_signature_buf = NULL;
    Py_ssize_t out_signature_size = 0;
    char const* message_buf = NULL;
    Py_ssize_t message_size = 0;
    char const* secret_buf = NULL;
    Py_ssize_t secret_size = 0;
    int compressed = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "y#y#y#p", kwlist, &out_signature_buf, &out_signature_size, &message_buf, &message_size, &secret_buf, &secret_size, &compressed)) {
        return NULL;
    }
    if (out_signature_size != (Py_ssize_t)KTH_BITCOIN_EC_UNCOMPRESSED_SIZE) {
        PyErr_Format(PyExc_ValueError, "expected %d-byte out_signature, got %zd", (int)KTH_BITCOIN_EC_UNCOMPRESSED_SIZE, out_signature_size);
        return NULL;
    }
    kth_message_signature_t out_signature;
    memcpy(out_signature.data, out_signature_buf, (size_t)KTH_BITCOIN_EC_UNCOMPRESSED_SIZE);
    if (secret_size != (Py_ssize_t)KTH_BITCOIN_HASH_SIZE) {
        PyErr_Format(PyExc_ValueError, "expected %d-byte secret, got %zd", (int)KTH_BITCOIN_HASH_SIZE, secret_size);
        return NULL;
    }
    kth_hash_t secret;
    memcpy(secret.hash, secret_buf, (size_t)KTH_BITCOIN_HASH_SIZE);
    auto const result = kth_wallet_message_sign_message_hash(&out_signature, (uint8_t const*)message_buf, (kth_size_t)message_size, &secret, (kth_bool_t)compressed);
    kth_core_secure_zero((void*)&secret, sizeof(kth_hash_t));
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_wallet_message_verify_message(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"message", (char*)"address", (char*)"signature", NULL};
    char const* message_buf = NULL;
    Py_ssize_t message_size = 0;
    PyObject* py_address = NULL;
    char const* signature_buf = NULL;
    Py_ssize_t signature_size = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "y#Oy#", kwlist, &message_buf, &message_size, &py_address, &signature_buf, &signature_size)) {
        return NULL;
    }
    kth_payment_address_const_t address_handle = (kth_payment_address_const_t)PyCapsule_GetPointer(py_address, KTH_PY_CAPSULE_WALLET_PAYMENT_ADDRESS);
    if (address_handle == NULL) return NULL;
    if (signature_size != (Py_ssize_t)KTH_BITCOIN_EC_UNCOMPRESSED_SIZE) {
        PyErr_Format(PyExc_ValueError, "expected %d-byte signature, got %zd", (int)KTH_BITCOIN_EC_UNCOMPRESSED_SIZE, signature_size);
        return NULL;
    }
    kth_message_signature_t signature;
    memcpy(signature.data, signature_buf, (size_t)KTH_BITCOIN_EC_UNCOMPRESSED_SIZE);
    auto const result = kth_wallet_message_verify_message((uint8_t const*)message_buf, (kth_size_t)message_size, address_handle, &signature);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_wallet_message_recovery_id_to_magic(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"out_magic", (char*)"recovery_id", (char*)"compressed", NULL};
    unsigned char out_magic = 0;
    unsigned char recovery_id = 0;
    int compressed = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "BBp", kwlist, &out_magic, &recovery_id, &compressed)) {
        return NULL;
    }
    auto const result = kth_wallet_message_recovery_id_to_magic((uint8_t)out_magic, (uint8_t)recovery_id, (kth_bool_t)compressed);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_wallet_message_magic_to_recovery_id(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"out_recovery_id", (char*)"out_compressed", (char*)"magic", NULL};
    unsigned char out_recovery_id = 0;
    int out_compressed = 0;
    unsigned char magic = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "BpB", kwlist, &out_recovery_id, &out_compressed, &magic)) {
        return NULL;
    }
    auto const result = kth_wallet_message_magic_to_recovery_id((uint8_t)out_recovery_id, (kth_bool_t)out_compressed, (uint8_t)magic);
    return PyBool_FromLong((long)result);
}

PyMethodDef kth_py_native_wallet_message_methods[] = {
    {"wallet_message_hash_message", (PyCFunction)kth_py_native_wallet_message_hash_message, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_message_sign_message_ec_private", (PyCFunction)kth_py_native_wallet_message_sign_message_ec_private, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_message_sign_message_string", (PyCFunction)kth_py_native_wallet_message_sign_message_string, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_message_sign_message_hash", (PyCFunction)kth_py_native_wallet_message_sign_message_hash, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_message_verify_message", (PyCFunction)kth_py_native_wallet_message_verify_message, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_message_recovery_id_to_magic", (PyCFunction)kth_py_native_wallet_message_recovery_id_to_magic, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_message_magic_to_recovery_id", (PyCFunction)kth_py_native_wallet_message_magic_to_recovery_id, METH_VARARGS | METH_KEYWORDS, NULL},
    {NULL, NULL, 0, NULL}  // sentinel
};

#ifdef __cplusplus
} // extern "C"
#endif
