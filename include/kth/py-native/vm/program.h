// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_PY_NATIVE_VM_PROGRAM_H_
#define KTH_PY_NATIVE_VM_PROGRAM_H_

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#ifdef __cplusplus
extern "C" {
#endif

PyObject* kth_py_native_vm_program_construct_default(PyObject* self, PyObject* args);
PyObject* kth_py_native_vm_program_construct_from_script(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_program_construct_from_script_transaction_input_index_flags_value(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_vm_program_construct_from_script_transaction_input_index_flags_stack_value(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_vm_program_construct_from_script_program(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_vm_program_construct_from_script_program_move(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_vm_program_copy(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_program_destruct(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_program_get_metrics(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_program_is_valid(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_program_flags(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_program_max_script_element_size(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_program_max_integer_size_legacy(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_program_max_integer_size(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_program_is_chip_vm_limits_enabled(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_program_is_bigint_enabled(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_program_input_index(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_program_value(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_program_transaction(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_program_get_script(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_program_reset_active_script(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_program_operation_count(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_program_evaluate_simple(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_program_evaluate(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_vm_program_increment_operation_count_operation(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_vm_program_increment_operation_count_int32(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_vm_program_mark_code_separator(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_vm_program_push(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_vm_program_push_move(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_vm_program_push_copy(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_vm_program_drop(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_program_pop(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_program_duplicate(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_vm_program_swap(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_vm_program_empty(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_program_stack_true(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_vm_program_stack_result(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_vm_program_is_stack_overflow_simple(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_program_is_stack_overflow(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_vm_program_if_(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_vm_program_item(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_vm_program_top(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_program_subscript(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_program_size(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_program_conditional_stack_size(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_program_empty_alternate(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_program_push_alternate(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_vm_program_pop_alternate(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_program_open(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_vm_program_negate(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_program_close(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_program_closed(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_program_succeeded(PyObject* self, PyObject* arg);

extern PyMethodDef kth_py_native_vm_program_methods[];

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_PY_NATIVE_VM_PROGRAM_H_
