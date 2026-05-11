// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/py-native/wallet/ek_private.h>

#include <string.h>
#include <kth/capi.h>
#include <kth/capi/wallet/ek_private.h>
#include <kth/py-native/capsule_names.h>
#include <kth/py-native/utils.h>

#ifdef __cplusplus
extern "C" {
#endif

// PyCapsule destructor — released by GC when the capsule is
// collected. Explicit `destruct` calls set the capsule name to
// "kth.destroyed", so PyCapsule_IsValid returns false and this
// destructor becomes a no-op (no double-free).
void kth_py_native_wallet_ek_private_capsule_dtor(PyObject* capsule) {
    if ( ! PyCapsule_IsValid(capsule, KTH_PY_CAPSULE_WALLET_EK_PRIVATE)) return;
    kth_ek_private_mut_t handle = (kth_ek_private_mut_t)PyCapsule_GetPointer(capsule, KTH_PY_CAPSULE_WALLET_EK_PRIVATE);
    if (handle != NULL) kth_wallet_ek_private_destruct(handle);
}

PyObject*
kth_py_native_wallet_ek_private_construct_default(PyObject* self, PyObject* Py_UNUSED(args)) {
    auto const result = kth_wallet_ek_private_construct_default();
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_EK_PRIVATE, kth_py_native_wallet_ek_private_capsule_dtor);
    if (capsule == NULL) {
        kth_wallet_ek_private_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_wallet_ek_private_construct_from_encoded(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"encoded", NULL};
    char const* encoded = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "s", kwlist, &encoded)) {
        return NULL;
    }
    auto const result = kth_wallet_ek_private_construct_from_encoded(encoded);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_EK_PRIVATE, kth_py_native_wallet_ek_private_capsule_dtor);
    if (capsule == NULL) {
        kth_wallet_ek_private_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_wallet_ek_private_construct_from_value(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"value", NULL};
    char const* value_buf = NULL;
    Py_ssize_t value_size = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "y#", kwlist, &value_buf, &value_size)) {
        return NULL;
    }
    if (value_size != (Py_ssize_t)43) {
        PyErr_Format(PyExc_ValueError, "expected %d-byte value, got %zd", (int)43, value_size);
        return NULL;
    }
    kth_encrypted_private_t value;
    memcpy(value.data, value_buf, (size_t)43);
    auto const result = kth_wallet_ek_private_construct_from_value(&value);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_EK_PRIVATE, kth_py_native_wallet_ek_private_capsule_dtor);
    if (capsule == NULL) {
        kth_wallet_ek_private_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_wallet_ek_private_copy(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_ek_private_const_t self_handle = (kth_ek_private_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_EK_PRIVATE);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_ek_private_copy(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_EK_PRIVATE, kth_py_native_wallet_ek_private_capsule_dtor);
    if (capsule == NULL) {
        kth_wallet_ek_private_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_wallet_ek_private_destruct(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_ek_private_mut_t self_handle = (kth_ek_private_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_EK_PRIVATE);
    if (self_handle == NULL) return NULL;
    kth_wallet_ek_private_destruct(self_handle);
    PyCapsule_SetName(py_self, "kth.destroyed");
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_wallet_ek_private_equals(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"other", NULL};
    PyObject* py_self = NULL;
    PyObject* py_other = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_other)) {
        return NULL;
    }
    kth_ek_private_const_t self_handle = (kth_ek_private_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_EK_PRIVATE);
    if (self_handle == NULL) return NULL;
    kth_ek_private_const_t other_handle = (kth_ek_private_const_t)PyCapsule_GetPointer(py_other, KTH_PY_CAPSULE_WALLET_EK_PRIVATE);
    if (other_handle == NULL) return NULL;
    auto const result = kth_wallet_ek_private_equals(self_handle, other_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_wallet_ek_private_less(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"x", NULL};
    PyObject* py_self = NULL;
    PyObject* py_x = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_x)) {
        return NULL;
    }
    kth_ek_private_const_t self_handle = (kth_ek_private_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_EK_PRIVATE);
    if (self_handle == NULL) return NULL;
    kth_ek_private_const_t x_handle = (kth_ek_private_const_t)PyCapsule_GetPointer(py_x, KTH_PY_CAPSULE_WALLET_EK_PRIVATE);
    if (x_handle == NULL) return NULL;
    auto const result = kth_wallet_ek_private_less(self_handle, x_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_wallet_ek_private_valid(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_ek_private_const_t self_handle = (kth_ek_private_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_EK_PRIVATE);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_ek_private_valid(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_wallet_ek_private_encoded(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_ek_private_const_t self_handle = (kth_ek_private_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_EK_PRIVATE);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_ek_private_encoded(self_handle);
    if (result == NULL) Py_RETURN_NONE;
    PyObject* py_result = Py_BuildValue("s", result);
    kth_core_destruct_string(result);
    return py_result;
}

PyObject*
kth_py_native_wallet_ek_private_private_key(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_ek_private_const_t self_handle = (kth_ek_private_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_EK_PRIVATE);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_ek_private_private_key(self_handle);
    return Py_BuildValue("y#", result.data, (Py_ssize_t)43);
}

PyMethodDef kth_py_native_wallet_ek_private_methods[] = {
    {"wallet_ek_private_construct_default", (PyCFunction)kth_py_native_wallet_ek_private_construct_default, METH_NOARGS, NULL},
    {"wallet_ek_private_construct_from_encoded", (PyCFunction)kth_py_native_wallet_ek_private_construct_from_encoded, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_ek_private_construct_from_value", (PyCFunction)kth_py_native_wallet_ek_private_construct_from_value, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_ek_private_copy", (PyCFunction)kth_py_native_wallet_ek_private_copy, METH_O, NULL},
    {"wallet_ek_private_destruct", (PyCFunction)kth_py_native_wallet_ek_private_destruct, METH_O, NULL},
    {"wallet_ek_private_equals", (PyCFunction)kth_py_native_wallet_ek_private_equals, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_ek_private_less", (PyCFunction)kth_py_native_wallet_ek_private_less, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_ek_private_valid", (PyCFunction)kth_py_native_wallet_ek_private_valid, METH_O, NULL},
    {"wallet_ek_private_encoded", (PyCFunction)kth_py_native_wallet_ek_private_encoded, METH_O, NULL},
    {"wallet_ek_private_private_key", (PyCFunction)kth_py_native_wallet_ek_private_private_key, METH_O, NULL},
    {NULL, NULL, 0, NULL}  // sentinel
};

#ifdef __cplusplus
} // extern "C"
#endif
