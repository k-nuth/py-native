// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/py-native/wallet/ec_public.h>

#include <string.h>
#include <kth/capi.h>
#include <kth/capi/wallet/ec_public.h>
#include <kth/py-native/capsule_names.h>
#include <kth/py-native/utils.h>

#ifdef __cplusplus
extern "C" {
#endif

// PyCapsule destructor — released by GC when the capsule is
// collected. Explicit `destruct` calls set the capsule name to
// "kth.destroyed", so PyCapsule_IsValid returns false and this
// destructor becomes a no-op (no double-free).
void kth_py_native_wallet_ec_public_capsule_dtor(PyObject* capsule) {
    if ( ! PyCapsule_IsValid(capsule, KTH_PY_CAPSULE_WALLET_EC_PUBLIC)) return;
    kth_ec_public_mut_t handle = (kth_ec_public_mut_t)PyCapsule_GetPointer(capsule, KTH_PY_CAPSULE_WALLET_EC_PUBLIC);
    if (handle != NULL) kth_wallet_ec_public_destruct(handle);
}

PyObject*
kth_py_native_wallet_ec_public_construct_default(PyObject* self, PyObject* Py_UNUSED(args)) {
    auto const result = kth_wallet_ec_public_construct_default();
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
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
kth_py_native_wallet_ec_public_construct_from_ec_private(PyObject* self, PyObject* py_arg0) {
    PyObject* py_secret = py_arg0;
    kth_ec_private_const_t secret_handle = (kth_ec_private_const_t)PyCapsule_GetPointer(py_secret, KTH_PY_CAPSULE_WALLET_EC_PRIVATE);
    if (secret_handle == NULL) return NULL;
    auto const result = kth_wallet_ec_public_construct_from_ec_private(secret_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
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
kth_py_native_wallet_ec_public_construct_from_decoded(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"decoded", NULL};
    char const* decoded_buf = NULL;
    Py_ssize_t decoded_size = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "y#", kwlist, &decoded_buf, &decoded_size)) {
        return NULL;
    }
    auto const result = kth_wallet_ec_public_construct_from_decoded((uint8_t const*)decoded_buf, (kth_size_t)decoded_size);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
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
kth_py_native_wallet_ec_public_construct_from_base16(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"base16", NULL};
    char const* base16 = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "s", kwlist, &base16)) {
        return NULL;
    }
    auto const result = kth_wallet_ec_public_construct_from_base16(base16);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
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
kth_py_native_wallet_ec_public_construct_from_compressed_point_compress(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"compressed_point", (char*)"compress", NULL};
    char const* compressed_point_buf = NULL;
    Py_ssize_t compressed_point_size = 0;
    int compress = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "y#p", kwlist, &compressed_point_buf, &compressed_point_size, &compress)) {
        return NULL;
    }
    if (compressed_point_size != (Py_ssize_t)KTH_EC_COMPRESSED_SIZE) {
        PyErr_Format(PyExc_ValueError, "expected %d-byte compressed_point, got %zd", (int)KTH_EC_COMPRESSED_SIZE, compressed_point_size);
        return NULL;
    }
    kth_ec_compressed_t compressed_point;
    memcpy(compressed_point.data, compressed_point_buf, (size_t)KTH_EC_COMPRESSED_SIZE);
    auto const result = kth_wallet_ec_public_construct_from_compressed_point_compress(&compressed_point, (kth_bool_t)compress);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
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
kth_py_native_wallet_ec_public_construct_from_uncompressed_point_compress(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"uncompressed_point", (char*)"compress", NULL};
    char const* uncompressed_point_buf = NULL;
    Py_ssize_t uncompressed_point_size = 0;
    int compress = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "y#p", kwlist, &uncompressed_point_buf, &uncompressed_point_size, &compress)) {
        return NULL;
    }
    if (uncompressed_point_size != (Py_ssize_t)KTH_BITCOIN_EC_UNCOMPRESSED_SIZE) {
        PyErr_Format(PyExc_ValueError, "expected %d-byte uncompressed_point, got %zd", (int)KTH_BITCOIN_EC_UNCOMPRESSED_SIZE, uncompressed_point_size);
        return NULL;
    }
    kth_ec_uncompressed_t uncompressed_point;
    memcpy(uncompressed_point.data, uncompressed_point_buf, (size_t)KTH_BITCOIN_EC_UNCOMPRESSED_SIZE);
    auto const result = kth_wallet_ec_public_construct_from_uncompressed_point_compress(&uncompressed_point, (kth_bool_t)compress);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
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
kth_py_native_wallet_ec_public_copy(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_ec_public_const_t self_handle = (kth_ec_public_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_EC_PUBLIC);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_ec_public_copy(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
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
kth_py_native_wallet_ec_public_destruct(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_ec_public_mut_t self_handle = (kth_ec_public_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_EC_PUBLIC);
    if (self_handle == NULL) return NULL;
    kth_wallet_ec_public_destruct(self_handle);
    PyCapsule_SetName(py_self, "kth.destroyed");
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_wallet_ec_public_equals(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"other", NULL};
    PyObject* py_self = NULL;
    PyObject* py_other = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_other)) {
        return NULL;
    }
    kth_ec_public_const_t self_handle = (kth_ec_public_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_EC_PUBLIC);
    if (self_handle == NULL) return NULL;
    kth_ec_public_const_t other_handle = (kth_ec_public_const_t)PyCapsule_GetPointer(py_other, KTH_PY_CAPSULE_WALLET_EC_PUBLIC);
    if (other_handle == NULL) return NULL;
    auto const result = kth_wallet_ec_public_equals(self_handle, other_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_wallet_ec_public_less(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"x", NULL};
    PyObject* py_self = NULL;
    PyObject* py_x = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_x)) {
        return NULL;
    }
    kth_ec_public_const_t self_handle = (kth_ec_public_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_EC_PUBLIC);
    if (self_handle == NULL) return NULL;
    kth_ec_public_const_t x_handle = (kth_ec_public_const_t)PyCapsule_GetPointer(py_x, KTH_PY_CAPSULE_WALLET_EC_PUBLIC);
    if (x_handle == NULL) return NULL;
    auto const result = kth_wallet_ec_public_less(self_handle, x_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_wallet_ec_public_valid(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_ec_public_const_t self_handle = (kth_ec_public_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_EC_PUBLIC);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_ec_public_valid(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_wallet_ec_public_encoded(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_ec_public_const_t self_handle = (kth_ec_public_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_EC_PUBLIC);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_ec_public_encoded(self_handle);
    if (result == NULL) Py_RETURN_NONE;
    PyObject* py_result = Py_BuildValue("s", result);
    kth_core_destruct_string(result);
    return py_result;
}

PyObject*
kth_py_native_wallet_ec_public_point(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_ec_public_const_t self_handle = (kth_ec_public_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_EC_PUBLIC);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_ec_public_point(self_handle);
    return Py_BuildValue("y#", result.data, (Py_ssize_t)KTH_EC_COMPRESSED_SIZE);
}

PyObject*
kth_py_native_wallet_ec_public_compressed(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_ec_public_const_t self_handle = (kth_ec_public_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_EC_PUBLIC);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_ec_public_compressed(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_wallet_ec_public_to_data(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_ec_public_const_t self_handle = (kth_ec_public_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_EC_PUBLIC);
    if (self_handle == NULL) return NULL;
    uint8_t* out = NULL;
    kth_size_t out_size = 0;
    kth_error_code_t result = kth_wallet_ec_public_to_data(self_handle, &out, &out_size);
    if (result != kth_ec_success) {
        PyErr_Format(PyExc_RuntimeError, "kth error code %d", (int)result);
        return NULL;
    }
    PyObject* py_result = Py_BuildValue("y#", out, (Py_ssize_t)out_size);
    kth_core_destruct_array(out);
    return py_result;
}

PyObject*
kth_py_native_wallet_ec_public_to_uncompressed(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_ec_public_const_t self_handle = (kth_ec_public_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_EC_PUBLIC);
    if (self_handle == NULL) return NULL;
    uint8_t out[KTH_BITCOIN_EC_UNCOMPRESSED_SIZE];
    kth_error_code_t result = kth_wallet_ec_public_to_uncompressed(self_handle, out, (kth_size_t)KTH_BITCOIN_EC_UNCOMPRESSED_SIZE);
    if (result != kth_ec_success) {
        PyErr_Format(PyExc_RuntimeError, "kth error code %d", (int)result);
        return NULL;
    }
    return Py_BuildValue("y#", out, (Py_ssize_t)KTH_BITCOIN_EC_UNCOMPRESSED_SIZE);
}

PyObject*
kth_py_native_wallet_ec_public_to_payment_address(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"version", NULL};
    PyObject* py_self = NULL;
    unsigned char version = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OB", kwlist, &py_self, &version)) {
        return NULL;
    }
    kth_ec_public_const_t self_handle = (kth_ec_public_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_EC_PUBLIC);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_ec_public_to_payment_address(self_handle, (uint8_t)version);
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

PyMethodDef kth_py_native_wallet_ec_public_methods[] = {
    {"wallet_ec_public_construct_default", (PyCFunction)kth_py_native_wallet_ec_public_construct_default, METH_NOARGS, NULL},
    {"wallet_ec_public_construct_from_ec_private", (PyCFunction)kth_py_native_wallet_ec_public_construct_from_ec_private, METH_O, NULL},
    {"wallet_ec_public_construct_from_decoded", (PyCFunction)kth_py_native_wallet_ec_public_construct_from_decoded, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_ec_public_construct_from_base16", (PyCFunction)kth_py_native_wallet_ec_public_construct_from_base16, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_ec_public_construct_from_compressed_point_compress", (PyCFunction)kth_py_native_wallet_ec_public_construct_from_compressed_point_compress, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_ec_public_construct_from_uncompressed_point_compress", (PyCFunction)kth_py_native_wallet_ec_public_construct_from_uncompressed_point_compress, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_ec_public_copy", (PyCFunction)kth_py_native_wallet_ec_public_copy, METH_O, NULL},
    {"wallet_ec_public_destruct", (PyCFunction)kth_py_native_wallet_ec_public_destruct, METH_O, NULL},
    {"wallet_ec_public_equals", (PyCFunction)kth_py_native_wallet_ec_public_equals, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_ec_public_less", (PyCFunction)kth_py_native_wallet_ec_public_less, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_ec_public_valid", (PyCFunction)kth_py_native_wallet_ec_public_valid, METH_O, NULL},
    {"wallet_ec_public_encoded", (PyCFunction)kth_py_native_wallet_ec_public_encoded, METH_O, NULL},
    {"wallet_ec_public_point", (PyCFunction)kth_py_native_wallet_ec_public_point, METH_O, NULL},
    {"wallet_ec_public_compressed", (PyCFunction)kth_py_native_wallet_ec_public_compressed, METH_O, NULL},
    {"wallet_ec_public_to_data", (PyCFunction)kth_py_native_wallet_ec_public_to_data, METH_O, NULL},
    {"wallet_ec_public_to_uncompressed", (PyCFunction)kth_py_native_wallet_ec_public_to_uncompressed, METH_O, NULL},
    {"wallet_ec_public_to_payment_address", (PyCFunction)kth_py_native_wallet_ec_public_to_payment_address, METH_VARARGS | METH_KEYWORDS, NULL},
    {NULL, NULL, 0, NULL}  // sentinel
};

#ifdef __cplusplus
} // extern "C"
#endif
