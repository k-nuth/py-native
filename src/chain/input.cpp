// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/py-native/chain/input.h>

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
void kth_py_native_chain_input_capsule_dtor(PyObject* capsule) {
    if ( ! PyCapsule_IsValid(capsule, KTH_PY_CAPSULE_CHAIN_INPUT)) return;
    kth_input_mut_t handle = (kth_input_mut_t)PyCapsule_GetPointer(capsule, KTH_PY_CAPSULE_CHAIN_INPUT);
    if (handle != NULL) kth_chain_input_destruct(handle);
}

PyObject*
kth_py_native_chain_input_construct_default(PyObject* self, PyObject* Py_UNUSED(args)) {
    auto const result = kth_chain_input_construct_default();
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_INPUT, kth_py_native_chain_input_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_input_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_input_construct_from_data(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"reader", (char*)"wire", NULL};
    char const* reader_buf = NULL;
    Py_ssize_t reader_size = 0;
    int wire = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "y#p", kwlist, &reader_buf, &reader_size, &wire)) {
        return NULL;
    }
    kth_input_mut_t out = NULL;
    kth_error_code_t result = kth_chain_input_construct_from_data((uint8_t const*)reader_buf, (kth_size_t)reader_size, (kth_bool_t)wire, &out);
    if (result != kth_ec_success) {
        PyErr_Format(PyExc_RuntimeError, "kth error code %d", (int)result);
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)out, KTH_PY_CAPSULE_CHAIN_INPUT, kth_py_native_chain_input_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_input_destruct(out);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_input_construct(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"previous_output", (char*)"script", (char*)"sequence", NULL};
    PyObject* py_previous_output = NULL;
    PyObject* py_script = NULL;
    unsigned int sequence = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OOI", kwlist, &py_previous_output, &py_script, &sequence)) {
        return NULL;
    }
    kth_output_point_const_t previous_output_handle = (kth_output_point_const_t)PyCapsule_GetPointer(py_previous_output, KTH_PY_CAPSULE_CHAIN_OUTPUT_POINT);
    if (previous_output_handle == NULL) return NULL;
    kth_script_const_t script_handle = (kth_script_const_t)PyCapsule_GetPointer(py_script, KTH_PY_CAPSULE_CHAIN_SCRIPT);
    if (script_handle == NULL) return NULL;
    auto const result = kth_chain_input_construct(previous_output_handle, script_handle, (uint32_t)sequence);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_INPUT, kth_py_native_chain_input_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_input_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_input_copy(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_input_const_t self_handle = (kth_input_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_INPUT);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_input_copy(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_INPUT, kth_py_native_chain_input_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_input_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_input_destruct(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_input_mut_t self_handle = (kth_input_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_INPUT);
    if (self_handle == NULL) return NULL;
    kth_chain_input_destruct(self_handle);
    PyCapsule_SetName(py_self, "kth.destroyed");
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_input_set_script(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    PyObject* py_value = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_value)) {
        return NULL;
    }
    kth_input_mut_t self_handle = (kth_input_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_INPUT);
    if (self_handle == NULL) return NULL;
    kth_script_const_t value_handle = (kth_script_const_t)PyCapsule_GetPointer(py_value, KTH_PY_CAPSULE_CHAIN_SCRIPT);
    if (value_handle == NULL) return NULL;
    kth_chain_input_set_script(self_handle, value_handle);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_input_address(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_input_const_t self_handle = (kth_input_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_INPUT);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_input_address(self_handle);
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
kth_py_native_chain_input_addresses(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_input_const_t self_handle = (kth_input_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_INPUT);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_input_addresses(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL list returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_PAYMENT_ADDRESS_LIST, kth_py_native_wallet_payment_address_list_capsule_dtor);
    if (capsule == NULL) {
        kth_wallet_payment_address_list_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_input_reset(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_input_mut_t self_handle = (kth_input_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_INPUT);
    if (self_handle == NULL) return NULL;
    kth_chain_input_reset(self_handle);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_input_equals(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"other", NULL};
    PyObject* py_self = NULL;
    PyObject* py_other = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_other)) {
        return NULL;
    }
    kth_input_const_t self_handle = (kth_input_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_INPUT);
    if (self_handle == NULL) return NULL;
    kth_input_const_t other_handle = (kth_input_const_t)PyCapsule_GetPointer(py_other, KTH_PY_CAPSULE_CHAIN_INPUT);
    if (other_handle == NULL) return NULL;
    auto const result = kth_chain_input_equals(self_handle, other_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_input_is_valid(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_input_const_t self_handle = (kth_input_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_INPUT);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_input_is_valid(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_input_to_data(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"wire", NULL};
    PyObject* py_self = NULL;
    int wire = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Op", kwlist, &py_self, &wire)) {
        return NULL;
    }
    kth_input_const_t self_handle = (kth_input_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_INPUT);
    if (self_handle == NULL) return NULL;
    kth_size_t out_size = 0;
    auto const result = kth_chain_input_to_data(self_handle, (kth_bool_t)wire, &out_size);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: serialization failed");
        return NULL;
    }
    PyObject* py_result = Py_BuildValue("y#", result, (Py_ssize_t)out_size);
    kth_core_destruct_array(result);
    return py_result;
}

PyObject*
kth_py_native_chain_input_serialized_size(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"wire", NULL};
    PyObject* py_self = NULL;
    int wire = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Op", kwlist, &py_self, &wire)) {
        return NULL;
    }
    kth_input_const_t self_handle = (kth_input_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_INPUT);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_input_serialized_size(self_handle, (kth_bool_t)wire);
    return PyLong_FromSize_t((size_t)result);
}

PyObject*
kth_py_native_chain_input_previous_output(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_input_const_t self_handle = (kth_input_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_INPUT);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_input_previous_output(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_OUTPUT_POINT, kth_py_native_borrowed_parent_dtor);
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
kth_py_native_chain_input_set_previous_output(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    PyObject* py_value = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_value)) {
        return NULL;
    }
    kth_input_mut_t self_handle = (kth_input_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_INPUT);
    if (self_handle == NULL) return NULL;
    kth_output_point_const_t value_handle = (kth_output_point_const_t)PyCapsule_GetPointer(py_value, KTH_PY_CAPSULE_CHAIN_OUTPUT_POINT);
    if (value_handle == NULL) return NULL;
    kth_chain_input_set_previous_output(self_handle, value_handle);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_input_script(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_input_const_t self_handle = (kth_input_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_INPUT);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_input_script(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_SCRIPT, kth_py_native_borrowed_parent_dtor);
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
kth_py_native_chain_input_sequence(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_input_const_t self_handle = (kth_input_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_INPUT);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_input_sequence(self_handle);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyObject*
kth_py_native_chain_input_set_sequence(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    unsigned int value = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OI", kwlist, &py_self, &value)) {
        return NULL;
    }
    kth_input_mut_t self_handle = (kth_input_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_INPUT);
    if (self_handle == NULL) return NULL;
    kth_chain_input_set_sequence(self_handle, (uint32_t)value);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_input_is_final(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_input_const_t self_handle = (kth_input_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_INPUT);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_input_is_final(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_input_is_locked(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"block_height", (char*)"median_time_past", NULL};
    PyObject* py_self = NULL;
    Py_ssize_t block_height = 0;
    unsigned int median_time_past = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OnI", kwlist, &py_self, &block_height, &median_time_past)) {
        return NULL;
    }
    kth_input_const_t self_handle = (kth_input_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_INPUT);
    if (self_handle == NULL) return NULL;
    if (block_height < 0) {
        PyErr_Format(PyExc_ValueError, "block_height must be non-negative, got %zd", block_height);
        return NULL;
    }
    auto const result = kth_chain_input_is_locked(self_handle, (kth_size_t)block_height, (uint32_t)median_time_past);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_input_signature_operations(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"bip16", (char*)"bip141", NULL};
    PyObject* py_self = NULL;
    int bip16 = 0;
    int bip141 = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Opp", kwlist, &py_self, &bip16, &bip141)) {
        return NULL;
    }
    kth_input_const_t self_handle = (kth_input_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_INPUT);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_input_signature_operations(self_handle, (kth_bool_t)bip16, (kth_bool_t)bip141);
    return PyLong_FromSize_t((size_t)result);
}

PyObject*
kth_py_native_chain_input_extract_embedded_script(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_input_const_t self_handle = (kth_input_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_INPUT);
    if (self_handle == NULL) return NULL;
    kth_script_mut_t out = NULL;
    kth_error_code_t result = kth_chain_input_extract_embedded_script(self_handle, &out);
    if (result != kth_ec_success) {
        PyErr_Format(PyExc_RuntimeError, "kth error code %d", (int)result);
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)out, KTH_PY_CAPSULE_CHAIN_SCRIPT, kth_py_native_chain_script_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_script_destruct(out);
        return NULL;
    }
    return capsule;
}

PyMethodDef kth_py_native_chain_input_methods[] = {
    {"chain_input_construct_default", (PyCFunction)kth_py_native_chain_input_construct_default, METH_NOARGS, NULL},
    {"chain_input_construct_from_data", (PyCFunction)kth_py_native_chain_input_construct_from_data, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_input_construct", (PyCFunction)kth_py_native_chain_input_construct, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_input_copy", (PyCFunction)kth_py_native_chain_input_copy, METH_O, NULL},
    {"chain_input_destruct", (PyCFunction)kth_py_native_chain_input_destruct, METH_O, NULL},
    {"chain_input_set_script", (PyCFunction)kth_py_native_chain_input_set_script, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_input_address", (PyCFunction)kth_py_native_chain_input_address, METH_O, NULL},
    {"chain_input_addresses", (PyCFunction)kth_py_native_chain_input_addresses, METH_O, NULL},
    {"chain_input_reset", (PyCFunction)kth_py_native_chain_input_reset, METH_O, NULL},
    {"chain_input_equals", (PyCFunction)kth_py_native_chain_input_equals, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_input_is_valid", (PyCFunction)kth_py_native_chain_input_is_valid, METH_O, NULL},
    {"chain_input_to_data", (PyCFunction)kth_py_native_chain_input_to_data, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_input_serialized_size", (PyCFunction)kth_py_native_chain_input_serialized_size, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_input_previous_output", (PyCFunction)kth_py_native_chain_input_previous_output, METH_O, NULL},
    {"chain_input_set_previous_output", (PyCFunction)kth_py_native_chain_input_set_previous_output, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_input_script", (PyCFunction)kth_py_native_chain_input_script, METH_O, NULL},
    {"chain_input_sequence", (PyCFunction)kth_py_native_chain_input_sequence, METH_O, NULL},
    {"chain_input_set_sequence", (PyCFunction)kth_py_native_chain_input_set_sequence, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_input_is_final", (PyCFunction)kth_py_native_chain_input_is_final, METH_O, NULL},
    {"chain_input_is_locked", (PyCFunction)kth_py_native_chain_input_is_locked, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_input_signature_operations", (PyCFunction)kth_py_native_chain_input_signature_operations, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_input_extract_embedded_script", (PyCFunction)kth_py_native_chain_input_extract_embedded_script, METH_O, NULL},
    {NULL, NULL, 0, NULL}  // sentinel
};

#ifdef __cplusplus
} // extern "C"
#endif
