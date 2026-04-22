// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/py-native/wallet/payment_address.h>

#include <string.h>
#include <kth/capi.h>
#include <kth/capi/wallet/payment_address.h>
#include <kth/py-native/capsule_names.h>
#include <kth/py-native/utils.h>

#ifdef __cplusplus
extern "C" {
#endif

// PyCapsule destructor — released by GC when the capsule is
// collected. Explicit `destruct` calls set the capsule name to
// "kth.destroyed", so PyCapsule_IsValid returns false and this
// destructor becomes a no-op (no double-free).
void kth_py_native_wallet_payment_address_capsule_dtor(PyObject* capsule) {
    if ( ! PyCapsule_IsValid(capsule, KTH_PY_CAPSULE_WALLET_PAYMENT_ADDRESS)) return;
    kth_payment_address_mut_t handle = (kth_payment_address_mut_t)PyCapsule_GetPointer(capsule, KTH_PY_CAPSULE_WALLET_PAYMENT_ADDRESS);
    if (handle != NULL) kth_wallet_payment_address_destruct(handle);
}

PyObject*
kth_py_native_wallet_payment_address_construct_default(PyObject* self, PyObject* Py_UNUSED(args)) {
    auto const result = kth_wallet_payment_address_construct_default();
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_PAYMENT_ADDRESS, kth_py_native_wallet_payment_address_capsule_dtor);
    if (capsule == NULL) {
        kth_wallet_payment_address_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_wallet_payment_address_construct_from_decoded(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"decoded", NULL};
    char const* decoded_buf = NULL;
    Py_ssize_t decoded_size = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "y#", kwlist, &decoded_buf, &decoded_size)) {
        return NULL;
    }
    if (decoded_size != (Py_ssize_t)KTH_BITCOIN_PAYMENT_SIZE) {
        PyErr_Format(PyExc_ValueError, "expected %d-byte decoded, got %zd", (int)KTH_BITCOIN_PAYMENT_SIZE, decoded_size);
        return NULL;
    }
    kth_payment_t decoded;
    memcpy(decoded.hash, decoded_buf, (size_t)KTH_BITCOIN_PAYMENT_SIZE);
    auto const result = kth_wallet_payment_address_construct_from_decoded(&decoded);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_PAYMENT_ADDRESS, kth_py_native_wallet_payment_address_capsule_dtor);
    if (capsule == NULL) {
        kth_wallet_payment_address_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_wallet_payment_address_construct_from_ec_private(PyObject* self, PyObject* py_arg0) {
    PyObject* py_secret = py_arg0;
    kth_ec_private_const_t secret_handle = (kth_ec_private_const_t)PyCapsule_GetPointer(py_secret, KTH_PY_CAPSULE_WALLET_EC_PRIVATE);
    if (secret_handle == NULL) return NULL;
    auto const result = kth_wallet_payment_address_construct_from_ec_private(secret_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_PAYMENT_ADDRESS, kth_py_native_wallet_payment_address_capsule_dtor);
    if (capsule == NULL) {
        kth_wallet_payment_address_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_wallet_payment_address_construct_from_address(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"address", NULL};
    char const* address = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "s", kwlist, &address)) {
        return NULL;
    }
    auto const result = kth_wallet_payment_address_construct_from_address(address);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_PAYMENT_ADDRESS, kth_py_native_wallet_payment_address_capsule_dtor);
    if (capsule == NULL) {
        kth_wallet_payment_address_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_wallet_payment_address_construct_from_address_net(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"address", (char*)"net", NULL};
    char const* address = NULL;
    unsigned long long net = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "sK", kwlist, &address, &net)) {
        return NULL;
    }
    auto const result = kth_wallet_payment_address_construct_from_address_net(address, (kth_network_t)net);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_PAYMENT_ADDRESS, kth_py_native_wallet_payment_address_capsule_dtor);
    if (capsule == NULL) {
        kth_wallet_payment_address_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_wallet_payment_address_construct_from_short_hash_version(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"short_hash", (char*)"version", NULL};
    char const* short_hash_buf = NULL;
    Py_ssize_t short_hash_size = 0;
    unsigned char version = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "y#B", kwlist, &short_hash_buf, &short_hash_size, &version)) {
        return NULL;
    }
    if (short_hash_size != (Py_ssize_t)KTH_BITCOIN_SHORT_HASH_SIZE) {
        PyErr_Format(PyExc_ValueError, "expected %d-byte short_hash, got %zd", (int)KTH_BITCOIN_SHORT_HASH_SIZE, short_hash_size);
        return NULL;
    }
    kth_shorthash_t short_hash;
    memcpy(short_hash.hash, short_hash_buf, (size_t)KTH_BITCOIN_SHORT_HASH_SIZE);
    auto const result = kth_wallet_payment_address_construct_from_short_hash_version(&short_hash, (uint8_t)version);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_PAYMENT_ADDRESS, kth_py_native_wallet_payment_address_capsule_dtor);
    if (capsule == NULL) {
        kth_wallet_payment_address_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_wallet_payment_address_construct_from_hash_version(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"hash", (char*)"version", NULL};
    char const* hash_buf = NULL;
    Py_ssize_t hash_size = 0;
    unsigned char version = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "y#B", kwlist, &hash_buf, &hash_size, &version)) {
        return NULL;
    }
    if (hash_size != (Py_ssize_t)KTH_BITCOIN_HASH_SIZE) {
        PyErr_Format(PyExc_ValueError, "expected %d-byte hash, got %zd", (int)KTH_BITCOIN_HASH_SIZE, hash_size);
        return NULL;
    }
    kth_hash_t hash;
    memcpy(hash.hash, hash_buf, (size_t)KTH_BITCOIN_HASH_SIZE);
    auto const result = kth_wallet_payment_address_construct_from_hash_version(&hash, (uint8_t)version);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_PAYMENT_ADDRESS, kth_py_native_wallet_payment_address_capsule_dtor);
    if (capsule == NULL) {
        kth_wallet_payment_address_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_wallet_payment_address_construct_from_ec_public_version(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"point", (char*)"version", NULL};
    PyObject* py_point = NULL;
    unsigned char version = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OB", kwlist, &py_point, &version)) {
        return NULL;
    }
    kth_ec_public_const_t point_handle = (kth_ec_public_const_t)PyCapsule_GetPointer(py_point, KTH_PY_CAPSULE_WALLET_EC_PUBLIC);
    if (point_handle == NULL) return NULL;
    auto const result = kth_wallet_payment_address_construct_from_ec_public_version(point_handle, (uint8_t)version);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_PAYMENT_ADDRESS, kth_py_native_wallet_payment_address_capsule_dtor);
    if (capsule == NULL) {
        kth_wallet_payment_address_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_wallet_payment_address_construct_from_script_version(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"script", (char*)"version", NULL};
    PyObject* py_script = NULL;
    unsigned char version = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OB", kwlist, &py_script, &version)) {
        return NULL;
    }
    kth_script_const_t script_handle = (kth_script_const_t)PyCapsule_GetPointer(py_script, KTH_PY_CAPSULE_CHAIN_SCRIPT);
    if (script_handle == NULL) return NULL;
    auto const result = kth_wallet_payment_address_construct_from_script_version(script_handle, (uint8_t)version);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_PAYMENT_ADDRESS, kth_py_native_wallet_payment_address_capsule_dtor);
    if (capsule == NULL) {
        kth_wallet_payment_address_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_wallet_payment_address_copy(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_payment_address_const_t self_handle = (kth_payment_address_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_PAYMENT_ADDRESS);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_payment_address_copy(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_PAYMENT_ADDRESS, kth_py_native_wallet_payment_address_capsule_dtor);
    if (capsule == NULL) {
        kth_wallet_payment_address_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_wallet_payment_address_destruct(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_payment_address_mut_t self_handle = (kth_payment_address_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_PAYMENT_ADDRESS);
    if (self_handle == NULL) return NULL;
    kth_wallet_payment_address_destruct(self_handle);
    PyCapsule_SetName(py_self, "kth.destroyed");
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_wallet_payment_address_cashaddr_prefix_for(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"net", NULL};
    unsigned long long net = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "K", kwlist, &net)) {
        return NULL;
    }
    auto const result = kth_wallet_payment_address_cashaddr_prefix_for((kth_network_t)net);
    if (result == NULL) Py_RETURN_NONE;
    PyObject* py_result = Py_BuildValue("s", result);
    kth_core_destruct_string(result);
    return py_result;
}

PyObject*
kth_py_native_wallet_payment_address_from_pay_public_key_hash_script(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"script", (char*)"version", NULL};
    PyObject* py_script = NULL;
    unsigned char version = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OB", kwlist, &py_script, &version)) {
        return NULL;
    }
    kth_script_const_t script_handle = (kth_script_const_t)PyCapsule_GetPointer(py_script, KTH_PY_CAPSULE_CHAIN_SCRIPT);
    if (script_handle == NULL) return NULL;
    auto const result = kth_wallet_payment_address_from_pay_public_key_hash_script(script_handle, (uint8_t)version);
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

PyObject*
kth_py_native_wallet_payment_address_equals(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"other", NULL};
    PyObject* py_self = NULL;
    PyObject* py_other = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_other)) {
        return NULL;
    }
    kth_payment_address_const_t self_handle = (kth_payment_address_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_PAYMENT_ADDRESS);
    if (self_handle == NULL) return NULL;
    kth_payment_address_const_t other_handle = (kth_payment_address_const_t)PyCapsule_GetPointer(py_other, KTH_PY_CAPSULE_WALLET_PAYMENT_ADDRESS);
    if (other_handle == NULL) return NULL;
    auto const result = kth_wallet_payment_address_equals(self_handle, other_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_wallet_payment_address_less(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"x", NULL};
    PyObject* py_self = NULL;
    PyObject* py_x = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_x)) {
        return NULL;
    }
    kth_payment_address_const_t self_handle = (kth_payment_address_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_PAYMENT_ADDRESS);
    if (self_handle == NULL) return NULL;
    kth_payment_address_const_t x_handle = (kth_payment_address_const_t)PyCapsule_GetPointer(py_x, KTH_PY_CAPSULE_WALLET_PAYMENT_ADDRESS);
    if (x_handle == NULL) return NULL;
    auto const result = kth_wallet_payment_address_less(self_handle, x_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_wallet_payment_address_valid(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_payment_address_const_t self_handle = (kth_payment_address_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_PAYMENT_ADDRESS);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_payment_address_valid(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_wallet_payment_address_encoded_legacy(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_payment_address_const_t self_handle = (kth_payment_address_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_PAYMENT_ADDRESS);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_payment_address_encoded_legacy(self_handle);
    if (result == NULL) Py_RETURN_NONE;
    PyObject* py_result = Py_BuildValue("s", result);
    kth_core_destruct_string(result);
    return py_result;
}

PyObject*
kth_py_native_wallet_payment_address_encoded_cashaddr(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"token_aware", NULL};
    PyObject* py_self = NULL;
    int token_aware = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Op", kwlist, &py_self, &token_aware)) {
        return NULL;
    }
    kth_payment_address_const_t self_handle = (kth_payment_address_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_PAYMENT_ADDRESS);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_payment_address_encoded_cashaddr(self_handle, (kth_bool_t)token_aware);
    if (result == NULL) Py_RETURN_NONE;
    PyObject* py_result = Py_BuildValue("s", result);
    kth_core_destruct_string(result);
    return py_result;
}

PyObject*
kth_py_native_wallet_payment_address_encoded_token(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_payment_address_const_t self_handle = (kth_payment_address_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_PAYMENT_ADDRESS);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_payment_address_encoded_token(self_handle);
    if (result == NULL) Py_RETURN_NONE;
    PyObject* py_result = Py_BuildValue("s", result);
    kth_core_destruct_string(result);
    return py_result;
}

PyObject*
kth_py_native_wallet_payment_address_version(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_payment_address_const_t self_handle = (kth_payment_address_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_PAYMENT_ADDRESS);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_payment_address_version(self_handle);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyObject*
kth_py_native_wallet_payment_address_hash_span(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_payment_address_const_t self_handle = (kth_payment_address_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_PAYMENT_ADDRESS);
    if (self_handle == NULL) return NULL;
    kth_size_t out_size = 0;
    auto const result = kth_wallet_payment_address_hash_span(self_handle, &out_size);
    if (result == NULL) {
        Py_RETURN_NONE;
    }
    return Py_BuildValue("y#", result, (Py_ssize_t)out_size);
}

PyObject*
kth_py_native_wallet_payment_address_hash20(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_payment_address_const_t self_handle = (kth_payment_address_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_PAYMENT_ADDRESS);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_payment_address_hash20(self_handle);
    return Py_BuildValue("y#", result.hash, (Py_ssize_t)KTH_BITCOIN_SHORT_HASH_SIZE);
}

PyObject*
kth_py_native_wallet_payment_address_hash32(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_payment_address_const_t self_handle = (kth_payment_address_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_PAYMENT_ADDRESS);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_payment_address_hash32(self_handle);
    return Py_BuildValue("y#", result.hash, (Py_ssize_t)KTH_BITCOIN_HASH_SIZE);
}

PyObject*
kth_py_native_wallet_payment_address_to_payment(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_payment_address_const_t self_handle = (kth_payment_address_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_PAYMENT_ADDRESS);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_payment_address_to_payment(self_handle);
    return Py_BuildValue("y#", result.hash, (Py_ssize_t)KTH_BITCOIN_PAYMENT_SIZE);
}

PyObject*
kth_py_native_wallet_payment_address_extract(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"script", (char*)"p2kh_version", (char*)"p2sh_version", NULL};
    PyObject* py_script = NULL;
    unsigned char p2kh_version = 0;
    unsigned char p2sh_version = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OBB", kwlist, &py_script, &p2kh_version, &p2sh_version)) {
        return NULL;
    }
    kth_script_const_t script_handle = (kth_script_const_t)PyCapsule_GetPointer(py_script, KTH_PY_CAPSULE_CHAIN_SCRIPT);
    if (script_handle == NULL) return NULL;
    auto const result = kth_wallet_payment_address_extract(script_handle, (uint8_t)p2kh_version, (uint8_t)p2sh_version);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL list returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_PAYMENT_ADDRESS_LIST, kth_py_native_wallet_payment_address_list_capsule_dtor);
    if (capsule == NULL) {
        kth_wallet_payment_address_list_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_wallet_payment_address_extract_input(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"script", (char*)"p2kh_version", (char*)"p2sh_version", NULL};
    PyObject* py_script = NULL;
    unsigned char p2kh_version = 0;
    unsigned char p2sh_version = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OBB", kwlist, &py_script, &p2kh_version, &p2sh_version)) {
        return NULL;
    }
    kth_script_const_t script_handle = (kth_script_const_t)PyCapsule_GetPointer(py_script, KTH_PY_CAPSULE_CHAIN_SCRIPT);
    if (script_handle == NULL) return NULL;
    auto const result = kth_wallet_payment_address_extract_input(script_handle, (uint8_t)p2kh_version, (uint8_t)p2sh_version);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL list returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_PAYMENT_ADDRESS_LIST, kth_py_native_wallet_payment_address_list_capsule_dtor);
    if (capsule == NULL) {
        kth_wallet_payment_address_list_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_wallet_payment_address_extract_output(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"script", (char*)"p2kh_version", (char*)"p2sh_version", NULL};
    PyObject* py_script = NULL;
    unsigned char p2kh_version = 0;
    unsigned char p2sh_version = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OBB", kwlist, &py_script, &p2kh_version, &p2sh_version)) {
        return NULL;
    }
    kth_script_const_t script_handle = (kth_script_const_t)PyCapsule_GetPointer(py_script, KTH_PY_CAPSULE_CHAIN_SCRIPT);
    if (script_handle == NULL) return NULL;
    auto const result = kth_wallet_payment_address_extract_output(script_handle, (uint8_t)p2kh_version, (uint8_t)p2sh_version);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL list returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_PAYMENT_ADDRESS_LIST, kth_py_native_wallet_payment_address_list_capsule_dtor);
    if (capsule == NULL) {
        kth_wallet_payment_address_list_destruct(result);
        return NULL;
    }
    return capsule;
}

PyMethodDef kth_py_native_wallet_payment_address_methods[] = {
    {"wallet_payment_address_construct_default", (PyCFunction)kth_py_native_wallet_payment_address_construct_default, METH_NOARGS, NULL},
    {"wallet_payment_address_construct_from_decoded", (PyCFunction)kth_py_native_wallet_payment_address_construct_from_decoded, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_payment_address_construct_from_ec_private", (PyCFunction)kth_py_native_wallet_payment_address_construct_from_ec_private, METH_O, NULL},
    {"wallet_payment_address_construct_from_address", (PyCFunction)kth_py_native_wallet_payment_address_construct_from_address, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_payment_address_construct_from_address_net", (PyCFunction)kth_py_native_wallet_payment_address_construct_from_address_net, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_payment_address_construct_from_short_hash_version", (PyCFunction)kth_py_native_wallet_payment_address_construct_from_short_hash_version, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_payment_address_construct_from_hash_version", (PyCFunction)kth_py_native_wallet_payment_address_construct_from_hash_version, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_payment_address_construct_from_ec_public_version", (PyCFunction)kth_py_native_wallet_payment_address_construct_from_ec_public_version, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_payment_address_construct_from_script_version", (PyCFunction)kth_py_native_wallet_payment_address_construct_from_script_version, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_payment_address_copy", (PyCFunction)kth_py_native_wallet_payment_address_copy, METH_O, NULL},
    {"wallet_payment_address_destruct", (PyCFunction)kth_py_native_wallet_payment_address_destruct, METH_O, NULL},
    {"wallet_payment_address_cashaddr_prefix_for", (PyCFunction)kth_py_native_wallet_payment_address_cashaddr_prefix_for, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_payment_address_from_pay_public_key_hash_script", (PyCFunction)kth_py_native_wallet_payment_address_from_pay_public_key_hash_script, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_payment_address_equals", (PyCFunction)kth_py_native_wallet_payment_address_equals, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_payment_address_less", (PyCFunction)kth_py_native_wallet_payment_address_less, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_payment_address_valid", (PyCFunction)kth_py_native_wallet_payment_address_valid, METH_O, NULL},
    {"wallet_payment_address_encoded_legacy", (PyCFunction)kth_py_native_wallet_payment_address_encoded_legacy, METH_O, NULL},
    {"wallet_payment_address_encoded_cashaddr", (PyCFunction)kth_py_native_wallet_payment_address_encoded_cashaddr, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_payment_address_encoded_token", (PyCFunction)kth_py_native_wallet_payment_address_encoded_token, METH_O, NULL},
    {"wallet_payment_address_version", (PyCFunction)kth_py_native_wallet_payment_address_version, METH_O, NULL},
    {"wallet_payment_address_hash_span", (PyCFunction)kth_py_native_wallet_payment_address_hash_span, METH_O, NULL},
    {"wallet_payment_address_hash20", (PyCFunction)kth_py_native_wallet_payment_address_hash20, METH_O, NULL},
    {"wallet_payment_address_hash32", (PyCFunction)kth_py_native_wallet_payment_address_hash32, METH_O, NULL},
    {"wallet_payment_address_to_payment", (PyCFunction)kth_py_native_wallet_payment_address_to_payment, METH_O, NULL},
    {"wallet_payment_address_extract", (PyCFunction)kth_py_native_wallet_payment_address_extract, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_payment_address_extract_input", (PyCFunction)kth_py_native_wallet_payment_address_extract_input, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_payment_address_extract_output", (PyCFunction)kth_py_native_wallet_payment_address_extract_output, METH_VARARGS | METH_KEYWORDS, NULL},
    {NULL, NULL, 0, NULL}  // sentinel
};

#ifdef __cplusplus
} // extern "C"
#endif
