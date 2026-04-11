// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/py-native/chain/output.h>

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
void kth_py_native_chain_output_capsule_dtor(PyObject* capsule) {
    if ( ! PyCapsule_IsValid(capsule, KTH_PY_CAPSULE_CHAIN_OUTPUT)) return;
    kth_output_mut_t handle = (kth_output_mut_t)PyCapsule_GetPointer(capsule, KTH_PY_CAPSULE_CHAIN_OUTPUT);
    if (handle != NULL) kth_chain_output_destruct(handle);
}

PyObject*
kth_py_native_chain_output_construct_default(PyObject* self, PyObject* Py_UNUSED(args)) {
    auto result = kth_chain_output_construct_default();
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    return PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_OUTPUT, kth_py_native_chain_output_capsule_dtor);
}

PyObject*
kth_py_native_chain_output_construct_from_data(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"reader", (char*)"wire", NULL};
    char const* reader_buf = NULL;
    Py_ssize_t reader_size = 0;
    int wire = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "y#p", kwlist, &reader_buf, &reader_size, &wire)) {
        return NULL;
    }
    kth_output_mut_t out = NULL;
    kth_error_code_t result = kth_chain_output_construct_from_data((uint8_t const*)reader_buf, (kth_size_t)reader_size, (kth_bool_t)wire, &out);
    if (result != kth_ec_success) {
        PyErr_Format(PyExc_RuntimeError, "kth error code %d", (int)result);
        return NULL;
    }
    return PyCapsule_New((void*)out, KTH_PY_CAPSULE_CHAIN_OUTPUT, kth_py_native_chain_output_capsule_dtor);
}

PyObject*
kth_py_native_chain_output_copy(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_output_const_t self_handle = (kth_output_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_OUTPUT);
    if (self_handle == NULL) return NULL;
    auto result = kth_chain_output_copy(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    return PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_OUTPUT, kth_py_native_chain_output_capsule_dtor);
}

PyObject*
kth_py_native_chain_output_destruct(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_output_mut_t self_handle = (kth_output_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_OUTPUT);
    if (self_handle == NULL) return NULL;
    kth_chain_output_destruct(self_handle);
    PyCapsule_SetName(py_self, "kth.destroyed");
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_output_to_data(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"wire", NULL};
    PyObject* py_self = NULL;
    int wire = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Op", kwlist, &py_self, &wire)) {
        return NULL;
    }
    kth_output_const_t self_handle = (kth_output_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_OUTPUT);
    if (self_handle == NULL) return NULL;
    kth_size_t out_size = 0;
    auto result = kth_chain_output_to_data(self_handle, (kth_bool_t)wire, &out_size);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: serialization failed");
        return NULL;
    }
    PyObject* py_result = Py_BuildValue("y#", result, (Py_ssize_t)out_size);
    kth_core_destruct_array(result);
    return py_result;
}

PyObject*
kth_py_native_chain_output_serialized_size(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"wire", NULL};
    PyObject* py_self = NULL;
    int wire = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Op", kwlist, &py_self, &wire)) {
        return NULL;
    }
    kth_output_const_t self_handle = (kth_output_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_OUTPUT);
    if (self_handle == NULL) return NULL;
    auto result = kth_chain_output_serialized_size(self_handle, (kth_bool_t)wire);
    return PyLong_FromSize_t((size_t)result);
}

PyObject*
kth_py_native_chain_output_set_script(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    PyObject* py_value = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_value)) {
        return NULL;
    }
    kth_output_mut_t self_handle = (kth_output_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_OUTPUT);
    if (self_handle == NULL) return NULL;
    kth_script_const_t value_handle = (kth_script_const_t)PyCapsule_GetPointer(py_value, KTH_PY_CAPSULE_CHAIN_SCRIPT);
    if (value_handle == NULL) return NULL;
    kth_chain_output_set_script(self_handle, value_handle);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_output_address_simple(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"testnet", NULL};
    PyObject* py_self = NULL;
    int testnet = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Op", kwlist, &py_self, &testnet)) {
        return NULL;
    }
    kth_output_const_t self_handle = (kth_output_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_OUTPUT);
    if (self_handle == NULL) return NULL;
    auto result = kth_chain_output_address_simple(self_handle, (kth_bool_t)testnet);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
        return NULL;
    }
    return PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_PAYMENT_ADDRESS, NULL);
}

PyObject*
kth_py_native_chain_output_address(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"p2kh_version", (char*)"p2sh_version", NULL};
    PyObject* py_self = NULL;
    unsigned char p2kh_version = 0;
    unsigned char p2sh_version = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OBB", kwlist, &py_self, &p2kh_version, &p2sh_version)) {
        return NULL;
    }
    kth_output_const_t self_handle = (kth_output_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_OUTPUT);
    if (self_handle == NULL) return NULL;
    auto result = kth_chain_output_address(self_handle, (uint8_t)p2kh_version, (uint8_t)p2sh_version);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
        return NULL;
    }
    return PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_PAYMENT_ADDRESS, NULL);
}

PyObject*
kth_py_native_chain_output_addresses(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"p2kh_version", (char*)"p2sh_version", NULL};
    PyObject* py_self = NULL;
    unsigned char p2kh_version = 0;
    unsigned char p2sh_version = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OBB", kwlist, &py_self, &p2kh_version, &p2sh_version)) {
        return NULL;
    }
    kth_output_const_t self_handle = (kth_output_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_OUTPUT);
    if (self_handle == NULL) return NULL;
    auto result = kth_chain_output_addresses(self_handle, (uint8_t)p2kh_version, (uint8_t)p2sh_version);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL list returned");
        return NULL;
    }
    return PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_PAYMENT_ADDRESS_LIST, NULL);
}

PyObject*
kth_py_native_chain_output_equals(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"other", NULL};
    PyObject* py_self = NULL;
    PyObject* py_other = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_other)) {
        return NULL;
    }
    kth_output_const_t self_handle = (kth_output_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_OUTPUT);
    if (self_handle == NULL) return NULL;
    kth_output_const_t other_handle = (kth_output_const_t)PyCapsule_GetPointer(py_other, KTH_PY_CAPSULE_CHAIN_OUTPUT);
    if (other_handle == NULL) return NULL;
    auto result = kth_chain_output_equals(self_handle, other_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_output_is_valid(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_output_const_t self_handle = (kth_output_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_OUTPUT);
    if (self_handle == NULL) return NULL;
    auto result = kth_chain_output_is_valid(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_output_value(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_output_const_t self_handle = (kth_output_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_OUTPUT);
    if (self_handle == NULL) return NULL;
    auto result = kth_chain_output_value(self_handle);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyObject*
kth_py_native_chain_output_set_value(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    unsigned long long value = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OK", kwlist, &py_self, &value)) {
        return NULL;
    }
    kth_output_mut_t self_handle = (kth_output_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_OUTPUT);
    if (self_handle == NULL) return NULL;
    kth_chain_output_set_value(self_handle, (uint64_t)value);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_output_script(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_output_const_t self_handle = (kth_output_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_OUTPUT);
    if (self_handle == NULL) return NULL;
    auto result = kth_chain_output_script(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
        return NULL;
    }
    return PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_SCRIPT, NULL);
}

PyObject*
kth_py_native_chain_output_signature_operations(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"bip141", NULL};
    PyObject* py_self = NULL;
    int bip141 = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Op", kwlist, &py_self, &bip141)) {
        return NULL;
    }
    kth_output_const_t self_handle = (kth_output_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_OUTPUT);
    if (self_handle == NULL) return NULL;
    auto result = kth_chain_output_signature_operations(self_handle, (kth_bool_t)bip141);
    return PyLong_FromSize_t((size_t)result);
}

PyObject*
kth_py_native_chain_output_is_dust(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"minimum_output_value", NULL};
    PyObject* py_self = NULL;
    unsigned long long minimum_output_value = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OK", kwlist, &py_self, &minimum_output_value)) {
        return NULL;
    }
    kth_output_const_t self_handle = (kth_output_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_OUTPUT);
    if (self_handle == NULL) return NULL;
    auto result = kth_chain_output_is_dust(self_handle, (uint64_t)minimum_output_value);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_output_reset(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_output_mut_t self_handle = (kth_output_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_OUTPUT);
    if (self_handle == NULL) return NULL;
    kth_chain_output_reset(self_handle);
    Py_RETURN_NONE;
}

PyMethodDef kth_py_native_chain_output_methods[] = {
    {"chain_output_construct_default", (PyCFunction)kth_py_native_chain_output_construct_default, METH_NOARGS, NULL},
    {"chain_output_construct_from_data", (PyCFunction)kth_py_native_chain_output_construct_from_data, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_output_copy", (PyCFunction)kth_py_native_chain_output_copy, METH_O, NULL},
    {"chain_output_destruct", (PyCFunction)kth_py_native_chain_output_destruct, METH_O, NULL},
    {"chain_output_to_data", (PyCFunction)kth_py_native_chain_output_to_data, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_output_serialized_size", (PyCFunction)kth_py_native_chain_output_serialized_size, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_output_set_script", (PyCFunction)kth_py_native_chain_output_set_script, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_output_address_simple", (PyCFunction)kth_py_native_chain_output_address_simple, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_output_address", (PyCFunction)kth_py_native_chain_output_address, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_output_addresses", (PyCFunction)kth_py_native_chain_output_addresses, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_output_equals", (PyCFunction)kth_py_native_chain_output_equals, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_output_is_valid", (PyCFunction)kth_py_native_chain_output_is_valid, METH_O, NULL},
    {"chain_output_value", (PyCFunction)kth_py_native_chain_output_value, METH_O, NULL},
    {"chain_output_set_value", (PyCFunction)kth_py_native_chain_output_set_value, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_output_script", (PyCFunction)kth_py_native_chain_output_script, METH_O, NULL},
    {"chain_output_signature_operations", (PyCFunction)kth_py_native_chain_output_signature_operations, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_output_is_dust", (PyCFunction)kth_py_native_chain_output_is_dust, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_output_reset", (PyCFunction)kth_py_native_chain_output_reset, METH_O, NULL},
    {NULL, NULL, 0, NULL}  // sentinel
};

#ifdef __cplusplus
} // extern "C"
#endif
