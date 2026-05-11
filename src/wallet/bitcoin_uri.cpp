// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/py-native/wallet/bitcoin_uri.h>

#include <string.h>
#include <kth/capi.h>
#include <kth/capi/wallet/bitcoin_uri.h>
#include <kth/py-native/capsule_names.h>
#include <kth/py-native/utils.h>

#ifdef __cplusplus
extern "C" {
#endif

// PyCapsule destructor — released by GC when the capsule is
// collected. Explicit `destruct` calls set the capsule name to
// "kth.destroyed", so PyCapsule_IsValid returns false and this
// destructor becomes a no-op (no double-free).
void kth_py_native_wallet_bitcoin_uri_capsule_dtor(PyObject* capsule) {
    if ( ! PyCapsule_IsValid(capsule, KTH_PY_CAPSULE_WALLET_BITCOIN_URI)) return;
    kth_bitcoin_uri_mut_t handle = (kth_bitcoin_uri_mut_t)PyCapsule_GetPointer(capsule, KTH_PY_CAPSULE_WALLET_BITCOIN_URI);
    if (handle != NULL) kth_wallet_bitcoin_uri_destruct(handle);
}

PyObject*
kth_py_native_wallet_bitcoin_uri_construct_default(PyObject* self, PyObject* Py_UNUSED(args)) {
    auto const result = kth_wallet_bitcoin_uri_construct_default();
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_BITCOIN_URI, kth_py_native_wallet_bitcoin_uri_capsule_dtor);
    if (capsule == NULL) {
        kth_wallet_bitcoin_uri_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_wallet_bitcoin_uri_construct(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"uri", (char*)"strict", NULL};
    char const* uri = NULL;
    int strict = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "sp", kwlist, &uri, &strict)) {
        return NULL;
    }
    auto const result = kth_wallet_bitcoin_uri_construct(uri, (kth_bool_t)strict);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_BITCOIN_URI, kth_py_native_wallet_bitcoin_uri_capsule_dtor);
    if (capsule == NULL) {
        kth_wallet_bitcoin_uri_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_wallet_bitcoin_uri_copy(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_bitcoin_uri_const_t self_handle = (kth_bitcoin_uri_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_BITCOIN_URI);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_bitcoin_uri_copy(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_BITCOIN_URI, kth_py_native_wallet_bitcoin_uri_capsule_dtor);
    if (capsule == NULL) {
        kth_wallet_bitcoin_uri_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_wallet_bitcoin_uri_destruct(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_bitcoin_uri_mut_t self_handle = (kth_bitcoin_uri_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_BITCOIN_URI);
    if (self_handle == NULL) return NULL;
    kth_wallet_bitcoin_uri_destruct(self_handle);
    PyCapsule_SetName(py_self, "kth.destroyed");
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_wallet_bitcoin_uri_equals(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"other", NULL};
    PyObject* py_self = NULL;
    PyObject* py_other = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_other)) {
        return NULL;
    }
    kth_bitcoin_uri_const_t self_handle = (kth_bitcoin_uri_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_BITCOIN_URI);
    if (self_handle == NULL) return NULL;
    kth_bitcoin_uri_const_t other_handle = (kth_bitcoin_uri_const_t)PyCapsule_GetPointer(py_other, KTH_PY_CAPSULE_WALLET_BITCOIN_URI);
    if (other_handle == NULL) return NULL;
    auto const result = kth_wallet_bitcoin_uri_equals(self_handle, other_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_wallet_bitcoin_uri_less(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"x", NULL};
    PyObject* py_self = NULL;
    PyObject* py_x = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_x)) {
        return NULL;
    }
    kth_bitcoin_uri_const_t self_handle = (kth_bitcoin_uri_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_BITCOIN_URI);
    if (self_handle == NULL) return NULL;
    kth_bitcoin_uri_const_t x_handle = (kth_bitcoin_uri_const_t)PyCapsule_GetPointer(py_x, KTH_PY_CAPSULE_WALLET_BITCOIN_URI);
    if (x_handle == NULL) return NULL;
    auto const result = kth_wallet_bitcoin_uri_less(self_handle, x_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_wallet_bitcoin_uri_valid(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_bitcoin_uri_const_t self_handle = (kth_bitcoin_uri_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_BITCOIN_URI);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_bitcoin_uri_valid(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_wallet_bitcoin_uri_encoded(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_bitcoin_uri_const_t self_handle = (kth_bitcoin_uri_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_BITCOIN_URI);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_bitcoin_uri_encoded(self_handle);
    if (result == NULL) Py_RETURN_NONE;
    PyObject* py_result = Py_BuildValue("s", result);
    kth_core_destruct_string(result);
    return py_result;
}

PyObject*
kth_py_native_wallet_bitcoin_uri_amount(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_bitcoin_uri_const_t self_handle = (kth_bitcoin_uri_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_BITCOIN_URI);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_bitcoin_uri_amount(self_handle);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyObject*
kth_py_native_wallet_bitcoin_uri_label(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_bitcoin_uri_const_t self_handle = (kth_bitcoin_uri_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_BITCOIN_URI);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_bitcoin_uri_label(self_handle);
    if (result == NULL) Py_RETURN_NONE;
    PyObject* py_result = Py_BuildValue("s", result);
    kth_core_destruct_string(result);
    return py_result;
}

PyObject*
kth_py_native_wallet_bitcoin_uri_message(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_bitcoin_uri_const_t self_handle = (kth_bitcoin_uri_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_BITCOIN_URI);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_bitcoin_uri_message(self_handle);
    if (result == NULL) Py_RETURN_NONE;
    PyObject* py_result = Py_BuildValue("s", result);
    kth_core_destruct_string(result);
    return py_result;
}

PyObject*
kth_py_native_wallet_bitcoin_uri_r(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_bitcoin_uri_const_t self_handle = (kth_bitcoin_uri_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_BITCOIN_URI);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_bitcoin_uri_r(self_handle);
    if (result == NULL) Py_RETURN_NONE;
    PyObject* py_result = Py_BuildValue("s", result);
    kth_core_destruct_string(result);
    return py_result;
}

PyObject*
kth_py_native_wallet_bitcoin_uri_address(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_bitcoin_uri_const_t self_handle = (kth_bitcoin_uri_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_BITCOIN_URI);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_bitcoin_uri_address(self_handle);
    if (result == NULL) Py_RETURN_NONE;
    PyObject* py_result = Py_BuildValue("s", result);
    kth_core_destruct_string(result);
    return py_result;
}

PyObject*
kth_py_native_wallet_bitcoin_uri_payment(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_bitcoin_uri_const_t self_handle = (kth_bitcoin_uri_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_BITCOIN_URI);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_bitcoin_uri_payment(self_handle);
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
kth_py_native_wallet_bitcoin_uri_stealth(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_bitcoin_uri_const_t self_handle = (kth_bitcoin_uri_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_BITCOIN_URI);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_bitcoin_uri_stealth(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
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
kth_py_native_wallet_bitcoin_uri_parameter(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"key", NULL};
    PyObject* py_self = NULL;
    char const* key = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Os", kwlist, &py_self, &key)) {
        return NULL;
    }
    kth_bitcoin_uri_const_t self_handle = (kth_bitcoin_uri_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_BITCOIN_URI);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_bitcoin_uri_parameter(self_handle, key);
    if (result == NULL) Py_RETURN_NONE;
    PyObject* py_result = Py_BuildValue("s", result);
    kth_core_destruct_string(result);
    return py_result;
}

PyObject*
kth_py_native_wallet_bitcoin_uri_set_amount(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"satoshis", NULL};
    PyObject* py_self = NULL;
    unsigned long long satoshis = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OK", kwlist, &py_self, &satoshis)) {
        return NULL;
    }
    kth_bitcoin_uri_mut_t self_handle = (kth_bitcoin_uri_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_BITCOIN_URI);
    if (self_handle == NULL) return NULL;
    kth_wallet_bitcoin_uri_set_amount(self_handle, (uint64_t)satoshis);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_wallet_bitcoin_uri_set_label(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"label", NULL};
    PyObject* py_self = NULL;
    char const* label = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Os", kwlist, &py_self, &label)) {
        return NULL;
    }
    kth_bitcoin_uri_mut_t self_handle = (kth_bitcoin_uri_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_BITCOIN_URI);
    if (self_handle == NULL) return NULL;
    kth_wallet_bitcoin_uri_set_label(self_handle, label);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_wallet_bitcoin_uri_set_message(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"message", NULL};
    PyObject* py_self = NULL;
    char const* message = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Os", kwlist, &py_self, &message)) {
        return NULL;
    }
    kth_bitcoin_uri_mut_t self_handle = (kth_bitcoin_uri_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_BITCOIN_URI);
    if (self_handle == NULL) return NULL;
    kth_wallet_bitcoin_uri_set_message(self_handle, message);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_wallet_bitcoin_uri_set_r(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"r", NULL};
    PyObject* py_self = NULL;
    char const* r = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Os", kwlist, &py_self, &r)) {
        return NULL;
    }
    kth_bitcoin_uri_mut_t self_handle = (kth_bitcoin_uri_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_BITCOIN_URI);
    if (self_handle == NULL) return NULL;
    kth_wallet_bitcoin_uri_set_r(self_handle, r);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_wallet_bitcoin_uri_set_address_string(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"address", NULL};
    PyObject* py_self = NULL;
    char const* address = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Os", kwlist, &py_self, &address)) {
        return NULL;
    }
    kth_bitcoin_uri_mut_t self_handle = (kth_bitcoin_uri_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_BITCOIN_URI);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_bitcoin_uri_set_address_string(self_handle, address);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_wallet_bitcoin_uri_set_address_payment_address(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"payment", NULL};
    PyObject* py_self = NULL;
    PyObject* py_payment = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_payment)) {
        return NULL;
    }
    kth_bitcoin_uri_mut_t self_handle = (kth_bitcoin_uri_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_BITCOIN_URI);
    if (self_handle == NULL) return NULL;
    kth_payment_address_const_t payment_handle = (kth_payment_address_const_t)PyCapsule_GetPointer(py_payment, KTH_PY_CAPSULE_WALLET_PAYMENT_ADDRESS);
    if (payment_handle == NULL) return NULL;
    kth_wallet_bitcoin_uri_set_address_payment_address(self_handle, payment_handle);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_wallet_bitcoin_uri_set_address_stealth_address(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"stealth", NULL};
    PyObject* py_self = NULL;
    PyObject* py_stealth = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_stealth)) {
        return NULL;
    }
    kth_bitcoin_uri_mut_t self_handle = (kth_bitcoin_uri_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_BITCOIN_URI);
    if (self_handle == NULL) return NULL;
    kth_stealth_address_const_t stealth_handle = (kth_stealth_address_const_t)PyCapsule_GetPointer(py_stealth, KTH_PY_CAPSULE_WALLET_STEALTH_ADDRESS);
    if (stealth_handle == NULL) return NULL;
    kth_wallet_bitcoin_uri_set_address_stealth_address(self_handle, stealth_handle);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_wallet_bitcoin_uri_set_strict(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"strict", NULL};
    PyObject* py_self = NULL;
    int strict = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Op", kwlist, &py_self, &strict)) {
        return NULL;
    }
    kth_bitcoin_uri_mut_t self_handle = (kth_bitcoin_uri_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_BITCOIN_URI);
    if (self_handle == NULL) return NULL;
    kth_wallet_bitcoin_uri_set_strict(self_handle, (kth_bool_t)strict);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_wallet_bitcoin_uri_set_scheme(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"scheme", NULL};
    PyObject* py_self = NULL;
    char const* scheme = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Os", kwlist, &py_self, &scheme)) {
        return NULL;
    }
    kth_bitcoin_uri_mut_t self_handle = (kth_bitcoin_uri_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_BITCOIN_URI);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_bitcoin_uri_set_scheme(self_handle, scheme);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_wallet_bitcoin_uri_set_authority(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"authority", NULL};
    PyObject* py_self = NULL;
    char const* authority = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Os", kwlist, &py_self, &authority)) {
        return NULL;
    }
    kth_bitcoin_uri_mut_t self_handle = (kth_bitcoin_uri_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_BITCOIN_URI);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_bitcoin_uri_set_authority(self_handle, authority);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_wallet_bitcoin_uri_set_path(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"path", NULL};
    PyObject* py_self = NULL;
    char const* path = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Os", kwlist, &py_self, &path)) {
        return NULL;
    }
    kth_bitcoin_uri_mut_t self_handle = (kth_bitcoin_uri_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_BITCOIN_URI);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_bitcoin_uri_set_path(self_handle, path);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_wallet_bitcoin_uri_set_fragment(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"fragment", NULL};
    PyObject* py_self = NULL;
    char const* fragment = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Os", kwlist, &py_self, &fragment)) {
        return NULL;
    }
    kth_bitcoin_uri_mut_t self_handle = (kth_bitcoin_uri_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_BITCOIN_URI);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_bitcoin_uri_set_fragment(self_handle, fragment);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_wallet_bitcoin_uri_set_parameter(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"key", (char*)"value", NULL};
    PyObject* py_self = NULL;
    char const* key = NULL;
    char const* value = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Oss", kwlist, &py_self, &key, &value)) {
        return NULL;
    }
    kth_bitcoin_uri_mut_t self_handle = (kth_bitcoin_uri_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_BITCOIN_URI);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_bitcoin_uri_set_parameter(self_handle, key, value);
    return PyBool_FromLong((long)result);
}

PyMethodDef kth_py_native_wallet_bitcoin_uri_methods[] = {
    {"wallet_bitcoin_uri_construct_default", (PyCFunction)kth_py_native_wallet_bitcoin_uri_construct_default, METH_NOARGS, NULL},
    {"wallet_bitcoin_uri_construct", (PyCFunction)kth_py_native_wallet_bitcoin_uri_construct, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_bitcoin_uri_copy", (PyCFunction)kth_py_native_wallet_bitcoin_uri_copy, METH_O, NULL},
    {"wallet_bitcoin_uri_destruct", (PyCFunction)kth_py_native_wallet_bitcoin_uri_destruct, METH_O, NULL},
    {"wallet_bitcoin_uri_equals", (PyCFunction)kth_py_native_wallet_bitcoin_uri_equals, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_bitcoin_uri_less", (PyCFunction)kth_py_native_wallet_bitcoin_uri_less, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_bitcoin_uri_valid", (PyCFunction)kth_py_native_wallet_bitcoin_uri_valid, METH_O, NULL},
    {"wallet_bitcoin_uri_encoded", (PyCFunction)kth_py_native_wallet_bitcoin_uri_encoded, METH_O, NULL},
    {"wallet_bitcoin_uri_amount", (PyCFunction)kth_py_native_wallet_bitcoin_uri_amount, METH_O, NULL},
    {"wallet_bitcoin_uri_label", (PyCFunction)kth_py_native_wallet_bitcoin_uri_label, METH_O, NULL},
    {"wallet_bitcoin_uri_message", (PyCFunction)kth_py_native_wallet_bitcoin_uri_message, METH_O, NULL},
    {"wallet_bitcoin_uri_r", (PyCFunction)kth_py_native_wallet_bitcoin_uri_r, METH_O, NULL},
    {"wallet_bitcoin_uri_address", (PyCFunction)kth_py_native_wallet_bitcoin_uri_address, METH_O, NULL},
    {"wallet_bitcoin_uri_payment", (PyCFunction)kth_py_native_wallet_bitcoin_uri_payment, METH_O, NULL},
    {"wallet_bitcoin_uri_stealth", (PyCFunction)kth_py_native_wallet_bitcoin_uri_stealth, METH_O, NULL},
    {"wallet_bitcoin_uri_parameter", (PyCFunction)kth_py_native_wallet_bitcoin_uri_parameter, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_bitcoin_uri_set_amount", (PyCFunction)kth_py_native_wallet_bitcoin_uri_set_amount, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_bitcoin_uri_set_label", (PyCFunction)kth_py_native_wallet_bitcoin_uri_set_label, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_bitcoin_uri_set_message", (PyCFunction)kth_py_native_wallet_bitcoin_uri_set_message, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_bitcoin_uri_set_r", (PyCFunction)kth_py_native_wallet_bitcoin_uri_set_r, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_bitcoin_uri_set_address_string", (PyCFunction)kth_py_native_wallet_bitcoin_uri_set_address_string, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_bitcoin_uri_set_address_payment_address", (PyCFunction)kth_py_native_wallet_bitcoin_uri_set_address_payment_address, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_bitcoin_uri_set_address_stealth_address", (PyCFunction)kth_py_native_wallet_bitcoin_uri_set_address_stealth_address, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_bitcoin_uri_set_strict", (PyCFunction)kth_py_native_wallet_bitcoin_uri_set_strict, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_bitcoin_uri_set_scheme", (PyCFunction)kth_py_native_wallet_bitcoin_uri_set_scheme, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_bitcoin_uri_set_authority", (PyCFunction)kth_py_native_wallet_bitcoin_uri_set_authority, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_bitcoin_uri_set_path", (PyCFunction)kth_py_native_wallet_bitcoin_uri_set_path, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_bitcoin_uri_set_fragment", (PyCFunction)kth_py_native_wallet_bitcoin_uri_set_fragment, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_bitcoin_uri_set_parameter", (PyCFunction)kth_py_native_wallet_bitcoin_uri_set_parameter, METH_VARARGS | METH_KEYWORDS, NULL},
    {NULL, NULL, 0, NULL}  // sentinel
};

#ifdef __cplusplus
} // extern "C"
#endif
