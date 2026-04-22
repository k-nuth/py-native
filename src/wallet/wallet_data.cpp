// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/py-native/wallet/wallet_data.h>

#include <string.h>
#include <kth/capi.h>
#include <kth/capi/wallet/wallet_data.h>
#include <kth/py-native/capsule_names.h>
#include <kth/py-native/utils.h>

#ifdef __cplusplus
extern "C" {
#endif

// PyCapsule destructor — released by GC when the capsule is
// collected. Explicit `destruct` calls set the capsule name to
// "kth.destroyed", so PyCapsule_IsValid returns false and this
// destructor becomes a no-op (no double-free).
void kth_py_native_wallet_wallet_data_capsule_dtor(PyObject* capsule) {
    if ( ! PyCapsule_IsValid(capsule, KTH_PY_CAPSULE_WALLET_WALLET_DATA)) return;
    kth_wallet_data_mut_t handle = (kth_wallet_data_mut_t)PyCapsule_GetPointer(capsule, KTH_PY_CAPSULE_WALLET_WALLET_DATA);
    if (handle != NULL) kth_wallet_wallet_data_destruct(handle);
}

PyObject*
kth_py_native_wallet_wallet_data_copy(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_wallet_data_const_t self_handle = (kth_wallet_data_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_WALLET_DATA);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_wallet_data_copy(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_WALLET_DATA, kth_py_native_wallet_wallet_data_capsule_dtor);
    if (capsule == NULL) {
        kth_wallet_wallet_data_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_wallet_wallet_data_destruct(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_wallet_data_mut_t self_handle = (kth_wallet_data_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_WALLET_DATA);
    if (self_handle == NULL) return NULL;
    kth_wallet_wallet_data_destruct(self_handle);
    PyCapsule_SetName(py_self, "kth.destroyed");
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_wallet_wallet_data_mnemonics(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_wallet_data_const_t self_handle = (kth_wallet_data_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_WALLET_DATA);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_wallet_data_mnemonics(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL list returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CORE_STRING_LIST, kth_py_native_borrowed_parent_dtor);
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
kth_py_native_wallet_wallet_data_set_mnemonics(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    PyObject* py_value = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_value)) {
        return NULL;
    }
    kth_wallet_data_mut_t self_handle = (kth_wallet_data_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_WALLET_DATA);
    if (self_handle == NULL) return NULL;
    kth_string_list_const_t value_handle = (kth_string_list_const_t)PyCapsule_GetPointer(py_value, KTH_PY_CAPSULE_CORE_STRING_LIST);
    if (value_handle == NULL) return NULL;
    kth_wallet_wallet_data_set_mnemonics(self_handle, value_handle);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_wallet_wallet_data_xpub(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_wallet_data_const_t self_handle = (kth_wallet_data_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_WALLET_DATA);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_wallet_data_xpub(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_HD_PUBLIC, kth_py_native_borrowed_parent_dtor);
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
kth_py_native_wallet_wallet_data_set_xpub(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    PyObject* py_value = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_value)) {
        return NULL;
    }
    kth_wallet_data_mut_t self_handle = (kth_wallet_data_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_WALLET_DATA);
    if (self_handle == NULL) return NULL;
    kth_hd_public_const_t value_handle = (kth_hd_public_const_t)PyCapsule_GetPointer(py_value, KTH_PY_CAPSULE_WALLET_HD_PUBLIC);
    if (value_handle == NULL) return NULL;
    kth_wallet_wallet_data_set_xpub(self_handle, value_handle);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_wallet_wallet_data_encrypted_seed(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_wallet_data_const_t self_handle = (kth_wallet_data_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_WALLET_DATA);
    if (self_handle == NULL) return NULL;
    auto result = kth_wallet_wallet_data_encrypted_seed(self_handle);
    PyObject* py_result = Py_BuildValue("y#", result.hash, (Py_ssize_t)KTH_BITCOIN_ENCRYPTED_SEED_SIZE);
    kth_core_secure_zero((void*)&result, sizeof(kth_encrypted_seed_t));
    return py_result;
}

PyObject*
kth_py_native_wallet_wallet_data_set_encrypted_seed(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    char const* value_buf = NULL;
    Py_ssize_t value_size = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Oy#", kwlist, &py_self, &value_buf, &value_size)) {
        return NULL;
    }
    kth_wallet_data_mut_t self_handle = (kth_wallet_data_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_WALLET_DATA);
    if (self_handle == NULL) return NULL;
    if (value_size != (Py_ssize_t)KTH_BITCOIN_ENCRYPTED_SEED_SIZE) {
        PyErr_Format(PyExc_ValueError, "expected %d-byte value, got %zd", (int)KTH_BITCOIN_ENCRYPTED_SEED_SIZE, value_size);
        return NULL;
    }
    kth_encrypted_seed_t value;
    memcpy(value.hash, value_buf, (size_t)KTH_BITCOIN_ENCRYPTED_SEED_SIZE);
    kth_wallet_wallet_data_set_encrypted_seed(self_handle, &value);
    kth_core_secure_zero((void*)&value, sizeof(kth_encrypted_seed_t));
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_wallet_wallet_data_create(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"password", (char*)"normalized_passphrase", NULL};
    char const* password = NULL;
    char const* normalized_passphrase = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "ss", kwlist, &password, &normalized_passphrase)) {
        return NULL;
    }
    kth_wallet_data_mut_t out = NULL;
    kth_error_code_t result = kth_wallet_create(password, normalized_passphrase, &out);
    if (result != kth_ec_success) {
        PyErr_Format(PyExc_RuntimeError, "kth error code %d", (int)result);
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)out, KTH_PY_CAPSULE_WALLET_WALLET_DATA, kth_py_native_wallet_wallet_data_capsule_dtor);
    if (capsule == NULL) {
        kth_wallet_wallet_data_destruct(out);
        return NULL;
    }
    return capsule;
}

PyMethodDef kth_py_native_wallet_wallet_data_methods[] = {
    {"wallet_wallet_data_copy", (PyCFunction)kth_py_native_wallet_wallet_data_copy, METH_O, NULL},
    {"wallet_wallet_data_destruct", (PyCFunction)kth_py_native_wallet_wallet_data_destruct, METH_O, NULL},
    {"wallet_wallet_data_mnemonics", (PyCFunction)kth_py_native_wallet_wallet_data_mnemonics, METH_O, NULL},
    {"wallet_wallet_data_set_mnemonics", (PyCFunction)kth_py_native_wallet_wallet_data_set_mnemonics, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_wallet_data_xpub", (PyCFunction)kth_py_native_wallet_wallet_data_xpub, METH_O, NULL},
    {"wallet_wallet_data_set_xpub", (PyCFunction)kth_py_native_wallet_wallet_data_set_xpub, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_wallet_data_encrypted_seed", (PyCFunction)kth_py_native_wallet_wallet_data_encrypted_seed, METH_O, NULL},
    {"wallet_wallet_data_set_encrypted_seed", (PyCFunction)kth_py_native_wallet_wallet_data_set_encrypted_seed, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_wallet_data_create", (PyCFunction)kth_py_native_wallet_wallet_data_create, METH_VARARGS | METH_KEYWORDS, NULL},
    {NULL, NULL, 0, NULL}  // sentinel
};

#ifdef __cplusplus
} // extern "C"
#endif
