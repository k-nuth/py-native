// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_PY_NATIVE_VM_NUMBER_H_
#define KTH_PY_NATIVE_VM_NUMBER_H_

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#ifdef __cplusplus
extern "C" {
#endif

PyObject* kth_py_native_vm_number_construct_default(PyObject* self, PyObject* args);
PyObject* kth_py_native_vm_number_copy(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_number_destruct(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_number_from_int(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_vm_number_valid(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_vm_number_set_data(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_vm_number_data(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_number_int32(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_number_int64(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_number_is_true(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_number_is_false(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_number_greater(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_vm_number_less(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_vm_number_greater_or_equal(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_vm_number_less_or_equal(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_vm_number_equals(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_vm_number_add_int64(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_vm_number_subtract_int64(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_vm_number_add_number(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_vm_number_subtract_number(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_vm_number_multiply(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_vm_number_safe_add_number(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_vm_number_safe_add_int64(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_vm_number_safe_sub_number(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_vm_number_safe_sub_int64(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_vm_number_safe_mul_number(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_vm_number_safe_mul_int64(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_vm_number_safe_add_number2(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_vm_number_safe_sub_number2(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_vm_number_safe_mul_number2(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_vm_number_is_minimally_encoded(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_vm_number_minimally_encode(PyObject* self, PyObject* args, PyObject* kwds);

extern PyMethodDef kth_py_native_vm_number_methods[];

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_PY_NATIVE_VM_NUMBER_H_
