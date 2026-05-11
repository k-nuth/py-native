// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/py-native/chain/abla_config.h>

#include <string.h>
#include <kth/capi.h>
#include <kth/capi/chain/abla_config.h>
#include <kth/py-native/capsule_names.h>
#include <kth/py-native/utils.h>

#ifdef __cplusplus
extern "C" {
#endif

// PyCapsule destructor — released by GC when the capsule is
// collected. Explicit `destruct` calls set the capsule name to
// "kth.destroyed", so PyCapsule_IsValid returns false and this
// destructor becomes a no-op (no double-free).
void kth_py_native_chain_abla_config_capsule_dtor(PyObject* capsule) {
    if ( ! PyCapsule_IsValid(capsule, KTH_PY_CAPSULE_CHAIN_ABLA_CONFIG)) return;
    kth_abla_config_mut_t handle = (kth_abla_config_mut_t)PyCapsule_GetPointer(capsule, KTH_PY_CAPSULE_CHAIN_ABLA_CONFIG);
    if (handle != NULL) kth_chain_abla_config_destruct(handle);
}

PyObject*
kth_py_native_chain_abla_config_copy(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_abla_config_const_t self_handle = (kth_abla_config_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_ABLA_CONFIG);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_abla_config_copy(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_ABLA_CONFIG, kth_py_native_chain_abla_config_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_abla_config_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_abla_config_destruct(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_abla_config_mut_t self_handle = (kth_abla_config_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_ABLA_CONFIG);
    if (self_handle == NULL) return NULL;
    kth_chain_abla_config_destruct(self_handle);
    PyCapsule_SetName(py_self, "kth.destroyed");
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_abla_config_epsilon0(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_abla_config_const_t self_handle = (kth_abla_config_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_ABLA_CONFIG);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_abla_config_epsilon0(self_handle);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyObject*
kth_py_native_chain_abla_config_set_epsilon0(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    unsigned long long value = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OK", kwlist, &py_self, &value)) {
        return NULL;
    }
    kth_abla_config_mut_t self_handle = (kth_abla_config_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_ABLA_CONFIG);
    if (self_handle == NULL) return NULL;
    kth_chain_abla_config_set_epsilon0(self_handle, (uint64_t)value);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_abla_config_beta0(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_abla_config_const_t self_handle = (kth_abla_config_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_ABLA_CONFIG);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_abla_config_beta0(self_handle);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyObject*
kth_py_native_chain_abla_config_set_beta0(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    unsigned long long value = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OK", kwlist, &py_self, &value)) {
        return NULL;
    }
    kth_abla_config_mut_t self_handle = (kth_abla_config_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_ABLA_CONFIG);
    if (self_handle == NULL) return NULL;
    kth_chain_abla_config_set_beta0(self_handle, (uint64_t)value);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_abla_config_n0(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_abla_config_const_t self_handle = (kth_abla_config_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_ABLA_CONFIG);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_abla_config_n0(self_handle);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyObject*
kth_py_native_chain_abla_config_set_n0(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    unsigned long long value = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OK", kwlist, &py_self, &value)) {
        return NULL;
    }
    kth_abla_config_mut_t self_handle = (kth_abla_config_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_ABLA_CONFIG);
    if (self_handle == NULL) return NULL;
    kth_chain_abla_config_set_n0(self_handle, (uint64_t)value);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_abla_config_gamma_reciprocal(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_abla_config_const_t self_handle = (kth_abla_config_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_ABLA_CONFIG);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_abla_config_gamma_reciprocal(self_handle);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyObject*
kth_py_native_chain_abla_config_set_gamma_reciprocal(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    unsigned long long value = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OK", kwlist, &py_self, &value)) {
        return NULL;
    }
    kth_abla_config_mut_t self_handle = (kth_abla_config_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_ABLA_CONFIG);
    if (self_handle == NULL) return NULL;
    kth_chain_abla_config_set_gamma_reciprocal(self_handle, (uint64_t)value);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_abla_config_zeta_xB7(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_abla_config_const_t self_handle = (kth_abla_config_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_ABLA_CONFIG);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_abla_config_zeta_xB7(self_handle);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyObject*
kth_py_native_chain_abla_config_set_zeta_xB7(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    unsigned long long value = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OK", kwlist, &py_self, &value)) {
        return NULL;
    }
    kth_abla_config_mut_t self_handle = (kth_abla_config_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_ABLA_CONFIG);
    if (self_handle == NULL) return NULL;
    kth_chain_abla_config_set_zeta_xB7(self_handle, (uint64_t)value);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_abla_config_theta_reciprocal(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_abla_config_const_t self_handle = (kth_abla_config_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_ABLA_CONFIG);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_abla_config_theta_reciprocal(self_handle);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyObject*
kth_py_native_chain_abla_config_set_theta_reciprocal(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    unsigned long long value = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OK", kwlist, &py_self, &value)) {
        return NULL;
    }
    kth_abla_config_mut_t self_handle = (kth_abla_config_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_ABLA_CONFIG);
    if (self_handle == NULL) return NULL;
    kth_chain_abla_config_set_theta_reciprocal(self_handle, (uint64_t)value);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_abla_config_delta(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_abla_config_const_t self_handle = (kth_abla_config_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_ABLA_CONFIG);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_abla_config_delta(self_handle);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyObject*
kth_py_native_chain_abla_config_set_delta(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    unsigned long long value = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OK", kwlist, &py_self, &value)) {
        return NULL;
    }
    kth_abla_config_mut_t self_handle = (kth_abla_config_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_ABLA_CONFIG);
    if (self_handle == NULL) return NULL;
    kth_chain_abla_config_set_delta(self_handle, (uint64_t)value);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_abla_config_epsilon_max(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_abla_config_const_t self_handle = (kth_abla_config_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_ABLA_CONFIG);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_abla_config_epsilon_max(self_handle);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyObject*
kth_py_native_chain_abla_config_set_epsilon_max(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    unsigned long long value = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OK", kwlist, &py_self, &value)) {
        return NULL;
    }
    kth_abla_config_mut_t self_handle = (kth_abla_config_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_ABLA_CONFIG);
    if (self_handle == NULL) return NULL;
    kth_chain_abla_config_set_epsilon_max(self_handle, (uint64_t)value);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_abla_config_beta_max(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_abla_config_const_t self_handle = (kth_abla_config_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_ABLA_CONFIG);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_abla_config_beta_max(self_handle);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyObject*
kth_py_native_chain_abla_config_set_beta_max(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    unsigned long long value = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OK", kwlist, &py_self, &value)) {
        return NULL;
    }
    kth_abla_config_mut_t self_handle = (kth_abla_config_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_ABLA_CONFIG);
    if (self_handle == NULL) return NULL;
    kth_chain_abla_config_set_beta_max(self_handle, (uint64_t)value);
    Py_RETURN_NONE;
}

PyMethodDef kth_py_native_chain_abla_config_methods[] = {
    {"chain_abla_config_copy", (PyCFunction)kth_py_native_chain_abla_config_copy, METH_O, NULL},
    {"chain_abla_config_destruct", (PyCFunction)kth_py_native_chain_abla_config_destruct, METH_O, NULL},
    {"chain_abla_config_epsilon0", (PyCFunction)kth_py_native_chain_abla_config_epsilon0, METH_O, NULL},
    {"chain_abla_config_set_epsilon0", (PyCFunction)kth_py_native_chain_abla_config_set_epsilon0, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_abla_config_beta0", (PyCFunction)kth_py_native_chain_abla_config_beta0, METH_O, NULL},
    {"chain_abla_config_set_beta0", (PyCFunction)kth_py_native_chain_abla_config_set_beta0, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_abla_config_n0", (PyCFunction)kth_py_native_chain_abla_config_n0, METH_O, NULL},
    {"chain_abla_config_set_n0", (PyCFunction)kth_py_native_chain_abla_config_set_n0, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_abla_config_gamma_reciprocal", (PyCFunction)kth_py_native_chain_abla_config_gamma_reciprocal, METH_O, NULL},
    {"chain_abla_config_set_gamma_reciprocal", (PyCFunction)kth_py_native_chain_abla_config_set_gamma_reciprocal, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_abla_config_zeta_xB7", (PyCFunction)kth_py_native_chain_abla_config_zeta_xB7, METH_O, NULL},
    {"chain_abla_config_set_zeta_xB7", (PyCFunction)kth_py_native_chain_abla_config_set_zeta_xB7, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_abla_config_theta_reciprocal", (PyCFunction)kth_py_native_chain_abla_config_theta_reciprocal, METH_O, NULL},
    {"chain_abla_config_set_theta_reciprocal", (PyCFunction)kth_py_native_chain_abla_config_set_theta_reciprocal, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_abla_config_delta", (PyCFunction)kth_py_native_chain_abla_config_delta, METH_O, NULL},
    {"chain_abla_config_set_delta", (PyCFunction)kth_py_native_chain_abla_config_set_delta, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_abla_config_epsilon_max", (PyCFunction)kth_py_native_chain_abla_config_epsilon_max, METH_O, NULL},
    {"chain_abla_config_set_epsilon_max", (PyCFunction)kth_py_native_chain_abla_config_set_epsilon_max, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_abla_config_beta_max", (PyCFunction)kth_py_native_chain_abla_config_beta_max, METH_O, NULL},
    {"chain_abla_config_set_beta_max", (PyCFunction)kth_py_native_chain_abla_config_set_beta_max, METH_VARARGS | METH_KEYWORDS, NULL},
    {NULL, NULL, 0, NULL}  // sentinel
};

#ifdef __cplusplus
} // extern "C"
#endif
