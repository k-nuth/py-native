// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/py-native/binary.h>

#include <string.h>
#include <kth/capi.h>
#include <kth/capi/binary.h>
#include <kth/py-native/capsule_names.h>
#include <kth/py-native/utils.h>

#ifdef __cplusplus
extern "C" {
#endif

// PyCapsule destructor — released by GC when the capsule is
// collected. Explicit `destruct` calls set the capsule name to
// "kth.destroyed", so PyCapsule_IsValid returns false and this
// destructor becomes a no-op (no double-free).
void kth_py_native_core_binary_capsule_dtor(PyObject* capsule) {
    if ( ! PyCapsule_IsValid(capsule, KTH_PY_CAPSULE_CORE_BINARY)) return;
    kth_binary_mut_t handle = (kth_binary_mut_t)PyCapsule_GetPointer(capsule, KTH_PY_CAPSULE_CORE_BINARY);
    if (handle != NULL) kth_core_binary_destruct(handle);
}

PyObject*
kth_py_native_core_binary_construct_default(PyObject* self, PyObject* Py_UNUSED(args)) {
    auto const result = kth_core_binary_construct_default();
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CORE_BINARY, kth_py_native_core_binary_capsule_dtor);
    if (capsule == NULL) {
        kth_core_binary_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_core_binary_construct_from_bit_string(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"bit_string", NULL};
    char const* bit_string = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "s", kwlist, &bit_string)) {
        return NULL;
    }
    auto const result = kth_core_binary_construct_from_bit_string(bit_string);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CORE_BINARY, kth_py_native_core_binary_capsule_dtor);
    if (capsule == NULL) {
        kth_core_binary_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_core_binary_construct_from_size_number(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"size", (char*)"number", NULL};
    Py_ssize_t size = 0;
    unsigned int number = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "nI", kwlist, &size, &number)) {
        return NULL;
    }
    if (size < 0) {
        PyErr_Format(PyExc_ValueError, "size must be non-negative, got %zd", size);
        return NULL;
    }
    auto const result = kth_core_binary_construct_from_size_number((kth_size_t)size, (uint32_t)number);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CORE_BINARY, kth_py_native_core_binary_capsule_dtor);
    if (capsule == NULL) {
        kth_core_binary_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_core_binary_construct_from_size_blocks(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"size", (char*)"blocks", NULL};
    Py_ssize_t size = 0;
    char const* blocks_buf = NULL;
    Py_ssize_t blocks_size = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "ny#", kwlist, &size, &blocks_buf, &blocks_size)) {
        return NULL;
    }
    if (size < 0) {
        PyErr_Format(PyExc_ValueError, "size must be non-negative, got %zd", size);
        return NULL;
    }
    auto const result = kth_core_binary_construct_from_size_blocks((kth_size_t)size, (uint8_t const*)blocks_buf, (kth_size_t)blocks_size);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CORE_BINARY, kth_py_native_core_binary_capsule_dtor);
    if (capsule == NULL) {
        kth_core_binary_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_core_binary_copy(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_binary_const_t self_handle = (kth_binary_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CORE_BINARY);
    if (self_handle == NULL) return NULL;
    auto const result = kth_core_binary_copy(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CORE_BINARY, kth_py_native_core_binary_capsule_dtor);
    if (capsule == NULL) {
        kth_core_binary_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_core_binary_destruct(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_binary_mut_t self_handle = (kth_binary_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CORE_BINARY);
    if (self_handle == NULL) return NULL;
    kth_core_binary_destruct(self_handle);
    PyCapsule_SetName(py_self, "kth.destroyed");
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_core_binary_blocks_size(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"bit_size", NULL};
    Py_ssize_t bit_size = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "n", kwlist, &bit_size)) {
        return NULL;
    }
    if (bit_size < 0) {
        PyErr_Format(PyExc_ValueError, "bit_size must be non-negative, got %zd", bit_size);
        return NULL;
    }
    auto const result = kth_core_binary_blocks_size((kth_size_t)bit_size);
    return PyLong_FromSize_t((size_t)result);
}

PyObject*
kth_py_native_core_binary_is_base2(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"text", NULL};
    char const* text = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "s", kwlist, &text)) {
        return NULL;
    }
    auto const result = kth_core_binary_is_base2(text);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_core_binary_resize(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"size", NULL};
    PyObject* py_self = NULL;
    Py_ssize_t size = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "On", kwlist, &py_self, &size)) {
        return NULL;
    }
    kth_binary_mut_t self_handle = (kth_binary_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CORE_BINARY);
    if (self_handle == NULL) return NULL;
    if (size < 0) {
        PyErr_Format(PyExc_ValueError, "size must be non-negative, got %zd", size);
        return NULL;
    }
    kth_core_binary_resize(self_handle, (kth_size_t)size);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_core_binary_at(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"index", NULL};
    PyObject* py_self = NULL;
    Py_ssize_t index = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "On", kwlist, &py_self, &index)) {
        return NULL;
    }
    kth_binary_const_t self_handle = (kth_binary_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CORE_BINARY);
    if (self_handle == NULL) return NULL;
    if (index < 0) {
        PyErr_Format(PyExc_ValueError, "index must be non-negative, got %zd", index);
        return NULL;
    }
    auto const result = kth_core_binary_at(self_handle, (kth_size_t)index);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_core_binary_blocks(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_binary_const_t self_handle = (kth_binary_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CORE_BINARY);
    if (self_handle == NULL) return NULL;
    kth_size_t out_size = 0;
    auto const result = kth_core_binary_blocks(self_handle, &out_size);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: serialization failed");
        return NULL;
    }
    PyObject* py_result = Py_BuildValue("y#", result, (Py_ssize_t)out_size);
    kth_core_destruct_array(result);
    return py_result;
}

PyObject*
kth_py_native_core_binary_encoded(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_binary_const_t self_handle = (kth_binary_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CORE_BINARY);
    if (self_handle == NULL) return NULL;
    auto const result = kth_core_binary_encoded(self_handle);
    if (result == NULL) Py_RETURN_NONE;
    PyObject* py_result = Py_BuildValue("s", result);
    kth_core_destruct_string(result);
    return py_result;
}

PyObject*
kth_py_native_core_binary_size(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_binary_const_t self_handle = (kth_binary_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CORE_BINARY);
    if (self_handle == NULL) return NULL;
    auto const result = kth_core_binary_size(self_handle);
    return PyLong_FromSize_t((size_t)result);
}

PyObject*
kth_py_native_core_binary_append(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"post", NULL};
    PyObject* py_self = NULL;
    PyObject* py_post = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_post)) {
        return NULL;
    }
    kth_binary_mut_t self_handle = (kth_binary_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CORE_BINARY);
    if (self_handle == NULL) return NULL;
    kth_binary_const_t post_handle = (kth_binary_const_t)PyCapsule_GetPointer(py_post, KTH_PY_CAPSULE_CORE_BINARY);
    if (post_handle == NULL) return NULL;
    kth_core_binary_append(self_handle, post_handle);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_core_binary_prepend(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"prior", NULL};
    PyObject* py_self = NULL;
    PyObject* py_prior = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_prior)) {
        return NULL;
    }
    kth_binary_mut_t self_handle = (kth_binary_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CORE_BINARY);
    if (self_handle == NULL) return NULL;
    kth_binary_const_t prior_handle = (kth_binary_const_t)PyCapsule_GetPointer(py_prior, KTH_PY_CAPSULE_CORE_BINARY);
    if (prior_handle == NULL) return NULL;
    kth_core_binary_prepend(self_handle, prior_handle);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_core_binary_shift_left(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"distance", NULL};
    PyObject* py_self = NULL;
    Py_ssize_t distance = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "On", kwlist, &py_self, &distance)) {
        return NULL;
    }
    kth_binary_mut_t self_handle = (kth_binary_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CORE_BINARY);
    if (self_handle == NULL) return NULL;
    if (distance < 0) {
        PyErr_Format(PyExc_ValueError, "distance must be non-negative, got %zd", distance);
        return NULL;
    }
    kth_core_binary_shift_left(self_handle, (kth_size_t)distance);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_core_binary_shift_right(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"distance", NULL};
    PyObject* py_self = NULL;
    Py_ssize_t distance = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "On", kwlist, &py_self, &distance)) {
        return NULL;
    }
    kth_binary_mut_t self_handle = (kth_binary_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CORE_BINARY);
    if (self_handle == NULL) return NULL;
    if (distance < 0) {
        PyErr_Format(PyExc_ValueError, "distance must be non-negative, got %zd", distance);
        return NULL;
    }
    kth_core_binary_shift_right(self_handle, (kth_size_t)distance);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_core_binary_substring(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"start", (char*)"length", NULL};
    PyObject* py_self = NULL;
    Py_ssize_t start = 0;
    Py_ssize_t length = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Onn", kwlist, &py_self, &start, &length)) {
        return NULL;
    }
    kth_binary_const_t self_handle = (kth_binary_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CORE_BINARY);
    if (self_handle == NULL) return NULL;
    if (start < 0) {
        PyErr_Format(PyExc_ValueError, "start must be non-negative, got %zd", start);
        return NULL;
    }
    if (length < 0) {
        PyErr_Format(PyExc_ValueError, "length must be non-negative, got %zd", length);
        return NULL;
    }
    auto const result = kth_core_binary_substring(self_handle, (kth_size_t)start, (kth_size_t)length);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CORE_BINARY, kth_py_native_core_binary_capsule_dtor);
    if (capsule == NULL) {
        kth_core_binary_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_core_binary_is_prefix_of_span(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"field", NULL};
    PyObject* py_self = NULL;
    char const* field_buf = NULL;
    Py_ssize_t field_size = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Oy#", kwlist, &py_self, &field_buf, &field_size)) {
        return NULL;
    }
    kth_binary_const_t self_handle = (kth_binary_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CORE_BINARY);
    if (self_handle == NULL) return NULL;
    auto const result = kth_core_binary_is_prefix_of_span(self_handle, (uint8_t const*)field_buf, (kth_size_t)field_size);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_core_binary_is_prefix_of_uint32(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"field", NULL};
    PyObject* py_self = NULL;
    unsigned int field = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OI", kwlist, &py_self, &field)) {
        return NULL;
    }
    kth_binary_const_t self_handle = (kth_binary_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CORE_BINARY);
    if (self_handle == NULL) return NULL;
    auto const result = kth_core_binary_is_prefix_of_uint32(self_handle, (uint32_t)field);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_core_binary_is_prefix_of_binary(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"field", NULL};
    PyObject* py_self = NULL;
    PyObject* py_field = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_field)) {
        return NULL;
    }
    kth_binary_const_t self_handle = (kth_binary_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CORE_BINARY);
    if (self_handle == NULL) return NULL;
    kth_binary_const_t field_handle = (kth_binary_const_t)PyCapsule_GetPointer(py_field, KTH_PY_CAPSULE_CORE_BINARY);
    if (field_handle == NULL) return NULL;
    auto const result = kth_core_binary_is_prefix_of_binary(self_handle, field_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_core_binary_equals(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"other", NULL};
    PyObject* py_self = NULL;
    PyObject* py_other = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_other)) {
        return NULL;
    }
    kth_binary_const_t self_handle = (kth_binary_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CORE_BINARY);
    if (self_handle == NULL) return NULL;
    kth_binary_const_t other_handle = (kth_binary_const_t)PyCapsule_GetPointer(py_other, KTH_PY_CAPSULE_CORE_BINARY);
    if (other_handle == NULL) return NULL;
    auto const result = kth_core_binary_equals(self_handle, other_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_core_binary_less(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"x", NULL};
    PyObject* py_self = NULL;
    PyObject* py_x = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_x)) {
        return NULL;
    }
    kth_binary_const_t self_handle = (kth_binary_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CORE_BINARY);
    if (self_handle == NULL) return NULL;
    kth_binary_const_t x_handle = (kth_binary_const_t)PyCapsule_GetPointer(py_x, KTH_PY_CAPSULE_CORE_BINARY);
    if (x_handle == NULL) return NULL;
    auto const result = kth_core_binary_less(self_handle, x_handle);
    return PyBool_FromLong((long)result);
}

PyMethodDef kth_py_native_core_binary_methods[] = {
    {"core_binary_construct_default", (PyCFunction)kth_py_native_core_binary_construct_default, METH_NOARGS, NULL},
    {"core_binary_construct_from_bit_string", (PyCFunction)kth_py_native_core_binary_construct_from_bit_string, METH_VARARGS | METH_KEYWORDS, NULL},
    {"core_binary_construct_from_size_number", (PyCFunction)kth_py_native_core_binary_construct_from_size_number, METH_VARARGS | METH_KEYWORDS, NULL},
    {"core_binary_construct_from_size_blocks", (PyCFunction)kth_py_native_core_binary_construct_from_size_blocks, METH_VARARGS | METH_KEYWORDS, NULL},
    {"core_binary_copy", (PyCFunction)kth_py_native_core_binary_copy, METH_O, NULL},
    {"core_binary_destruct", (PyCFunction)kth_py_native_core_binary_destruct, METH_O, NULL},
    {"core_binary_blocks_size", (PyCFunction)kth_py_native_core_binary_blocks_size, METH_VARARGS | METH_KEYWORDS, NULL},
    {"core_binary_is_base2", (PyCFunction)kth_py_native_core_binary_is_base2, METH_VARARGS | METH_KEYWORDS, NULL},
    {"core_binary_resize", (PyCFunction)kth_py_native_core_binary_resize, METH_VARARGS | METH_KEYWORDS, NULL},
    {"core_binary_at", (PyCFunction)kth_py_native_core_binary_at, METH_VARARGS | METH_KEYWORDS, NULL},
    {"core_binary_blocks", (PyCFunction)kth_py_native_core_binary_blocks, METH_O, NULL},
    {"core_binary_encoded", (PyCFunction)kth_py_native_core_binary_encoded, METH_O, NULL},
    {"core_binary_size", (PyCFunction)kth_py_native_core_binary_size, METH_O, NULL},
    {"core_binary_append", (PyCFunction)kth_py_native_core_binary_append, METH_VARARGS | METH_KEYWORDS, NULL},
    {"core_binary_prepend", (PyCFunction)kth_py_native_core_binary_prepend, METH_VARARGS | METH_KEYWORDS, NULL},
    {"core_binary_shift_left", (PyCFunction)kth_py_native_core_binary_shift_left, METH_VARARGS | METH_KEYWORDS, NULL},
    {"core_binary_shift_right", (PyCFunction)kth_py_native_core_binary_shift_right, METH_VARARGS | METH_KEYWORDS, NULL},
    {"core_binary_substring", (PyCFunction)kth_py_native_core_binary_substring, METH_VARARGS | METH_KEYWORDS, NULL},
    {"core_binary_is_prefix_of_span", (PyCFunction)kth_py_native_core_binary_is_prefix_of_span, METH_VARARGS | METH_KEYWORDS, NULL},
    {"core_binary_is_prefix_of_uint32", (PyCFunction)kth_py_native_core_binary_is_prefix_of_uint32, METH_VARARGS | METH_KEYWORDS, NULL},
    {"core_binary_is_prefix_of_binary", (PyCFunction)kth_py_native_core_binary_is_prefix_of_binary, METH_VARARGS | METH_KEYWORDS, NULL},
    {"core_binary_equals", (PyCFunction)kth_py_native_core_binary_equals, METH_VARARGS | METH_KEYWORDS, NULL},
    {"core_binary_less", (PyCFunction)kth_py_native_core_binary_less, METH_VARARGS | METH_KEYWORDS, NULL},
    {NULL, NULL, 0, NULL}  // sentinel
};

#ifdef __cplusplus
} // extern "C"
#endif
