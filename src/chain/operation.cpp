// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/py-native/chain/operation.h>

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
void kth_py_native_chain_operation_capsule_dtor(PyObject* capsule) {
    if ( ! PyCapsule_IsValid(capsule, KTH_PY_CAPSULE_CHAIN_OPERATION)) return;
    kth_operation_mut_t handle = (kth_operation_mut_t)PyCapsule_GetPointer(capsule, KTH_PY_CAPSULE_CHAIN_OPERATION);
    if (handle != NULL) kth_chain_operation_destruct(handle);
}

PyObject*
kth_py_native_chain_operation_construct_default(PyObject* self, PyObject* Py_UNUSED(args)) {
    auto const result = kth_chain_operation_construct_default();
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_OPERATION, kth_py_native_chain_operation_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_operation_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_operation_construct_from_data(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"reader", NULL};
    char const* reader_buf = NULL;
    Py_ssize_t reader_size = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "y#", kwlist, &reader_buf, &reader_size)) {
        return NULL;
    }
    kth_operation_mut_t out = NULL;
    kth_error_code_t result = kth_chain_operation_construct_from_data((uint8_t const*)reader_buf, (kth_size_t)reader_size, &out);
    if (result != kth_ec_success) {
        PyErr_Format(PyExc_RuntimeError, "kth error code %d", (int)result);
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)out, KTH_PY_CAPSULE_CHAIN_OPERATION, kth_py_native_chain_operation_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_operation_destruct(out);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_operation_construct_from_uncoded_minimal(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"uncoded", (char*)"minimal", NULL};
    char const* uncoded_buf = NULL;
    Py_ssize_t uncoded_size = 0;
    int minimal = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "y#p", kwlist, &uncoded_buf, &uncoded_size, &minimal)) {
        return NULL;
    }
    auto const result = kth_chain_operation_construct_from_uncoded_minimal((uint8_t const*)uncoded_buf, (kth_size_t)uncoded_size, (kth_bool_t)minimal);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_OPERATION, kth_py_native_chain_operation_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_operation_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_operation_construct_from_code(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"code", NULL};
    unsigned char code = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "B", kwlist, &code)) {
        return NULL;
    }
    auto const result = kth_chain_operation_construct_from_code((kth_opcode_t)code);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_OPERATION, kth_py_native_chain_operation_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_operation_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_operation_copy(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_operation_const_t self_handle = (kth_operation_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_OPERATION);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_operation_copy(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_OPERATION, kth_py_native_chain_operation_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_operation_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_operation_destruct(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_operation_mut_t self_handle = (kth_operation_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_OPERATION);
    if (self_handle == NULL) return NULL;
    kth_chain_operation_destruct(self_handle);
    PyCapsule_SetName(py_self, "kth.destroyed");
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_operation_equals(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"other", NULL};
    PyObject* py_self = NULL;
    PyObject* py_other = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_other)) {
        return NULL;
    }
    kth_operation_const_t self_handle = (kth_operation_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_OPERATION);
    if (self_handle == NULL) return NULL;
    kth_operation_const_t other_handle = (kth_operation_const_t)PyCapsule_GetPointer(py_other, KTH_PY_CAPSULE_CHAIN_OPERATION);
    if (other_handle == NULL) return NULL;
    auto const result = kth_chain_operation_equals(self_handle, other_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_operation_from_string(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"mnemonic", NULL};
    PyObject* py_self = NULL;
    char const* mnemonic = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Os", kwlist, &py_self, &mnemonic)) {
        return NULL;
    }
    kth_operation_mut_t self_handle = (kth_operation_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_OPERATION);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_operation_from_string(self_handle, mnemonic);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_operation_is_valid(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_operation_const_t self_handle = (kth_operation_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_OPERATION);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_operation_is_valid(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_operation_to_data(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_operation_const_t self_handle = (kth_operation_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_OPERATION);
    if (self_handle == NULL) return NULL;
    kth_size_t out_size = 0;
    auto const result = kth_chain_operation_to_data(self_handle, &out_size);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: serialization failed");
        return NULL;
    }
    PyObject* py_result = Py_BuildValue("y#", result, (Py_ssize_t)out_size);
    kth_core_destruct_array(result);
    return py_result;
}

PyObject*
kth_py_native_chain_operation_to_string(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"active_flags", NULL};
    PyObject* py_self = NULL;
    unsigned long long active_flags = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OK", kwlist, &py_self, &active_flags)) {
        return NULL;
    }
    kth_operation_const_t self_handle = (kth_operation_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_OPERATION);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_operation_to_string(self_handle, (kth_script_flags_t)active_flags);
    if (result == NULL) Py_RETURN_NONE;
    PyObject* py_result = Py_BuildValue("s", result);
    kth_core_destruct_string(result);
    return py_result;
}

PyObject*
kth_py_native_chain_operation_serialized_size(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_operation_const_t self_handle = (kth_operation_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_OPERATION);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_operation_serialized_size(self_handle);
    return PyLong_FromSize_t((size_t)result);
}

PyObject*
kth_py_native_chain_operation_code(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_operation_const_t self_handle = (kth_operation_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_OPERATION);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_operation_code(self_handle);
    return PyLong_FromLong((long)result);
}

PyObject*
kth_py_native_chain_operation_data(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_operation_const_t self_handle = (kth_operation_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_OPERATION);
    if (self_handle == NULL) return NULL;
    kth_size_t out_size = 0;
    auto const result = kth_chain_operation_data(self_handle, &out_size);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: serialization failed");
        return NULL;
    }
    PyObject* py_result = Py_BuildValue("y#", result, (Py_ssize_t)out_size);
    kth_core_destruct_array(result);
    return py_result;
}

PyObject*
kth_py_native_chain_operation_opcode_from_size(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"size", NULL};
    Py_ssize_t size = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "n", kwlist, &size)) {
        return NULL;
    }
    if (size < 0) {
        PyErr_Format(PyExc_ValueError, "size must be non-negative, got %zd", size);
        return NULL;
    }
    auto const result = kth_chain_operation_opcode_from_size((kth_size_t)size);
    return PyLong_FromLong((long)result);
}

PyObject*
kth_py_native_chain_operation_minimal_opcode_from_data(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"data", NULL};
    char const* data_buf = NULL;
    Py_ssize_t data_size = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "y#", kwlist, &data_buf, &data_size)) {
        return NULL;
    }
    auto const result = kth_chain_operation_minimal_opcode_from_data((uint8_t const*)data_buf, (kth_size_t)data_size);
    return PyLong_FromLong((long)result);
}

PyObject*
kth_py_native_chain_operation_nominal_opcode_from_data(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"data", NULL};
    char const* data_buf = NULL;
    Py_ssize_t data_size = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "y#", kwlist, &data_buf, &data_size)) {
        return NULL;
    }
    auto const result = kth_chain_operation_nominal_opcode_from_data((uint8_t const*)data_buf, (kth_size_t)data_size);
    return PyLong_FromLong((long)result);
}

PyObject*
kth_py_native_chain_operation_opcode_from_positive(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"value", NULL};
    unsigned char value = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "B", kwlist, &value)) {
        return NULL;
    }
    auto const result = kth_chain_operation_opcode_from_positive((uint8_t)value);
    return PyLong_FromLong((long)result);
}

PyObject*
kth_py_native_chain_operation_opcode_to_positive(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"code", NULL};
    unsigned char code = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "B", kwlist, &code)) {
        return NULL;
    }
    auto const result = kth_chain_operation_opcode_to_positive((kth_opcode_t)code);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyObject*
kth_py_native_chain_operation_is_push(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"code", NULL};
    unsigned char code = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "B", kwlist, &code)) {
        return NULL;
    }
    auto const result = kth_chain_operation_is_push((kth_opcode_t)code);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_operation_is_payload(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"code", NULL};
    unsigned char code = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "B", kwlist, &code)) {
        return NULL;
    }
    auto const result = kth_chain_operation_is_payload((kth_opcode_t)code);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_operation_is_counted(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"code", NULL};
    unsigned char code = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "B", kwlist, &code)) {
        return NULL;
    }
    auto const result = kth_chain_operation_is_counted((kth_opcode_t)code);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_operation_is_version(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"code", NULL};
    unsigned char code = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "B", kwlist, &code)) {
        return NULL;
    }
    auto const result = kth_chain_operation_is_version((kth_opcode_t)code);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_operation_is_numeric(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"code", NULL};
    unsigned char code = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "B", kwlist, &code)) {
        return NULL;
    }
    auto const result = kth_chain_operation_is_numeric((kth_opcode_t)code);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_operation_is_positive(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"code", NULL};
    unsigned char code = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "B", kwlist, &code)) {
        return NULL;
    }
    auto const result = kth_chain_operation_is_positive((kth_opcode_t)code);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_operation_is_reserved(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"code", NULL};
    unsigned char code = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "B", kwlist, &code)) {
        return NULL;
    }
    auto const result = kth_chain_operation_is_reserved((kth_opcode_t)code);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_operation_is_disabled(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"code", (char*)"active_flags", NULL};
    unsigned char code = 0;
    unsigned long long active_flags = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "BK", kwlist, &code, &active_flags)) {
        return NULL;
    }
    auto const result = kth_chain_operation_is_disabled((kth_opcode_t)code, (kth_script_flags_t)active_flags);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_operation_is_conditional(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"code", NULL};
    unsigned char code = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "B", kwlist, &code)) {
        return NULL;
    }
    auto const result = kth_chain_operation_is_conditional((kth_opcode_t)code);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_operation_is_relaxed_push(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"code", NULL};
    unsigned char code = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "B", kwlist, &code)) {
        return NULL;
    }
    auto const result = kth_chain_operation_is_relaxed_push((kth_opcode_t)code);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_operation_is_push_simple(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_operation_const_t self_handle = (kth_operation_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_OPERATION);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_operation_is_push_simple(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_operation_is_counted_simple(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_operation_const_t self_handle = (kth_operation_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_OPERATION);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_operation_is_counted_simple(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_operation_is_version_simple(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_operation_const_t self_handle = (kth_operation_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_OPERATION);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_operation_is_version_simple(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_operation_is_positive_simple(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_operation_const_t self_handle = (kth_operation_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_OPERATION);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_operation_is_positive_simple(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_operation_is_disabled_simple(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"active_flags", NULL};
    PyObject* py_self = NULL;
    unsigned long long active_flags = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OK", kwlist, &py_self, &active_flags)) {
        return NULL;
    }
    kth_operation_const_t self_handle = (kth_operation_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_OPERATION);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_operation_is_disabled_simple(self_handle, (kth_script_flags_t)active_flags);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_operation_is_conditional_simple(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_operation_const_t self_handle = (kth_operation_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_OPERATION);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_operation_is_conditional_simple(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_operation_is_relaxed_push_simple(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_operation_const_t self_handle = (kth_operation_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_OPERATION);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_operation_is_relaxed_push_simple(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_operation_is_oversized(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"max_size", NULL};
    PyObject* py_self = NULL;
    Py_ssize_t max_size = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "On", kwlist, &py_self, &max_size)) {
        return NULL;
    }
    kth_operation_const_t self_handle = (kth_operation_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_OPERATION);
    if (self_handle == NULL) return NULL;
    if (max_size < 0) {
        PyErr_Format(PyExc_ValueError, "max_size must be non-negative, got %zd", max_size);
        return NULL;
    }
    auto const result = kth_chain_operation_is_oversized(self_handle, (kth_size_t)max_size);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_operation_is_minimal_push(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_operation_const_t self_handle = (kth_operation_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_OPERATION);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_operation_is_minimal_push(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_operation_is_nominal_push(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_operation_const_t self_handle = (kth_operation_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_OPERATION);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_operation_is_nominal_push(self_handle);
    return PyBool_FromLong((long)result);
}

PyMethodDef kth_py_native_chain_operation_methods[] = {
    {"chain_operation_construct_default", (PyCFunction)kth_py_native_chain_operation_construct_default, METH_NOARGS, NULL},
    {"chain_operation_construct_from_data", (PyCFunction)kth_py_native_chain_operation_construct_from_data, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_operation_construct_from_uncoded_minimal", (PyCFunction)kth_py_native_chain_operation_construct_from_uncoded_minimal, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_operation_construct_from_code", (PyCFunction)kth_py_native_chain_operation_construct_from_code, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_operation_copy", (PyCFunction)kth_py_native_chain_operation_copy, METH_O, NULL},
    {"chain_operation_destruct", (PyCFunction)kth_py_native_chain_operation_destruct, METH_O, NULL},
    {"chain_operation_equals", (PyCFunction)kth_py_native_chain_operation_equals, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_operation_from_string", (PyCFunction)kth_py_native_chain_operation_from_string, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_operation_is_valid", (PyCFunction)kth_py_native_chain_operation_is_valid, METH_O, NULL},
    {"chain_operation_to_data", (PyCFunction)kth_py_native_chain_operation_to_data, METH_O, NULL},
    {"chain_operation_to_string", (PyCFunction)kth_py_native_chain_operation_to_string, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_operation_serialized_size", (PyCFunction)kth_py_native_chain_operation_serialized_size, METH_O, NULL},
    {"chain_operation_code", (PyCFunction)kth_py_native_chain_operation_code, METH_O, NULL},
    {"chain_operation_data", (PyCFunction)kth_py_native_chain_operation_data, METH_O, NULL},
    {"chain_operation_opcode_from_size", (PyCFunction)kth_py_native_chain_operation_opcode_from_size, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_operation_minimal_opcode_from_data", (PyCFunction)kth_py_native_chain_operation_minimal_opcode_from_data, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_operation_nominal_opcode_from_data", (PyCFunction)kth_py_native_chain_operation_nominal_opcode_from_data, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_operation_opcode_from_positive", (PyCFunction)kth_py_native_chain_operation_opcode_from_positive, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_operation_opcode_to_positive", (PyCFunction)kth_py_native_chain_operation_opcode_to_positive, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_operation_is_push", (PyCFunction)kth_py_native_chain_operation_is_push, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_operation_is_payload", (PyCFunction)kth_py_native_chain_operation_is_payload, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_operation_is_counted", (PyCFunction)kth_py_native_chain_operation_is_counted, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_operation_is_version", (PyCFunction)kth_py_native_chain_operation_is_version, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_operation_is_numeric", (PyCFunction)kth_py_native_chain_operation_is_numeric, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_operation_is_positive", (PyCFunction)kth_py_native_chain_operation_is_positive, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_operation_is_reserved", (PyCFunction)kth_py_native_chain_operation_is_reserved, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_operation_is_disabled", (PyCFunction)kth_py_native_chain_operation_is_disabled, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_operation_is_conditional", (PyCFunction)kth_py_native_chain_operation_is_conditional, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_operation_is_relaxed_push", (PyCFunction)kth_py_native_chain_operation_is_relaxed_push, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_operation_is_push_simple", (PyCFunction)kth_py_native_chain_operation_is_push_simple, METH_O, NULL},
    {"chain_operation_is_counted_simple", (PyCFunction)kth_py_native_chain_operation_is_counted_simple, METH_O, NULL},
    {"chain_operation_is_version_simple", (PyCFunction)kth_py_native_chain_operation_is_version_simple, METH_O, NULL},
    {"chain_operation_is_positive_simple", (PyCFunction)kth_py_native_chain_operation_is_positive_simple, METH_O, NULL},
    {"chain_operation_is_disabled_simple", (PyCFunction)kth_py_native_chain_operation_is_disabled_simple, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_operation_is_conditional_simple", (PyCFunction)kth_py_native_chain_operation_is_conditional_simple, METH_O, NULL},
    {"chain_operation_is_relaxed_push_simple", (PyCFunction)kth_py_native_chain_operation_is_relaxed_push_simple, METH_O, NULL},
    {"chain_operation_is_oversized", (PyCFunction)kth_py_native_chain_operation_is_oversized, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_operation_is_minimal_push", (PyCFunction)kth_py_native_chain_operation_is_minimal_push, METH_O, NULL},
    {"chain_operation_is_nominal_push", (PyCFunction)kth_py_native_chain_operation_is_nominal_push, METH_O, NULL},
    {NULL, NULL, 0, NULL}  // sentinel
};

#ifdef __cplusplus
} // extern "C"
#endif
