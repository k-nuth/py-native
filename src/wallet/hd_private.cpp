// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/py-native/wallet/hd_private.h>

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
void kth_py_native_wallet_hd_private_capsule_dtor(PyObject* capsule) {
    if ( ! PyCapsule_IsValid(capsule, KTH_PY_CAPSULE_WALLET_HD_PRIVATE)) return;
    kth_hd_private_mut_t handle = (kth_hd_private_mut_t)PyCapsule_GetPointer(capsule, KTH_PY_CAPSULE_WALLET_HD_PRIVATE);
    if (handle != NULL) kth_wallet_hd_private_destruct(handle);
}

PyObject*
kth_py_native_wallet_hd_private_construct_default(PyObject* self, PyObject* Py_UNUSED(args)) {
    auto const result = kth_wallet_hd_private_construct_default();
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_HD_PRIVATE, kth_py_native_wallet_hd_private_capsule_dtor);
    if (capsule == NULL) {
        kth_wallet_hd_private_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_wallet_hd_private_construct_from_seed_prefixes(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"seed", (char*)"prefixes", NULL};
    char const* seed_buf = NULL;
    Py_ssize_t seed_size = 0;
    unsigned long long prefixes = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "y#K", kwlist, &seed_buf, &seed_size, &prefixes)) {
        return NULL;
    }
    auto const result = kth_wallet_hd_private_construct_from_seed_prefixes((uint8_t const*)seed_buf, (kth_size_t)seed_size, (uint64_t)prefixes);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_HD_PRIVATE, kth_py_native_wallet_hd_private_capsule_dtor);
    if (capsule == NULL) {
        kth_wallet_hd_private_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_wallet_hd_private_construct_from_private_key(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"private_key", NULL};
    char const* private_key_buf = NULL;
    Py_ssize_t private_key_size = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "y#", kwlist, &private_key_buf, &private_key_size)) {
        return NULL;
    }
    if (private_key_size != (Py_ssize_t)KTH_HD_KEY_SIZE) {
        PyErr_Format(PyExc_ValueError, "expected %d-byte private_key, got %zd", (int)KTH_HD_KEY_SIZE, private_key_size);
        return NULL;
    }
    kth_hd_key_t private_key;
    memcpy(private_key.data, private_key_buf, (size_t)KTH_HD_KEY_SIZE);
    auto const result = kth_wallet_hd_private_construct_from_private_key(private_key);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_HD_PRIVATE, kth_py_native_wallet_hd_private_capsule_dtor);
    if (capsule == NULL) {
        kth_wallet_hd_private_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_wallet_hd_private_construct_from_private_key_prefixes(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"private_key", (char*)"prefixes", NULL};
    char const* private_key_buf = NULL;
    Py_ssize_t private_key_size = 0;
    unsigned long long prefixes = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "y#K", kwlist, &private_key_buf, &private_key_size, &prefixes)) {
        return NULL;
    }
    if (private_key_size != (Py_ssize_t)KTH_HD_KEY_SIZE) {
        PyErr_Format(PyExc_ValueError, "expected %d-byte private_key, got %zd", (int)KTH_HD_KEY_SIZE, private_key_size);
        return NULL;
    }
    kth_hd_key_t private_key;
    memcpy(private_key.data, private_key_buf, (size_t)KTH_HD_KEY_SIZE);
    auto const result = kth_wallet_hd_private_construct_from_private_key_prefixes(private_key, (uint64_t)prefixes);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_HD_PRIVATE, kth_py_native_wallet_hd_private_capsule_dtor);
    if (capsule == NULL) {
        kth_wallet_hd_private_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_wallet_hd_private_construct_from_private_key_prefix(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"private_key", (char*)"prefix", NULL};
    char const* private_key_buf = NULL;
    Py_ssize_t private_key_size = 0;
    unsigned int prefix = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "y#I", kwlist, &private_key_buf, &private_key_size, &prefix)) {
        return NULL;
    }
    if (private_key_size != (Py_ssize_t)KTH_HD_KEY_SIZE) {
        PyErr_Format(PyExc_ValueError, "expected %d-byte private_key, got %zd", (int)KTH_HD_KEY_SIZE, private_key_size);
        return NULL;
    }
    kth_hd_key_t private_key;
    memcpy(private_key.data, private_key_buf, (size_t)KTH_HD_KEY_SIZE);
    auto const result = kth_wallet_hd_private_construct_from_private_key_prefix(private_key, (uint32_t)prefix);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_HD_PRIVATE, kth_py_native_wallet_hd_private_capsule_dtor);
    if (capsule == NULL) {
        kth_wallet_hd_private_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_wallet_hd_private_construct_from_encoded(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"encoded", NULL};
    char const* encoded = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "s", kwlist, &encoded)) {
        return NULL;
    }
    auto const result = kth_wallet_hd_private_construct_from_encoded(encoded);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_HD_PRIVATE, kth_py_native_wallet_hd_private_capsule_dtor);
    if (capsule == NULL) {
        kth_wallet_hd_private_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_wallet_hd_private_construct_from_encoded_prefixes(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"encoded", (char*)"prefixes", NULL};
    char const* encoded = NULL;
    unsigned long long prefixes = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "sK", kwlist, &encoded, &prefixes)) {
        return NULL;
    }
    auto const result = kth_wallet_hd_private_construct_from_encoded_prefixes(encoded, (uint64_t)prefixes);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_HD_PRIVATE, kth_py_native_wallet_hd_private_capsule_dtor);
    if (capsule == NULL) {
        kth_wallet_hd_private_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_wallet_hd_private_construct_from_encoded_prefix(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"encoded", (char*)"prefix", NULL};
    char const* encoded = NULL;
    unsigned int prefix = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "sI", kwlist, &encoded, &prefix)) {
        return NULL;
    }
    auto const result = kth_wallet_hd_private_construct_from_encoded_prefix(encoded, (uint32_t)prefix);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_HD_PRIVATE, kth_py_native_wallet_hd_private_capsule_dtor);
    if (capsule == NULL) {
        kth_wallet_hd_private_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_wallet_hd_private_copy(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_hd_private_const_t self_handle = (kth_hd_private_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_HD_PRIVATE);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_hd_private_copy(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_HD_PRIVATE, kth_py_native_wallet_hd_private_capsule_dtor);
    if (capsule == NULL) {
        kth_wallet_hd_private_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_wallet_hd_private_destruct(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_hd_private_mut_t self_handle = (kth_hd_private_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_HD_PRIVATE);
    if (self_handle == NULL) return NULL;
    kth_wallet_hd_private_destruct(self_handle);
    PyCapsule_SetName(py_self, "kth.destroyed");
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_wallet_hd_private_to_prefix(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"prefixes", NULL};
    unsigned long long prefixes = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "K", kwlist, &prefixes)) {
        return NULL;
    }
    auto const result = kth_wallet_hd_private_to_prefix((uint64_t)prefixes);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyObject*
kth_py_native_wallet_hd_private_less(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"x", NULL};
    PyObject* py_self = NULL;
    PyObject* py_x = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_x)) {
        return NULL;
    }
    kth_hd_private_const_t self_handle = (kth_hd_private_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_HD_PRIVATE);
    if (self_handle == NULL) return NULL;
    kth_hd_private_const_t x_handle = (kth_hd_private_const_t)PyCapsule_GetPointer(py_x, KTH_PY_CAPSULE_WALLET_HD_PRIVATE);
    if (x_handle == NULL) return NULL;
    auto const result = kth_wallet_hd_private_less(self_handle, x_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_wallet_hd_private_equals(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"other", NULL};
    PyObject* py_self = NULL;
    PyObject* py_other = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_other)) {
        return NULL;
    }
    kth_hd_private_const_t self_handle = (kth_hd_private_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_HD_PRIVATE);
    if (self_handle == NULL) return NULL;
    kth_hd_private_const_t other_handle = (kth_hd_private_const_t)PyCapsule_GetPointer(py_other, KTH_PY_CAPSULE_WALLET_HD_PRIVATE);
    if (other_handle == NULL) return NULL;
    auto const result = kth_wallet_hd_private_equals(self_handle, other_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_wallet_hd_private_encoded(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_hd_private_const_t self_handle = (kth_hd_private_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_HD_PRIVATE);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_hd_private_encoded(self_handle);
    if (result == NULL) Py_RETURN_NONE;
    PyObject* py_result = Py_BuildValue("s", result);
    kth_core_destruct_string(result);
    return py_result;
}

PyObject*
kth_py_native_wallet_hd_private_secret(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_hd_private_const_t self_handle = (kth_hd_private_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_HD_PRIVATE);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_hd_private_secret(self_handle);
    return Py_BuildValue("y#", result.hash, (Py_ssize_t)KTH_BITCOIN_HASH_SIZE);
}

PyObject*
kth_py_native_wallet_hd_private_to_hd_key(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_hd_private_const_t self_handle = (kth_hd_private_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_HD_PRIVATE);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_hd_private_to_hd_key(self_handle);
    return Py_BuildValue("y#", result.data, (Py_ssize_t)KTH_HD_KEY_SIZE);
}

PyObject*
kth_py_native_wallet_hd_private_to_public(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_hd_private_const_t self_handle = (kth_hd_private_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_HD_PRIVATE);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_hd_private_to_public(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_HD_PUBLIC, kth_py_native_wallet_hd_public_capsule_dtor);
    if (capsule == NULL) {
        kth_wallet_hd_public_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_wallet_hd_private_derive_private(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"index", NULL};
    PyObject* py_self = NULL;
    unsigned int index = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OI", kwlist, &py_self, &index)) {
        return NULL;
    }
    kth_hd_private_const_t self_handle = (kth_hd_private_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_HD_PRIVATE);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_hd_private_derive_private(self_handle, (uint32_t)index);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_HD_PRIVATE, kth_py_native_wallet_hd_private_capsule_dtor);
    if (capsule == NULL) {
        kth_wallet_hd_private_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_wallet_hd_private_derive_public(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"index", NULL};
    PyObject* py_self = NULL;
    unsigned int index = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OI", kwlist, &py_self, &index)) {
        return NULL;
    }
    kth_hd_private_const_t self_handle = (kth_hd_private_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_HD_PRIVATE);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_hd_private_derive_public(self_handle, (uint32_t)index);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_HD_PUBLIC, kth_py_native_wallet_hd_public_capsule_dtor);
    if (capsule == NULL) {
        kth_wallet_hd_public_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_wallet_hd_private_valid(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_hd_private_const_t self_handle = (kth_hd_private_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_HD_PRIVATE);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_hd_private_valid(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_wallet_hd_private_chain_code(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_hd_private_const_t self_handle = (kth_hd_private_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_HD_PRIVATE);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_hd_private_chain_code(self_handle);
    return Py_BuildValue("y#", result.hash, (Py_ssize_t)KTH_BITCOIN_HASH_SIZE);
}

PyObject*
kth_py_native_wallet_hd_private_lineage(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_hd_private_const_t self_handle = (kth_hd_private_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_HD_PRIVATE);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_hd_private_lineage(self_handle);
    return Py_BuildValue("(KBII)", result.prefixes, result.depth, result.parent_fingerprint, result.child_number);
}

PyObject*
kth_py_native_wallet_hd_private_point(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_hd_private_const_t self_handle = (kth_hd_private_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_HD_PRIVATE);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_hd_private_point(self_handle);
    return Py_BuildValue("y#", result.data, (Py_ssize_t)KTH_EC_COMPRESSED_SIZE);
}

PyMethodDef kth_py_native_wallet_hd_private_methods[] = {
    {"wallet_hd_private_construct_default", (PyCFunction)kth_py_native_wallet_hd_private_construct_default, METH_NOARGS, NULL},
    {"wallet_hd_private_construct_from_seed_prefixes", (PyCFunction)kth_py_native_wallet_hd_private_construct_from_seed_prefixes, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_hd_private_construct_from_private_key", (PyCFunction)kth_py_native_wallet_hd_private_construct_from_private_key, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_hd_private_construct_from_private_key_prefixes", (PyCFunction)kth_py_native_wallet_hd_private_construct_from_private_key_prefixes, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_hd_private_construct_from_private_key_prefix", (PyCFunction)kth_py_native_wallet_hd_private_construct_from_private_key_prefix, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_hd_private_construct_from_encoded", (PyCFunction)kth_py_native_wallet_hd_private_construct_from_encoded, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_hd_private_construct_from_encoded_prefixes", (PyCFunction)kth_py_native_wallet_hd_private_construct_from_encoded_prefixes, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_hd_private_construct_from_encoded_prefix", (PyCFunction)kth_py_native_wallet_hd_private_construct_from_encoded_prefix, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_hd_private_copy", (PyCFunction)kth_py_native_wallet_hd_private_copy, METH_O, NULL},
    {"wallet_hd_private_destruct", (PyCFunction)kth_py_native_wallet_hd_private_destruct, METH_O, NULL},
    {"wallet_hd_private_to_prefix", (PyCFunction)kth_py_native_wallet_hd_private_to_prefix, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_hd_private_less", (PyCFunction)kth_py_native_wallet_hd_private_less, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_hd_private_equals", (PyCFunction)kth_py_native_wallet_hd_private_equals, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_hd_private_encoded", (PyCFunction)kth_py_native_wallet_hd_private_encoded, METH_O, NULL},
    {"wallet_hd_private_secret", (PyCFunction)kth_py_native_wallet_hd_private_secret, METH_O, NULL},
    {"wallet_hd_private_to_hd_key", (PyCFunction)kth_py_native_wallet_hd_private_to_hd_key, METH_O, NULL},
    {"wallet_hd_private_to_public", (PyCFunction)kth_py_native_wallet_hd_private_to_public, METH_O, NULL},
    {"wallet_hd_private_derive_private", (PyCFunction)kth_py_native_wallet_hd_private_derive_private, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_hd_private_derive_public", (PyCFunction)kth_py_native_wallet_hd_private_derive_public, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_hd_private_valid", (PyCFunction)kth_py_native_wallet_hd_private_valid, METH_O, NULL},
    {"wallet_hd_private_chain_code", (PyCFunction)kth_py_native_wallet_hd_private_chain_code, METH_O, NULL},
    {"wallet_hd_private_lineage", (PyCFunction)kth_py_native_wallet_hd_private_lineage, METH_O, NULL},
    {"wallet_hd_private_point", (PyCFunction)kth_py_native_wallet_hd_private_point, METH_O, NULL},
    {NULL, NULL, 0, NULL}  // sentinel
};

#ifdef __cplusplus
} // extern "C"
#endif
