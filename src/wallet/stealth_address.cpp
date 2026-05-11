// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/py-native/wallet/stealth_address.h>

#include <string.h>
#include <kth/capi.h>
#include <kth/capi/wallet/stealth_address.h>
#include <kth/py-native/capsule_names.h>
#include <kth/py-native/utils.h>

#ifdef __cplusplus
extern "C" {
#endif

// PyCapsule destructor — released by GC when the capsule is
// collected. Explicit `destruct` calls set the capsule name to
// "kth.destroyed", so PyCapsule_IsValid returns false and this
// destructor becomes a no-op (no double-free).
void kth_py_native_wallet_stealth_address_capsule_dtor(PyObject* capsule) {
    if ( ! PyCapsule_IsValid(capsule, KTH_PY_CAPSULE_WALLET_STEALTH_ADDRESS)) return;
    kth_stealth_address_mut_t handle = (kth_stealth_address_mut_t)PyCapsule_GetPointer(capsule, KTH_PY_CAPSULE_WALLET_STEALTH_ADDRESS);
    if (handle != NULL) kth_wallet_stealth_address_destruct(handle);
}

PyObject*
kth_py_native_wallet_stealth_address_construct_default(PyObject* self, PyObject* Py_UNUSED(args)) {
    auto const result = kth_wallet_stealth_address_construct_default();
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_STEALTH_ADDRESS, kth_py_native_wallet_stealth_address_capsule_dtor);
    if (capsule == NULL) {
        kth_wallet_stealth_address_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_wallet_stealth_address_construct_from_decoded(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"decoded", NULL};
    char const* decoded_buf = NULL;
    Py_ssize_t decoded_size = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "y#", kwlist, &decoded_buf, &decoded_size)) {
        return NULL;
    }
    auto const result = kth_wallet_stealth_address_construct_from_decoded((uint8_t const*)decoded_buf, (kth_size_t)decoded_size);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_STEALTH_ADDRESS, kth_py_native_wallet_stealth_address_capsule_dtor);
    if (capsule == NULL) {
        kth_wallet_stealth_address_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_wallet_stealth_address_construct_from_encoded(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"encoded", NULL};
    char const* encoded = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "s", kwlist, &encoded)) {
        return NULL;
    }
    auto const result = kth_wallet_stealth_address_construct_from_encoded(encoded);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_STEALTH_ADDRESS, kth_py_native_wallet_stealth_address_capsule_dtor);
    if (capsule == NULL) {
        kth_wallet_stealth_address_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_wallet_stealth_address_construct_from_binary_scan_key_spend_keys_signatures_version(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"filter", (char*)"scan_key", (char*)"spend_keys", (char*)"signatures", (char*)"version", NULL};
    PyObject* py_filter = NULL;
    char const* scan_key_buf = NULL;
    Py_ssize_t scan_key_size = 0;
    PyObject* py_spend_keys = NULL;
    unsigned char signatures = 0;
    unsigned char version = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Oy#OBB", kwlist, &py_filter, &scan_key_buf, &scan_key_size, &py_spend_keys, &signatures, &version)) {
        return NULL;
    }
    kth_binary_const_t filter_handle = (kth_binary_const_t)PyCapsule_GetPointer(py_filter, KTH_PY_CAPSULE_CORE_BINARY);
    if (filter_handle == NULL) return NULL;
    if (scan_key_size != (Py_ssize_t)KTH_EC_COMPRESSED_SIZE) {
        PyErr_Format(PyExc_ValueError, "expected %d-byte scan_key, got %zd", (int)KTH_EC_COMPRESSED_SIZE, scan_key_size);
        return NULL;
    }
    kth_ec_compressed_t scan_key;
    memcpy(scan_key.data, scan_key_buf, (size_t)KTH_EC_COMPRESSED_SIZE);
    kth_ec_compressed_list_const_t spend_keys_handle = (kth_ec_compressed_list_const_t)PyCapsule_GetPointer(py_spend_keys, KTH_PY_CAPSULE_WALLET_EC_COMPRESSED_LIST);
    if (spend_keys_handle == NULL) return NULL;
    auto const result = kth_wallet_stealth_address_construct_from_binary_scan_key_spend_keys_signatures_version(filter_handle, &scan_key, spend_keys_handle, (uint8_t)signatures, (uint8_t)version);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_STEALTH_ADDRESS, kth_py_native_wallet_stealth_address_capsule_dtor);
    if (capsule == NULL) {
        kth_wallet_stealth_address_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_wallet_stealth_address_copy(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_stealth_address_const_t self_handle = (kth_stealth_address_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_STEALTH_ADDRESS);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_stealth_address_copy(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_STEALTH_ADDRESS, kth_py_native_wallet_stealth_address_capsule_dtor);
    if (capsule == NULL) {
        kth_wallet_stealth_address_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_wallet_stealth_address_destruct(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_stealth_address_mut_t self_handle = (kth_stealth_address_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_STEALTH_ADDRESS);
    if (self_handle == NULL) return NULL;
    kth_wallet_stealth_address_destruct(self_handle);
    PyCapsule_SetName(py_self, "kth.destroyed");
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_wallet_stealth_address_equals(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"other", NULL};
    PyObject* py_self = NULL;
    PyObject* py_other = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_other)) {
        return NULL;
    }
    kth_stealth_address_const_t self_handle = (kth_stealth_address_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_STEALTH_ADDRESS);
    if (self_handle == NULL) return NULL;
    kth_stealth_address_const_t other_handle = (kth_stealth_address_const_t)PyCapsule_GetPointer(py_other, KTH_PY_CAPSULE_WALLET_STEALTH_ADDRESS);
    if (other_handle == NULL) return NULL;
    auto const result = kth_wallet_stealth_address_equals(self_handle, other_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_wallet_stealth_address_less(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"x", NULL};
    PyObject* py_self = NULL;
    PyObject* py_x = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_x)) {
        return NULL;
    }
    kth_stealth_address_const_t self_handle = (kth_stealth_address_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_STEALTH_ADDRESS);
    if (self_handle == NULL) return NULL;
    kth_stealth_address_const_t x_handle = (kth_stealth_address_const_t)PyCapsule_GetPointer(py_x, KTH_PY_CAPSULE_WALLET_STEALTH_ADDRESS);
    if (x_handle == NULL) return NULL;
    auto const result = kth_wallet_stealth_address_less(self_handle, x_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_wallet_stealth_address_valid(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_stealth_address_const_t self_handle = (kth_stealth_address_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_STEALTH_ADDRESS);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_stealth_address_valid(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_wallet_stealth_address_encoded(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_stealth_address_const_t self_handle = (kth_stealth_address_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_STEALTH_ADDRESS);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_stealth_address_encoded(self_handle);
    if (result == NULL) Py_RETURN_NONE;
    PyObject* py_result = Py_BuildValue("s", result);
    kth_core_destruct_string(result);
    return py_result;
}

PyObject*
kth_py_native_wallet_stealth_address_version(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_stealth_address_const_t self_handle = (kth_stealth_address_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_STEALTH_ADDRESS);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_stealth_address_version(self_handle);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyObject*
kth_py_native_wallet_stealth_address_scan_key(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_stealth_address_const_t self_handle = (kth_stealth_address_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_STEALTH_ADDRESS);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_stealth_address_scan_key(self_handle);
    return Py_BuildValue("y#", result.data, (Py_ssize_t)KTH_EC_COMPRESSED_SIZE);
}

PyObject*
kth_py_native_wallet_stealth_address_spend_keys(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_stealth_address_const_t self_handle = (kth_stealth_address_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_STEALTH_ADDRESS);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_stealth_address_spend_keys(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL list returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_EC_COMPRESSED_LIST, kth_py_native_borrowed_parent_dtor);
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
kth_py_native_wallet_stealth_address_signatures(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_stealth_address_const_t self_handle = (kth_stealth_address_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_STEALTH_ADDRESS);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_stealth_address_signatures(self_handle);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyObject*
kth_py_native_wallet_stealth_address_filter(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_stealth_address_const_t self_handle = (kth_stealth_address_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_STEALTH_ADDRESS);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_stealth_address_filter(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CORE_BINARY, kth_py_native_borrowed_parent_dtor);
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
kth_py_native_wallet_stealth_address_to_chunk(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_stealth_address_const_t self_handle = (kth_stealth_address_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_STEALTH_ADDRESS);
    if (self_handle == NULL) return NULL;
    kth_size_t out_size = 0;
    auto const result = kth_wallet_stealth_address_to_chunk(self_handle, &out_size);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: serialization failed");
        return NULL;
    }
    PyObject* py_result = Py_BuildValue("y#", result, (Py_ssize_t)out_size);
    kth_core_destruct_array(result);
    return py_result;
}

PyMethodDef kth_py_native_wallet_stealth_address_methods[] = {
    {"wallet_stealth_address_construct_default", (PyCFunction)kth_py_native_wallet_stealth_address_construct_default, METH_NOARGS, NULL},
    {"wallet_stealth_address_construct_from_decoded", (PyCFunction)kth_py_native_wallet_stealth_address_construct_from_decoded, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_stealth_address_construct_from_encoded", (PyCFunction)kth_py_native_wallet_stealth_address_construct_from_encoded, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_stealth_address_construct_from_binary_scan_key_spend_keys_signatures_version", (PyCFunction)kth_py_native_wallet_stealth_address_construct_from_binary_scan_key_spend_keys_signatures_version, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_stealth_address_copy", (PyCFunction)kth_py_native_wallet_stealth_address_copy, METH_O, NULL},
    {"wallet_stealth_address_destruct", (PyCFunction)kth_py_native_wallet_stealth_address_destruct, METH_O, NULL},
    {"wallet_stealth_address_equals", (PyCFunction)kth_py_native_wallet_stealth_address_equals, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_stealth_address_less", (PyCFunction)kth_py_native_wallet_stealth_address_less, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_stealth_address_valid", (PyCFunction)kth_py_native_wallet_stealth_address_valid, METH_O, NULL},
    {"wallet_stealth_address_encoded", (PyCFunction)kth_py_native_wallet_stealth_address_encoded, METH_O, NULL},
    {"wallet_stealth_address_version", (PyCFunction)kth_py_native_wallet_stealth_address_version, METH_O, NULL},
    {"wallet_stealth_address_scan_key", (PyCFunction)kth_py_native_wallet_stealth_address_scan_key, METH_O, NULL},
    {"wallet_stealth_address_spend_keys", (PyCFunction)kth_py_native_wallet_stealth_address_spend_keys, METH_O, NULL},
    {"wallet_stealth_address_signatures", (PyCFunction)kth_py_native_wallet_stealth_address_signatures, METH_O, NULL},
    {"wallet_stealth_address_filter", (PyCFunction)kth_py_native_wallet_stealth_address_filter, METH_O, NULL},
    {"wallet_stealth_address_to_chunk", (PyCFunction)kth_py_native_wallet_stealth_address_to_chunk, METH_O, NULL},
    {NULL, NULL, 0, NULL}  // sentinel
};

#ifdef __cplusplus
} // extern "C"
#endif
