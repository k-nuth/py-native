// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_PY_NATIVE_CORE_BINARY_H_
#define KTH_PY_NATIVE_CORE_BINARY_H_

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#ifdef __cplusplus
extern "C" {
#endif

PyObject* kth_py_native_core_binary_construct_default(PyObject* self, PyObject* args);
PyObject* kth_py_native_core_binary_construct_from_bit_string(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_core_binary_construct_from_size_number(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_core_binary_construct_from_size_blocks(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_core_binary_copy(PyObject* self, PyObject* arg);
PyObject* kth_py_native_core_binary_destruct(PyObject* self, PyObject* arg);
PyObject* kth_py_native_core_binary_blocks_size(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_core_binary_is_base2(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_core_binary_resize(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_core_binary_at(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_core_binary_blocks(PyObject* self, PyObject* arg);
PyObject* kth_py_native_core_binary_encoded(PyObject* self, PyObject* arg);
PyObject* kth_py_native_core_binary_size(PyObject* self, PyObject* arg);
PyObject* kth_py_native_core_binary_append(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_core_binary_prepend(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_core_binary_shift_left(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_core_binary_shift_right(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_core_binary_substring(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_core_binary_is_prefix_of_span(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_core_binary_is_prefix_of_uint32(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_core_binary_is_prefix_of_binary(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_core_binary_equals(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_core_binary_less(PyObject* self, PyObject* args, PyObject* kwds);

extern PyMethodDef kth_py_native_core_binary_methods[];

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_PY_NATIVE_CORE_BINARY_H_
