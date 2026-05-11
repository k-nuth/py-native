// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/py-native/vm/number.h>

#include <string.h>
#include <kth/capi.h>
#include <kth/capi/vm/number.h>
#include <kth/py-native/capsule_names.h>
#include <kth/py-native/utils.h>

#ifdef __cplusplus
extern "C" {
#endif

// PyCapsule destructor — released by GC when the capsule is
// collected. Explicit `destruct` calls set the capsule name to
// "kth.destroyed", so PyCapsule_IsValid returns false and this
// destructor becomes a no-op (no double-free).
void kth_py_native_vm_number_capsule_dtor(PyObject* capsule) {
    if ( ! PyCapsule_IsValid(capsule, KTH_PY_CAPSULE_VM_NUMBER)) return;
    kth_number_mut_t handle = (kth_number_mut_t)PyCapsule_GetPointer(capsule, KTH_PY_CAPSULE_VM_NUMBER);
    if (handle != NULL) kth_vm_number_destruct(handle);
}

PyObject*
kth_py_native_vm_number_construct_default(PyObject* self, PyObject* Py_UNUSED(args)) {
    auto const result = kth_vm_number_construct_default();
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_VM_NUMBER, kth_py_native_vm_number_capsule_dtor);
    if (capsule == NULL) {
        kth_vm_number_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_vm_number_copy(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_number_const_t self_handle = (kth_number_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_NUMBER);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_number_copy(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_VM_NUMBER, kth_py_native_vm_number_capsule_dtor);
    if (capsule == NULL) {
        kth_vm_number_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_vm_number_destruct(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_number_mut_t self_handle = (kth_number_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_NUMBER);
    if (self_handle == NULL) return NULL;
    kth_vm_number_destruct(self_handle);
    PyCapsule_SetName(py_self, "kth.destroyed");
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_vm_number_from_int(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"value", NULL};
    long long value = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "L", kwlist, &value)) {
        return NULL;
    }
    kth_number_mut_t out = NULL;
    kth_error_code_t result = kth_vm_number_from_int((int64_t)value, &out);
    if (result != kth_ec_success) {
        PyErr_Format(PyExc_RuntimeError, "kth error code %d", (int)result);
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)out, KTH_PY_CAPSULE_VM_NUMBER, kth_py_native_vm_number_capsule_dtor);
    if (capsule == NULL) {
        kth_vm_number_destruct(out);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_vm_number_valid(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"max_size", NULL};
    PyObject* py_self = NULL;
    Py_ssize_t max_size = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "On", kwlist, &py_self, &max_size)) {
        return NULL;
    }
    kth_number_mut_t self_handle = (kth_number_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_NUMBER);
    if (self_handle == NULL) return NULL;
    if (max_size < 0) {
        PyErr_Format(PyExc_ValueError, "max_size must be non-negative, got %zd", max_size);
        return NULL;
    }
    auto const result = kth_vm_number_valid(self_handle, (kth_size_t)max_size);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_vm_number_set_data(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"data", (char*)"max_size", NULL};
    PyObject* py_self = NULL;
    char const* data_buf = NULL;
    Py_ssize_t data_size = 0;
    Py_ssize_t max_size = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Oy#n", kwlist, &py_self, &data_buf, &data_size, &max_size)) {
        return NULL;
    }
    kth_number_mut_t self_handle = (kth_number_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_NUMBER);
    if (self_handle == NULL) return NULL;
    if (max_size < 0) {
        PyErr_Format(PyExc_ValueError, "max_size must be non-negative, got %zd", max_size);
        return NULL;
    }
    auto const result = kth_vm_number_set_data(self_handle, (uint8_t const*)data_buf, (kth_size_t)data_size, (kth_size_t)max_size);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_vm_number_data(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_number_const_t self_handle = (kth_number_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_NUMBER);
    if (self_handle == NULL) return NULL;
    kth_size_t out_size = 0;
    auto const result = kth_vm_number_data(self_handle, &out_size);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: serialization failed");
        return NULL;
    }
    PyObject* py_result = Py_BuildValue("y#", result, (Py_ssize_t)out_size);
    kth_core_destruct_array(result);
    return py_result;
}

PyObject*
kth_py_native_vm_number_int32(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_number_const_t self_handle = (kth_number_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_NUMBER);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_number_int32(self_handle);
    return PyLong_FromLongLong((long long)result);
}

PyObject*
kth_py_native_vm_number_int64(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_number_const_t self_handle = (kth_number_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_NUMBER);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_number_int64(self_handle);
    return PyLong_FromLongLong((long long)result);
}

PyObject*
kth_py_native_vm_number_is_true(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_number_const_t self_handle = (kth_number_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_NUMBER);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_number_is_true(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_vm_number_is_false(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_number_const_t self_handle = (kth_number_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_NUMBER);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_number_is_false(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_vm_number_greater(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    long long value = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OL", kwlist, &py_self, &value)) {
        return NULL;
    }
    kth_number_const_t self_handle = (kth_number_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_NUMBER);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_number_greater(self_handle, (int64_t)value);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_vm_number_less(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    long long value = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OL", kwlist, &py_self, &value)) {
        return NULL;
    }
    kth_number_const_t self_handle = (kth_number_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_NUMBER);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_number_less(self_handle, (int64_t)value);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_vm_number_greater_or_equal(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    long long value = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OL", kwlist, &py_self, &value)) {
        return NULL;
    }
    kth_number_const_t self_handle = (kth_number_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_NUMBER);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_number_greater_or_equal(self_handle, (int64_t)value);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_vm_number_less_or_equal(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    long long value = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OL", kwlist, &py_self, &value)) {
        return NULL;
    }
    kth_number_const_t self_handle = (kth_number_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_NUMBER);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_number_less_or_equal(self_handle, (int64_t)value);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_vm_number_equals(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"other", NULL};
    PyObject* py_self = NULL;
    PyObject* py_other = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_other)) {
        return NULL;
    }
    kth_number_const_t self_handle = (kth_number_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_NUMBER);
    if (self_handle == NULL) return NULL;
    kth_number_const_t other_handle = (kth_number_const_t)PyCapsule_GetPointer(py_other, KTH_PY_CAPSULE_VM_NUMBER);
    if (other_handle == NULL) return NULL;
    auto const result = kth_vm_number_equals(self_handle, other_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_vm_number_add_int64(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    long long value = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OL", kwlist, &py_self, &value)) {
        return NULL;
    }
    kth_number_const_t self_handle = (kth_number_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_NUMBER);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_number_add_int64(self_handle, (int64_t)value);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_VM_NUMBER, kth_py_native_vm_number_capsule_dtor);
    if (capsule == NULL) {
        kth_vm_number_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_vm_number_subtract_int64(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    long long value = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OL", kwlist, &py_self, &value)) {
        return NULL;
    }
    kth_number_const_t self_handle = (kth_number_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_NUMBER);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_number_subtract_int64(self_handle, (int64_t)value);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_VM_NUMBER, kth_py_native_vm_number_capsule_dtor);
    if (capsule == NULL) {
        kth_vm_number_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_vm_number_add_number(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"x", NULL};
    PyObject* py_self = NULL;
    PyObject* py_x = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_x)) {
        return NULL;
    }
    kth_number_const_t self_handle = (kth_number_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_NUMBER);
    if (self_handle == NULL) return NULL;
    kth_number_const_t x_handle = (kth_number_const_t)PyCapsule_GetPointer(py_x, KTH_PY_CAPSULE_VM_NUMBER);
    if (x_handle == NULL) return NULL;
    auto const result = kth_vm_number_add_number(self_handle, x_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_VM_NUMBER, kth_py_native_vm_number_capsule_dtor);
    if (capsule == NULL) {
        kth_vm_number_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_vm_number_subtract_number(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"x", NULL};
    PyObject* py_self = NULL;
    PyObject* py_x = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_x)) {
        return NULL;
    }
    kth_number_const_t self_handle = (kth_number_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_NUMBER);
    if (self_handle == NULL) return NULL;
    kth_number_const_t x_handle = (kth_number_const_t)PyCapsule_GetPointer(py_x, KTH_PY_CAPSULE_VM_NUMBER);
    if (x_handle == NULL) return NULL;
    auto const result = kth_vm_number_subtract_number(self_handle, x_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_VM_NUMBER, kth_py_native_vm_number_capsule_dtor);
    if (capsule == NULL) {
        kth_vm_number_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_vm_number_multiply(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"x", NULL};
    PyObject* py_self = NULL;
    PyObject* py_x = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_x)) {
        return NULL;
    }
    kth_number_const_t self_handle = (kth_number_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_NUMBER);
    if (self_handle == NULL) return NULL;
    kth_number_const_t x_handle = (kth_number_const_t)PyCapsule_GetPointer(py_x, KTH_PY_CAPSULE_VM_NUMBER);
    if (x_handle == NULL) return NULL;
    auto const result = kth_vm_number_multiply(self_handle, x_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_VM_NUMBER, kth_py_native_vm_number_capsule_dtor);
    if (capsule == NULL) {
        kth_vm_number_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_vm_number_safe_add_number(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"x", NULL};
    PyObject* py_self = NULL;
    PyObject* py_x = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_x)) {
        return NULL;
    }
    kth_number_mut_t self_handle = (kth_number_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_NUMBER);
    if (self_handle == NULL) return NULL;
    kth_number_const_t x_handle = (kth_number_const_t)PyCapsule_GetPointer(py_x, KTH_PY_CAPSULE_VM_NUMBER);
    if (x_handle == NULL) return NULL;
    auto const result = kth_vm_number_safe_add_number(self_handle, x_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_vm_number_safe_add_int64(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"x", NULL};
    PyObject* py_self = NULL;
    long long x = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OL", kwlist, &py_self, &x)) {
        return NULL;
    }
    kth_number_mut_t self_handle = (kth_number_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_NUMBER);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_number_safe_add_int64(self_handle, (int64_t)x);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_vm_number_safe_sub_number(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"x", NULL};
    PyObject* py_self = NULL;
    PyObject* py_x = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_x)) {
        return NULL;
    }
    kth_number_mut_t self_handle = (kth_number_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_NUMBER);
    if (self_handle == NULL) return NULL;
    kth_number_const_t x_handle = (kth_number_const_t)PyCapsule_GetPointer(py_x, KTH_PY_CAPSULE_VM_NUMBER);
    if (x_handle == NULL) return NULL;
    auto const result = kth_vm_number_safe_sub_number(self_handle, x_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_vm_number_safe_sub_int64(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"x", NULL};
    PyObject* py_self = NULL;
    long long x = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OL", kwlist, &py_self, &x)) {
        return NULL;
    }
    kth_number_mut_t self_handle = (kth_number_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_NUMBER);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_number_safe_sub_int64(self_handle, (int64_t)x);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_vm_number_safe_mul_number(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"x", NULL};
    PyObject* py_self = NULL;
    PyObject* py_x = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_x)) {
        return NULL;
    }
    kth_number_mut_t self_handle = (kth_number_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_NUMBER);
    if (self_handle == NULL) return NULL;
    kth_number_const_t x_handle = (kth_number_const_t)PyCapsule_GetPointer(py_x, KTH_PY_CAPSULE_VM_NUMBER);
    if (x_handle == NULL) return NULL;
    auto const result = kth_vm_number_safe_mul_number(self_handle, x_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_vm_number_safe_mul_int64(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"x", NULL};
    PyObject* py_self = NULL;
    long long x = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OL", kwlist, &py_self, &x)) {
        return NULL;
    }
    kth_number_mut_t self_handle = (kth_number_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_NUMBER);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_number_safe_mul_int64(self_handle, (int64_t)x);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_vm_number_safe_add_number2(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"x", (char*)"y", NULL};
    PyObject* py_x = NULL;
    PyObject* py_y = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_x, &py_y)) {
        return NULL;
    }
    kth_number_const_t x_handle = (kth_number_const_t)PyCapsule_GetPointer(py_x, KTH_PY_CAPSULE_VM_NUMBER);
    if (x_handle == NULL) return NULL;
    kth_number_const_t y_handle = (kth_number_const_t)PyCapsule_GetPointer(py_y, KTH_PY_CAPSULE_VM_NUMBER);
    if (y_handle == NULL) return NULL;
    kth_number_mut_t out = NULL;
    kth_error_code_t result = kth_vm_number_safe_add_number2(x_handle, y_handle, &out);
    if (result != kth_ec_success) {
        PyErr_Format(PyExc_RuntimeError, "kth error code %d", (int)result);
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)out, KTH_PY_CAPSULE_VM_NUMBER, kth_py_native_vm_number_capsule_dtor);
    if (capsule == NULL) {
        kth_vm_number_destruct(out);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_vm_number_safe_sub_number2(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"x", (char*)"y", NULL};
    PyObject* py_x = NULL;
    PyObject* py_y = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_x, &py_y)) {
        return NULL;
    }
    kth_number_const_t x_handle = (kth_number_const_t)PyCapsule_GetPointer(py_x, KTH_PY_CAPSULE_VM_NUMBER);
    if (x_handle == NULL) return NULL;
    kth_number_const_t y_handle = (kth_number_const_t)PyCapsule_GetPointer(py_y, KTH_PY_CAPSULE_VM_NUMBER);
    if (y_handle == NULL) return NULL;
    kth_number_mut_t out = NULL;
    kth_error_code_t result = kth_vm_number_safe_sub_number2(x_handle, y_handle, &out);
    if (result != kth_ec_success) {
        PyErr_Format(PyExc_RuntimeError, "kth error code %d", (int)result);
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)out, KTH_PY_CAPSULE_VM_NUMBER, kth_py_native_vm_number_capsule_dtor);
    if (capsule == NULL) {
        kth_vm_number_destruct(out);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_vm_number_safe_mul_number2(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"x", (char*)"y", NULL};
    PyObject* py_x = NULL;
    PyObject* py_y = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_x, &py_y)) {
        return NULL;
    }
    kth_number_const_t x_handle = (kth_number_const_t)PyCapsule_GetPointer(py_x, KTH_PY_CAPSULE_VM_NUMBER);
    if (x_handle == NULL) return NULL;
    kth_number_const_t y_handle = (kth_number_const_t)PyCapsule_GetPointer(py_y, KTH_PY_CAPSULE_VM_NUMBER);
    if (y_handle == NULL) return NULL;
    kth_number_mut_t out = NULL;
    kth_error_code_t result = kth_vm_number_safe_mul_number2(x_handle, y_handle, &out);
    if (result != kth_ec_success) {
        PyErr_Format(PyExc_RuntimeError, "kth error code %d", (int)result);
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)out, KTH_PY_CAPSULE_VM_NUMBER, kth_py_native_vm_number_capsule_dtor);
    if (capsule == NULL) {
        kth_vm_number_destruct(out);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_vm_number_is_minimally_encoded(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"data", (char*)"max_integer_size", NULL};
    char const* data_buf = NULL;
    Py_ssize_t data_size = 0;
    Py_ssize_t max_integer_size = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "y#n", kwlist, &data_buf, &data_size, &max_integer_size)) {
        return NULL;
    }
    if (max_integer_size < 0) {
        PyErr_Format(PyExc_ValueError, "max_integer_size must be non-negative, got %zd", max_integer_size);
        return NULL;
    }
    auto const result = kth_vm_number_is_minimally_encoded((uint8_t const*)data_buf, (kth_size_t)data_size, (kth_size_t)max_integer_size);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_vm_number_minimally_encode(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"data", NULL};
    char const* data_buf = NULL;
    Py_ssize_t data_size = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "y#", kwlist, &data_buf, &data_size)) {
        return NULL;
    }
    auto const result = kth_vm_number_minimally_encode((uint8_t const*)data_buf, (kth_size_t)data_size);
    return PyBool_FromLong((long)result);
}

PyMethodDef kth_py_native_vm_number_methods[] = {
    {"vm_number_construct_default", (PyCFunction)kth_py_native_vm_number_construct_default, METH_NOARGS, NULL},
    {"vm_number_copy", (PyCFunction)kth_py_native_vm_number_copy, METH_O, NULL},
    {"vm_number_destruct", (PyCFunction)kth_py_native_vm_number_destruct, METH_O, NULL},
    {"vm_number_from_int", (PyCFunction)kth_py_native_vm_number_from_int, METH_VARARGS | METH_KEYWORDS, NULL},
    {"vm_number_valid", (PyCFunction)kth_py_native_vm_number_valid, METH_VARARGS | METH_KEYWORDS, NULL},
    {"vm_number_set_data", (PyCFunction)kth_py_native_vm_number_set_data, METH_VARARGS | METH_KEYWORDS, NULL},
    {"vm_number_data", (PyCFunction)kth_py_native_vm_number_data, METH_O, NULL},
    {"vm_number_int32", (PyCFunction)kth_py_native_vm_number_int32, METH_O, NULL},
    {"vm_number_int64", (PyCFunction)kth_py_native_vm_number_int64, METH_O, NULL},
    {"vm_number_is_true", (PyCFunction)kth_py_native_vm_number_is_true, METH_O, NULL},
    {"vm_number_is_false", (PyCFunction)kth_py_native_vm_number_is_false, METH_O, NULL},
    {"vm_number_greater", (PyCFunction)kth_py_native_vm_number_greater, METH_VARARGS | METH_KEYWORDS, NULL},
    {"vm_number_less", (PyCFunction)kth_py_native_vm_number_less, METH_VARARGS | METH_KEYWORDS, NULL},
    {"vm_number_greater_or_equal", (PyCFunction)kth_py_native_vm_number_greater_or_equal, METH_VARARGS | METH_KEYWORDS, NULL},
    {"vm_number_less_or_equal", (PyCFunction)kth_py_native_vm_number_less_or_equal, METH_VARARGS | METH_KEYWORDS, NULL},
    {"vm_number_equals", (PyCFunction)kth_py_native_vm_number_equals, METH_VARARGS | METH_KEYWORDS, NULL},
    {"vm_number_add_int64", (PyCFunction)kth_py_native_vm_number_add_int64, METH_VARARGS | METH_KEYWORDS, NULL},
    {"vm_number_subtract_int64", (PyCFunction)kth_py_native_vm_number_subtract_int64, METH_VARARGS | METH_KEYWORDS, NULL},
    {"vm_number_add_number", (PyCFunction)kth_py_native_vm_number_add_number, METH_VARARGS | METH_KEYWORDS, NULL},
    {"vm_number_subtract_number", (PyCFunction)kth_py_native_vm_number_subtract_number, METH_VARARGS | METH_KEYWORDS, NULL},
    {"vm_number_multiply", (PyCFunction)kth_py_native_vm_number_multiply, METH_VARARGS | METH_KEYWORDS, NULL},
    {"vm_number_safe_add_number", (PyCFunction)kth_py_native_vm_number_safe_add_number, METH_VARARGS | METH_KEYWORDS, NULL},
    {"vm_number_safe_add_int64", (PyCFunction)kth_py_native_vm_number_safe_add_int64, METH_VARARGS | METH_KEYWORDS, NULL},
    {"vm_number_safe_sub_number", (PyCFunction)kth_py_native_vm_number_safe_sub_number, METH_VARARGS | METH_KEYWORDS, NULL},
    {"vm_number_safe_sub_int64", (PyCFunction)kth_py_native_vm_number_safe_sub_int64, METH_VARARGS | METH_KEYWORDS, NULL},
    {"vm_number_safe_mul_number", (PyCFunction)kth_py_native_vm_number_safe_mul_number, METH_VARARGS | METH_KEYWORDS, NULL},
    {"vm_number_safe_mul_int64", (PyCFunction)kth_py_native_vm_number_safe_mul_int64, METH_VARARGS | METH_KEYWORDS, NULL},
    {"vm_number_safe_add_number2", (PyCFunction)kth_py_native_vm_number_safe_add_number2, METH_VARARGS | METH_KEYWORDS, NULL},
    {"vm_number_safe_sub_number2", (PyCFunction)kth_py_native_vm_number_safe_sub_number2, METH_VARARGS | METH_KEYWORDS, NULL},
    {"vm_number_safe_mul_number2", (PyCFunction)kth_py_native_vm_number_safe_mul_number2, METH_VARARGS | METH_KEYWORDS, NULL},
    {"vm_number_is_minimally_encoded", (PyCFunction)kth_py_native_vm_number_is_minimally_encoded, METH_VARARGS | METH_KEYWORDS, NULL},
    {"vm_number_minimally_encode", (PyCFunction)kth_py_native_vm_number_minimally_encode, METH_VARARGS | METH_KEYWORDS, NULL},
    {NULL, NULL, 0, NULL}  // sentinel
};

#ifdef __cplusplus
} // extern "C"
#endif
