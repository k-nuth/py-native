// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_PY_NATIVE_VM_BIG_NUMBER_H_
#define KTH_PY_NATIVE_VM_BIG_NUMBER_H_

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#ifdef __cplusplus
extern "C" {
#endif

PyObject* kth_py_native_vm_big_number_construct_default(PyObject* self, PyObject* args);
PyObject* kth_py_native_vm_big_number_construct_from_value(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_vm_big_number_construct_from_decimal_str(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_vm_big_number_copy(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_big_number_destruct(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_big_number_from_hex(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_vm_big_number_serialize(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_big_number_deserialize(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_vm_big_number_to_string(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_big_number_to_hex(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_big_number_sign(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_big_number_is_zero(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_big_number_is_nonzero(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_big_number_is_negative(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_big_number_to_int32_saturating(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_big_number_byte_count(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_big_number_compare(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_vm_big_number_equals(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_vm_big_number_add(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_vm_big_number_subtract(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_vm_big_number_multiply(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_vm_big_number_abs(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_big_number_negate(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_big_number_pow(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_vm_big_number_pow_mod(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_vm_big_number_math_modulo(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_vm_big_number_data(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_big_number_set_data(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_vm_big_number_is_true(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_big_number_is_false(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_big_number_is_minimally_encoded(PyObject* self, PyObject* args, PyObject* kwds);

extern PyMethodDef kth_py_native_vm_big_number_methods[];

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_PY_NATIVE_VM_BIG_NUMBER_H_
