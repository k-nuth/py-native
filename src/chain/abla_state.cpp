// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/py-native/chain/abla_state.h>

#include <string.h>
#include <kth/capi.h>
#include <kth/capi/chain/abla_state.h>
#include <kth/py-native/capsule_names.h>
#include <kth/py-native/utils.h>

#ifdef __cplusplus
extern "C" {
#endif

// PyCapsule destructor — released by GC when the capsule is
// collected. Explicit `destruct` calls set the capsule name to
// "kth.destroyed", so PyCapsule_IsValid returns false and this
// destructor becomes a no-op (no double-free).
void kth_py_native_chain_abla_state_capsule_dtor(PyObject* capsule) {
    if ( ! PyCapsule_IsValid(capsule, KTH_PY_CAPSULE_CHAIN_ABLA_STATE)) return;
    kth_abla_state_mut_t handle = (kth_abla_state_mut_t)PyCapsule_GetPointer(capsule, KTH_PY_CAPSULE_CHAIN_ABLA_STATE);
    if (handle != NULL) kth_chain_abla_state_destruct(handle);
}

PyObject*
kth_py_native_chain_abla_state_construct_default(PyObject* self, PyObject* Py_UNUSED(args)) {
    auto const result = kth_chain_abla_state_construct_default();
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_ABLA_STATE, kth_py_native_chain_abla_state_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_abla_state_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_abla_state_construct(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"cfg", (char*)"block_size", NULL};
    PyObject* py_cfg = NULL;
    unsigned long long block_size = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OK", kwlist, &py_cfg, &block_size)) {
        return NULL;
    }
    kth_abla_config_const_t cfg_handle = (kth_abla_config_const_t)PyCapsule_GetPointer(py_cfg, KTH_PY_CAPSULE_CHAIN_ABLA_CONFIG);
    if (cfg_handle == NULL) return NULL;
    auto const result = kth_chain_abla_state_construct(cfg_handle, (uint64_t)block_size);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_ABLA_STATE, kth_py_native_chain_abla_state_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_abla_state_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_abla_state_copy(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_abla_state_const_t self_handle = (kth_abla_state_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_ABLA_STATE);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_abla_state_copy(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_ABLA_STATE, kth_py_native_chain_abla_state_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_abla_state_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_abla_state_destruct(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_abla_state_mut_t self_handle = (kth_abla_state_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_ABLA_STATE);
    if (self_handle == NULL) return NULL;
    kth_chain_abla_state_destruct(self_handle);
    PyCapsule_SetName(py_self, "kth.destroyed");
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_abla_state_block_size(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_abla_state_const_t self_handle = (kth_abla_state_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_ABLA_STATE);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_abla_state_block_size(self_handle);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyObject*
kth_py_native_chain_abla_state_set_block_size(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    unsigned long long value = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OK", kwlist, &py_self, &value)) {
        return NULL;
    }
    kth_abla_state_mut_t self_handle = (kth_abla_state_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_ABLA_STATE);
    if (self_handle == NULL) return NULL;
    kth_chain_abla_state_set_block_size(self_handle, (uint64_t)value);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_abla_state_control_block_size(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_abla_state_const_t self_handle = (kth_abla_state_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_ABLA_STATE);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_abla_state_control_block_size(self_handle);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyObject*
kth_py_native_chain_abla_state_set_control_block_size(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    unsigned long long value = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OK", kwlist, &py_self, &value)) {
        return NULL;
    }
    kth_abla_state_mut_t self_handle = (kth_abla_state_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_ABLA_STATE);
    if (self_handle == NULL) return NULL;
    kth_chain_abla_state_set_control_block_size(self_handle, (uint64_t)value);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_abla_state_elastic_buffer_size(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_abla_state_const_t self_handle = (kth_abla_state_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_ABLA_STATE);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_abla_state_elastic_buffer_size(self_handle);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyObject*
kth_py_native_chain_abla_state_set_elastic_buffer_size(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    unsigned long long value = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OK", kwlist, &py_self, &value)) {
        return NULL;
    }
    kth_abla_state_mut_t self_handle = (kth_abla_state_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_ABLA_STATE);
    if (self_handle == NULL) return NULL;
    kth_chain_abla_state_set_elastic_buffer_size(self_handle, (uint64_t)value);
    Py_RETURN_NONE;
}

PyMethodDef kth_py_native_chain_abla_state_methods[] = {
    {"chain_abla_state_construct_default", (PyCFunction)kth_py_native_chain_abla_state_construct_default, METH_NOARGS, NULL},
    {"chain_abla_state_construct", (PyCFunction)kth_py_native_chain_abla_state_construct, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_abla_state_copy", (PyCFunction)kth_py_native_chain_abla_state_copy, METH_O, NULL},
    {"chain_abla_state_destruct", (PyCFunction)kth_py_native_chain_abla_state_destruct, METH_O, NULL},
    {"chain_abla_state_block_size", (PyCFunction)kth_py_native_chain_abla_state_block_size, METH_O, NULL},
    {"chain_abla_state_set_block_size", (PyCFunction)kth_py_native_chain_abla_state_set_block_size, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_abla_state_control_block_size", (PyCFunction)kth_py_native_chain_abla_state_control_block_size, METH_O, NULL},
    {"chain_abla_state_set_control_block_size", (PyCFunction)kth_py_native_chain_abla_state_set_control_block_size, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_abla_state_elastic_buffer_size", (PyCFunction)kth_py_native_chain_abla_state_elastic_buffer_size, METH_O, NULL},
    {"chain_abla_state_set_elastic_buffer_size", (PyCFunction)kth_py_native_chain_abla_state_set_elastic_buffer_size, METH_VARARGS | METH_KEYWORDS, NULL},
    {NULL, NULL, 0, NULL}  // sentinel
};

#ifdef __cplusplus
} // extern "C"
#endif
