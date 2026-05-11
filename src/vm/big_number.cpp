// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/py-native/vm/big_number.h>

#include <string.h>
#include <kth/capi.h>
#include <kth/capi/vm/big_number.h>
#include <kth/py-native/capsule_names.h>
#include <kth/py-native/utils.h>

#ifdef __cplusplus
extern "C" {
#endif

// PyCapsule destructor — released by GC when the capsule is
// collected. Explicit `destruct` calls set the capsule name to
// "kth.destroyed", so PyCapsule_IsValid returns false and this
// destructor becomes a no-op (no double-free).
void kth_py_native_vm_big_number_capsule_dtor(PyObject* capsule) {
    if ( ! PyCapsule_IsValid(capsule, KTH_PY_CAPSULE_VM_BIG_NUMBER)) return;
    kth_big_number_mut_t handle = (kth_big_number_mut_t)PyCapsule_GetPointer(capsule, KTH_PY_CAPSULE_VM_BIG_NUMBER);
    if (handle != NULL) kth_vm_big_number_destruct(handle);
}

PyObject*
kth_py_native_vm_big_number_construct_default(PyObject* self, PyObject* Py_UNUSED(args)) {
    auto const result = kth_vm_big_number_construct_default();
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_VM_BIG_NUMBER, kth_py_native_vm_big_number_capsule_dtor);
    if (capsule == NULL) {
        kth_vm_big_number_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_vm_big_number_construct_from_value(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"value", NULL};
    long long value = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "L", kwlist, &value)) {
        return NULL;
    }
    auto const result = kth_vm_big_number_construct_from_value((int64_t)value);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_VM_BIG_NUMBER, kth_py_native_vm_big_number_capsule_dtor);
    if (capsule == NULL) {
        kth_vm_big_number_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_vm_big_number_construct_from_decimal_str(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"decimal_str", NULL};
    char const* decimal_str = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "s", kwlist, &decimal_str)) {
        return NULL;
    }
    auto const result = kth_vm_big_number_construct_from_decimal_str(decimal_str);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_VM_BIG_NUMBER, kth_py_native_vm_big_number_capsule_dtor);
    if (capsule == NULL) {
        kth_vm_big_number_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_vm_big_number_copy(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_big_number_const_t self_handle = (kth_big_number_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_BIG_NUMBER);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_big_number_copy(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_VM_BIG_NUMBER, kth_py_native_vm_big_number_capsule_dtor);
    if (capsule == NULL) {
        kth_vm_big_number_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_vm_big_number_destruct(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_big_number_mut_t self_handle = (kth_big_number_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_BIG_NUMBER);
    if (self_handle == NULL) return NULL;
    kth_vm_big_number_destruct(self_handle);
    PyCapsule_SetName(py_self, "kth.destroyed");
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_vm_big_number_from_hex(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"hex_str", NULL};
    char const* hex_str = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "s", kwlist, &hex_str)) {
        return NULL;
    }
    auto const result = kth_vm_big_number_from_hex(hex_str);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_VM_BIG_NUMBER, kth_py_native_vm_big_number_capsule_dtor);
    if (capsule == NULL) {
        kth_vm_big_number_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_vm_big_number_serialize(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_big_number_const_t self_handle = (kth_big_number_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_BIG_NUMBER);
    if (self_handle == NULL) return NULL;
    kth_size_t out_size = 0;
    auto const result = kth_vm_big_number_serialize(self_handle, &out_size);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: serialization failed");
        return NULL;
    }
    PyObject* py_result = Py_BuildValue("y#", result, (Py_ssize_t)out_size);
    kth_core_destruct_array(result);
    return py_result;
}

PyObject*
kth_py_native_vm_big_number_deserialize(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"data", NULL};
    PyObject* py_self = NULL;
    char const* data_buf = NULL;
    Py_ssize_t data_size = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Oy#", kwlist, &py_self, &data_buf, &data_size)) {
        return NULL;
    }
    kth_big_number_mut_t self_handle = (kth_big_number_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_BIG_NUMBER);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_big_number_deserialize(self_handle, (uint8_t const*)data_buf, (kth_size_t)data_size);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_vm_big_number_to_string(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_big_number_const_t self_handle = (kth_big_number_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_BIG_NUMBER);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_big_number_to_string(self_handle);
    if (result == NULL) Py_RETURN_NONE;
    PyObject* py_result = Py_BuildValue("s", result);
    kth_core_destruct_string(result);
    return py_result;
}

PyObject*
kth_py_native_vm_big_number_to_hex(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_big_number_const_t self_handle = (kth_big_number_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_BIG_NUMBER);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_big_number_to_hex(self_handle);
    if (result == NULL) Py_RETURN_NONE;
    PyObject* py_result = Py_BuildValue("s", result);
    kth_core_destruct_string(result);
    return py_result;
}

PyObject*
kth_py_native_vm_big_number_sign(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_big_number_const_t self_handle = (kth_big_number_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_BIG_NUMBER);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_big_number_sign(self_handle);
    return PyLong_FromLongLong((long long)result);
}

PyObject*
kth_py_native_vm_big_number_is_zero(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_big_number_const_t self_handle = (kth_big_number_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_BIG_NUMBER);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_big_number_is_zero(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_vm_big_number_is_nonzero(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_big_number_const_t self_handle = (kth_big_number_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_BIG_NUMBER);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_big_number_is_nonzero(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_vm_big_number_is_negative(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_big_number_const_t self_handle = (kth_big_number_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_BIG_NUMBER);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_big_number_is_negative(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_vm_big_number_to_int32_saturating(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_big_number_const_t self_handle = (kth_big_number_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_BIG_NUMBER);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_big_number_to_int32_saturating(self_handle);
    return PyLong_FromLongLong((long long)result);
}

PyObject*
kth_py_native_vm_big_number_byte_count(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_big_number_const_t self_handle = (kth_big_number_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_BIG_NUMBER);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_big_number_byte_count(self_handle);
    return PyLong_FromSize_t((size_t)result);
}

PyObject*
kth_py_native_vm_big_number_compare(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"other", NULL};
    PyObject* py_self = NULL;
    PyObject* py_other = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_other)) {
        return NULL;
    }
    kth_big_number_const_t self_handle = (kth_big_number_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_BIG_NUMBER);
    if (self_handle == NULL) return NULL;
    kth_big_number_const_t other_handle = (kth_big_number_const_t)PyCapsule_GetPointer(py_other, KTH_PY_CAPSULE_VM_BIG_NUMBER);
    if (other_handle == NULL) return NULL;
    auto const result = kth_vm_big_number_compare(self_handle, other_handle);
    return PyLong_FromLongLong((long long)result);
}

PyObject*
kth_py_native_vm_big_number_equals(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"other", NULL};
    PyObject* py_self = NULL;
    PyObject* py_other = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_other)) {
        return NULL;
    }
    kth_big_number_const_t self_handle = (kth_big_number_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_BIG_NUMBER);
    if (self_handle == NULL) return NULL;
    kth_big_number_const_t other_handle = (kth_big_number_const_t)PyCapsule_GetPointer(py_other, KTH_PY_CAPSULE_VM_BIG_NUMBER);
    if (other_handle == NULL) return NULL;
    auto const result = kth_vm_big_number_equals(self_handle, other_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_vm_big_number_add(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"other", NULL};
    PyObject* py_self = NULL;
    PyObject* py_other = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_other)) {
        return NULL;
    }
    kth_big_number_const_t self_handle = (kth_big_number_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_BIG_NUMBER);
    if (self_handle == NULL) return NULL;
    kth_big_number_const_t other_handle = (kth_big_number_const_t)PyCapsule_GetPointer(py_other, KTH_PY_CAPSULE_VM_BIG_NUMBER);
    if (other_handle == NULL) return NULL;
    auto const result = kth_vm_big_number_add(self_handle, other_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_VM_BIG_NUMBER, kth_py_native_vm_big_number_capsule_dtor);
    if (capsule == NULL) {
        kth_vm_big_number_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_vm_big_number_subtract(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"other", NULL};
    PyObject* py_self = NULL;
    PyObject* py_other = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_other)) {
        return NULL;
    }
    kth_big_number_const_t self_handle = (kth_big_number_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_BIG_NUMBER);
    if (self_handle == NULL) return NULL;
    kth_big_number_const_t other_handle = (kth_big_number_const_t)PyCapsule_GetPointer(py_other, KTH_PY_CAPSULE_VM_BIG_NUMBER);
    if (other_handle == NULL) return NULL;
    auto const result = kth_vm_big_number_subtract(self_handle, other_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_VM_BIG_NUMBER, kth_py_native_vm_big_number_capsule_dtor);
    if (capsule == NULL) {
        kth_vm_big_number_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_vm_big_number_multiply(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"other", NULL};
    PyObject* py_self = NULL;
    PyObject* py_other = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_other)) {
        return NULL;
    }
    kth_big_number_const_t self_handle = (kth_big_number_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_BIG_NUMBER);
    if (self_handle == NULL) return NULL;
    kth_big_number_const_t other_handle = (kth_big_number_const_t)PyCapsule_GetPointer(py_other, KTH_PY_CAPSULE_VM_BIG_NUMBER);
    if (other_handle == NULL) return NULL;
    auto const result = kth_vm_big_number_multiply(self_handle, other_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_VM_BIG_NUMBER, kth_py_native_vm_big_number_capsule_dtor);
    if (capsule == NULL) {
        kth_vm_big_number_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_vm_big_number_abs(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_big_number_const_t self_handle = (kth_big_number_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_BIG_NUMBER);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_big_number_abs(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_VM_BIG_NUMBER, kth_py_native_vm_big_number_capsule_dtor);
    if (capsule == NULL) {
        kth_vm_big_number_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_vm_big_number_negate(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_big_number_mut_t self_handle = (kth_big_number_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_BIG_NUMBER);
    if (self_handle == NULL) return NULL;
    kth_vm_big_number_negate(self_handle);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_vm_big_number_pow(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"exp", NULL};
    PyObject* py_self = NULL;
    PyObject* py_exp = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_exp)) {
        return NULL;
    }
    kth_big_number_const_t self_handle = (kth_big_number_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_BIG_NUMBER);
    if (self_handle == NULL) return NULL;
    kth_big_number_const_t exp_handle = (kth_big_number_const_t)PyCapsule_GetPointer(py_exp, KTH_PY_CAPSULE_VM_BIG_NUMBER);
    if (exp_handle == NULL) return NULL;
    auto const result = kth_vm_big_number_pow(self_handle, exp_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_VM_BIG_NUMBER, kth_py_native_vm_big_number_capsule_dtor);
    if (capsule == NULL) {
        kth_vm_big_number_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_vm_big_number_pow_mod(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"exp", (char*)"mod", NULL};
    PyObject* py_self = NULL;
    PyObject* py_exp = NULL;
    PyObject* py_mod = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OOO", kwlist, &py_self, &py_exp, &py_mod)) {
        return NULL;
    }
    kth_big_number_const_t self_handle = (kth_big_number_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_BIG_NUMBER);
    if (self_handle == NULL) return NULL;
    kth_big_number_const_t exp_handle = (kth_big_number_const_t)PyCapsule_GetPointer(py_exp, KTH_PY_CAPSULE_VM_BIG_NUMBER);
    if (exp_handle == NULL) return NULL;
    kth_big_number_const_t mod_handle = (kth_big_number_const_t)PyCapsule_GetPointer(py_mod, KTH_PY_CAPSULE_VM_BIG_NUMBER);
    if (mod_handle == NULL) return NULL;
    auto const result = kth_vm_big_number_pow_mod(self_handle, exp_handle, mod_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_VM_BIG_NUMBER, kth_py_native_vm_big_number_capsule_dtor);
    if (capsule == NULL) {
        kth_vm_big_number_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_vm_big_number_math_modulo(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"mod", NULL};
    PyObject* py_self = NULL;
    PyObject* py_mod = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_mod)) {
        return NULL;
    }
    kth_big_number_const_t self_handle = (kth_big_number_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_BIG_NUMBER);
    if (self_handle == NULL) return NULL;
    kth_big_number_const_t mod_handle = (kth_big_number_const_t)PyCapsule_GetPointer(py_mod, KTH_PY_CAPSULE_VM_BIG_NUMBER);
    if (mod_handle == NULL) return NULL;
    auto const result = kth_vm_big_number_math_modulo(self_handle, mod_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_VM_BIG_NUMBER, kth_py_native_vm_big_number_capsule_dtor);
    if (capsule == NULL) {
        kth_vm_big_number_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_vm_big_number_data(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_big_number_const_t self_handle = (kth_big_number_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_BIG_NUMBER);
    if (self_handle == NULL) return NULL;
    kth_size_t out_size = 0;
    auto const result = kth_vm_big_number_data(self_handle, &out_size);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: serialization failed");
        return NULL;
    }
    PyObject* py_result = Py_BuildValue("y#", result, (Py_ssize_t)out_size);
    kth_core_destruct_array(result);
    return py_result;
}

PyObject*
kth_py_native_vm_big_number_set_data(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"d", (char*)"max_size", NULL};
    PyObject* py_self = NULL;
    char const* d_buf = NULL;
    Py_ssize_t d_size = 0;
    Py_ssize_t max_size = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Oy#n", kwlist, &py_self, &d_buf, &d_size, &max_size)) {
        return NULL;
    }
    kth_big_number_mut_t self_handle = (kth_big_number_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_BIG_NUMBER);
    if (self_handle == NULL) return NULL;
    if (max_size < 0) {
        PyErr_Format(PyExc_ValueError, "max_size must be non-negative, got %zd", max_size);
        return NULL;
    }
    auto const result = kth_vm_big_number_set_data(self_handle, (uint8_t const*)d_buf, (kth_size_t)d_size, (kth_size_t)max_size);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_vm_big_number_is_true(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_big_number_const_t self_handle = (kth_big_number_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_BIG_NUMBER);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_big_number_is_true(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_vm_big_number_is_false(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_big_number_const_t self_handle = (kth_big_number_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_BIG_NUMBER);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_big_number_is_false(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_vm_big_number_is_minimally_encoded(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"data", (char*)"max_size", NULL};
    char const* data_buf = NULL;
    Py_ssize_t data_size = 0;
    Py_ssize_t max_size = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "y#n", kwlist, &data_buf, &data_size, &max_size)) {
        return NULL;
    }
    if (max_size < 0) {
        PyErr_Format(PyExc_ValueError, "max_size must be non-negative, got %zd", max_size);
        return NULL;
    }
    auto const result = kth_vm_big_number_is_minimally_encoded((uint8_t const*)data_buf, (kth_size_t)data_size, (kth_size_t)max_size);
    return PyBool_FromLong((long)result);
}

PyMethodDef kth_py_native_vm_big_number_methods[] = {
    {"vm_big_number_construct_default", (PyCFunction)kth_py_native_vm_big_number_construct_default, METH_NOARGS, NULL},
    {"vm_big_number_construct_from_value", (PyCFunction)kth_py_native_vm_big_number_construct_from_value, METH_VARARGS | METH_KEYWORDS, NULL},
    {"vm_big_number_construct_from_decimal_str", (PyCFunction)kth_py_native_vm_big_number_construct_from_decimal_str, METH_VARARGS | METH_KEYWORDS, NULL},
    {"vm_big_number_copy", (PyCFunction)kth_py_native_vm_big_number_copy, METH_O, NULL},
    {"vm_big_number_destruct", (PyCFunction)kth_py_native_vm_big_number_destruct, METH_O, NULL},
    {"vm_big_number_from_hex", (PyCFunction)kth_py_native_vm_big_number_from_hex, METH_VARARGS | METH_KEYWORDS, NULL},
    {"vm_big_number_serialize", (PyCFunction)kth_py_native_vm_big_number_serialize, METH_O, NULL},
    {"vm_big_number_deserialize", (PyCFunction)kth_py_native_vm_big_number_deserialize, METH_VARARGS | METH_KEYWORDS, NULL},
    {"vm_big_number_to_string", (PyCFunction)kth_py_native_vm_big_number_to_string, METH_O, NULL},
    {"vm_big_number_to_hex", (PyCFunction)kth_py_native_vm_big_number_to_hex, METH_O, NULL},
    {"vm_big_number_sign", (PyCFunction)kth_py_native_vm_big_number_sign, METH_O, NULL},
    {"vm_big_number_is_zero", (PyCFunction)kth_py_native_vm_big_number_is_zero, METH_O, NULL},
    {"vm_big_number_is_nonzero", (PyCFunction)kth_py_native_vm_big_number_is_nonzero, METH_O, NULL},
    {"vm_big_number_is_negative", (PyCFunction)kth_py_native_vm_big_number_is_negative, METH_O, NULL},
    {"vm_big_number_to_int32_saturating", (PyCFunction)kth_py_native_vm_big_number_to_int32_saturating, METH_O, NULL},
    {"vm_big_number_byte_count", (PyCFunction)kth_py_native_vm_big_number_byte_count, METH_O, NULL},
    {"vm_big_number_compare", (PyCFunction)kth_py_native_vm_big_number_compare, METH_VARARGS | METH_KEYWORDS, NULL},
    {"vm_big_number_equals", (PyCFunction)kth_py_native_vm_big_number_equals, METH_VARARGS | METH_KEYWORDS, NULL},
    {"vm_big_number_add", (PyCFunction)kth_py_native_vm_big_number_add, METH_VARARGS | METH_KEYWORDS, NULL},
    {"vm_big_number_subtract", (PyCFunction)kth_py_native_vm_big_number_subtract, METH_VARARGS | METH_KEYWORDS, NULL},
    {"vm_big_number_multiply", (PyCFunction)kth_py_native_vm_big_number_multiply, METH_VARARGS | METH_KEYWORDS, NULL},
    {"vm_big_number_abs", (PyCFunction)kth_py_native_vm_big_number_abs, METH_O, NULL},
    {"vm_big_number_negate", (PyCFunction)kth_py_native_vm_big_number_negate, METH_O, NULL},
    {"vm_big_number_pow", (PyCFunction)kth_py_native_vm_big_number_pow, METH_VARARGS | METH_KEYWORDS, NULL},
    {"vm_big_number_pow_mod", (PyCFunction)kth_py_native_vm_big_number_pow_mod, METH_VARARGS | METH_KEYWORDS, NULL},
    {"vm_big_number_math_modulo", (PyCFunction)kth_py_native_vm_big_number_math_modulo, METH_VARARGS | METH_KEYWORDS, NULL},
    {"vm_big_number_data", (PyCFunction)kth_py_native_vm_big_number_data, METH_O, NULL},
    {"vm_big_number_set_data", (PyCFunction)kth_py_native_vm_big_number_set_data, METH_VARARGS | METH_KEYWORDS, NULL},
    {"vm_big_number_is_true", (PyCFunction)kth_py_native_vm_big_number_is_true, METH_O, NULL},
    {"vm_big_number_is_false", (PyCFunction)kth_py_native_vm_big_number_is_false, METH_O, NULL},
    {"vm_big_number_is_minimally_encoded", (PyCFunction)kth_py_native_vm_big_number_is_minimally_encoded, METH_VARARGS | METH_KEYWORDS, NULL},
    {NULL, NULL, 0, NULL}  // sentinel
};

#ifdef __cplusplus
} // extern "C"
#endif
