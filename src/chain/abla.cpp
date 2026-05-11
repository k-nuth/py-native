// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/py-native/chain/abla.h>

#include <string.h>
#include <kth/capi.h>
#include <kth/capi/chain/abla.h>
#include <kth/py-native/capsule_names.h>
#include <kth/py-native/utils.h>

#ifdef __cplusplus
extern "C" {
#endif

PyObject*
kth_py_native_chain_abla_set_max(PyObject* self, PyObject* py_arg0) {
    PyObject* py_cfg = py_arg0;
    kth_abla_config_mut_t cfg_handle = (kth_abla_config_mut_t)PyCapsule_GetPointer(py_cfg, KTH_PY_CAPSULE_CHAIN_ABLA_CONFIG);
    if (cfg_handle == NULL) return NULL;
    kth_chain_abla_set_max(cfg_handle);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_abla_default_config(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"default_block_size", (char*)"fixed_size", NULL};
    unsigned long long default_block_size = 0;
    int fixed_size = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Kp", kwlist, &default_block_size, &fixed_size)) {
        return NULL;
    }
    auto const result = kth_chain_abla_default_config((uint64_t)default_block_size, (kth_bool_t)fixed_size);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
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
kth_py_native_chain_abla_validate_config(PyObject* self, PyObject* py_arg0) {
    PyObject* py_cfg = py_arg0;
    kth_abla_config_const_t cfg_handle = (kth_abla_config_const_t)PyCapsule_GetPointer(py_cfg, KTH_PY_CAPSULE_CHAIN_ABLA_CONFIG);
    if (cfg_handle == NULL) return NULL;
    auto const result = kth_chain_abla_validate_config(cfg_handle);
    return PyLong_FromLong((long)result);
}

PyObject*
kth_py_native_chain_abla_block_size_limit(PyObject* self, PyObject* py_arg0) {
    PyObject* py_st = py_arg0;
    kth_abla_state_const_t st_handle = (kth_abla_state_const_t)PyCapsule_GetPointer(py_st, KTH_PY_CAPSULE_CHAIN_ABLA_STATE);
    if (st_handle == NULL) return NULL;
    auto const result = kth_chain_abla_block_size_limit(st_handle);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyObject*
kth_py_native_chain_abla_validate_state(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"st", (char*)"cfg", NULL};
    PyObject* py_st = NULL;
    PyObject* py_cfg = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_st, &py_cfg)) {
        return NULL;
    }
    kth_abla_state_const_t st_handle = (kth_abla_state_const_t)PyCapsule_GetPointer(py_st, KTH_PY_CAPSULE_CHAIN_ABLA_STATE);
    if (st_handle == NULL) return NULL;
    kth_abla_config_const_t cfg_handle = (kth_abla_config_const_t)PyCapsule_GetPointer(py_cfg, KTH_PY_CAPSULE_CHAIN_ABLA_CONFIG);
    if (cfg_handle == NULL) return NULL;
    auto const result = kth_chain_abla_validate_state(st_handle, cfg_handle);
    return PyLong_FromLong((long)result);
}

PyMethodDef kth_py_native_chain_abla_methods[] = {
    {"chain_abla_set_max", (PyCFunction)kth_py_native_chain_abla_set_max, METH_O, NULL},
    {"chain_abla_default_config", (PyCFunction)kth_py_native_chain_abla_default_config, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_abla_validate_config", (PyCFunction)kth_py_native_chain_abla_validate_config, METH_O, NULL},
    {"chain_abla_block_size_limit", (PyCFunction)kth_py_native_chain_abla_block_size_limit, METH_O, NULL},
    {"chain_abla_validate_state", (PyCFunction)kth_py_native_chain_abla_validate_state, METH_VARARGS | METH_KEYWORDS, NULL},
    {NULL, NULL, 0, NULL}  // sentinel
};

#ifdef __cplusplus
} // extern "C"
#endif
