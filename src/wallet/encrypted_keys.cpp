// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/py-native/wallet/encrypted_keys.h>

#include <string.h>
#include <kth/capi.h>
#include <kth/capi/wallet/encrypted_keys.h>
#include <kth/py-native/capsule_names.h>
#include <kth/py-native/utils.h>

#ifdef __cplusplus
extern "C" {
#endif

PyObject*
kth_py_native_wallet_encrypted_keys_create_key_pair(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"out_private", (char*)"out_point", (char*)"token", (char*)"seed", (char*)"version", (char*)"compressed", NULL};
    char const* out_private_buf = NULL;
    Py_ssize_t out_private_size = 0;
    char const* out_point_buf = NULL;
    Py_ssize_t out_point_size = 0;
    char const* token_buf = NULL;
    Py_ssize_t token_size = 0;
    char const* seed_buf = NULL;
    Py_ssize_t seed_size = 0;
    unsigned char version = 0;
    int compressed = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "y#y#y#y#Bp", kwlist, &out_private_buf, &out_private_size, &out_point_buf, &out_point_size, &token_buf, &token_size, &seed_buf, &seed_size, &version, &compressed)) {
        return NULL;
    }
    if (out_private_size != (Py_ssize_t)43) {
        PyErr_Format(PyExc_ValueError, "expected %d-byte out_private, got %zd", (int)43, out_private_size);
        return NULL;
    }
    kth_encrypted_private_t out_private;
    memcpy(out_private.data, out_private_buf, (size_t)43);
    if (out_point_size != (Py_ssize_t)KTH_EC_COMPRESSED_SIZE) {
        PyErr_Format(PyExc_ValueError, "expected %d-byte out_point, got %zd", (int)KTH_EC_COMPRESSED_SIZE, out_point_size);
        return NULL;
    }
    kth_ec_compressed_t out_point;
    memcpy(out_point.data, out_point_buf, (size_t)KTH_EC_COMPRESSED_SIZE);
    if (token_size != (Py_ssize_t)53) {
        PyErr_Format(PyExc_ValueError, "expected %d-byte token, got %zd", (int)53, token_size);
        return NULL;
    }
    kth_encrypted_token_t token;
    memcpy(token.data, token_buf, (size_t)53);
    if (seed_size != (Py_ssize_t)24) {
        PyErr_Format(PyExc_ValueError, "expected %d-byte seed, got %zd", (int)24, seed_size);
        return NULL;
    }
    kth_ek_seed_t seed;
    memcpy(seed.data, seed_buf, (size_t)24);
    auto const result = kth_wallet_encrypted_keys_create_key_pair(&out_private, &out_point, &token, &seed, (uint8_t)version, (kth_bool_t)compressed);
    kth_core_secure_zero((void*)&out_private, sizeof(kth_encrypted_private_t));
    return PyBool_FromLong((long)result);
}

PyMethodDef kth_py_native_wallet_encrypted_keys_methods[] = {
    {"wallet_encrypted_keys_create_key_pair", (PyCFunction)kth_py_native_wallet_encrypted_keys_create_key_pair, METH_VARARGS | METH_KEYWORDS, NULL},
    {NULL, NULL, 0, NULL}  // sentinel
};

#ifdef __cplusplus
} // extern "C"
#endif
