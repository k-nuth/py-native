// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/py-native/vm/program.h>

#include <string.h>
#include <kth/capi.h>
#include <kth/capi/vm/program.h>
#include <kth/py-native/capsule_names.h>
#include <kth/py-native/utils.h>

#ifdef __cplusplus
extern "C" {
#endif

// PyCapsule destructor — released by GC when the capsule is
// collected. Explicit `destruct` calls set the capsule name to
// "kth.destroyed", so PyCapsule_IsValid returns false and this
// destructor becomes a no-op (no double-free).
void kth_py_native_vm_program_capsule_dtor(PyObject* capsule) {
    if ( ! PyCapsule_IsValid(capsule, KTH_PY_CAPSULE_VM_PROGRAM)) return;
    kth_program_mut_t handle = (kth_program_mut_t)PyCapsule_GetPointer(capsule, KTH_PY_CAPSULE_VM_PROGRAM);
    if (handle != NULL) kth_vm_program_destruct(handle);
}

PyObject*
kth_py_native_vm_program_construct_default(PyObject* self, PyObject* Py_UNUSED(args)) {
    auto const result = kth_vm_program_construct_default();
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_VM_PROGRAM, kth_py_native_vm_program_capsule_dtor);
    if (capsule == NULL) {
        kth_vm_program_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_vm_program_construct_from_script(PyObject* self, PyObject* py_arg0) {
    PyObject* py_script = py_arg0;
    kth_script_const_t script_handle = (kth_script_const_t)PyCapsule_GetPointer(py_script, KTH_PY_CAPSULE_CHAIN_SCRIPT);
    if (script_handle == NULL) return NULL;
    auto const result = kth_vm_program_construct_from_script(script_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_VM_PROGRAM, kth_py_native_vm_program_capsule_dtor);
    if (capsule == NULL) {
        kth_vm_program_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_vm_program_construct_from_script_transaction_input_index_flags_value(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"script", (char*)"transaction", (char*)"input_index", (char*)"flags", (char*)"value", NULL};
    PyObject* py_script = NULL;
    PyObject* py_transaction = NULL;
    unsigned int input_index = 0;
    unsigned long long flags = 0;
    unsigned long long value = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OOIKK", kwlist, &py_script, &py_transaction, &input_index, &flags, &value)) {
        return NULL;
    }
    kth_script_const_t script_handle = (kth_script_const_t)PyCapsule_GetPointer(py_script, KTH_PY_CAPSULE_CHAIN_SCRIPT);
    if (script_handle == NULL) return NULL;
    kth_transaction_const_t transaction_handle = (kth_transaction_const_t)PyCapsule_GetPointer(py_transaction, KTH_PY_CAPSULE_CHAIN_TRANSACTION);
    if (transaction_handle == NULL) return NULL;
    auto const result = kth_vm_program_construct_from_script_transaction_input_index_flags_value(script_handle, transaction_handle, (uint32_t)input_index, (kth_script_flags_t)flags, (uint64_t)value);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_VM_PROGRAM, kth_py_native_vm_program_capsule_dtor);
    if (capsule == NULL) {
        kth_vm_program_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_vm_program_construct_from_script_transaction_input_index_flags_stack_value(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"script", (char*)"transaction", (char*)"input_index", (char*)"flags", (char*)"stack", (char*)"value", NULL};
    PyObject* py_script = NULL;
    PyObject* py_transaction = NULL;
    unsigned int input_index = 0;
    unsigned long long flags = 0;
    PyObject* py_stack = NULL;
    unsigned long long value = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OOIKOK", kwlist, &py_script, &py_transaction, &input_index, &flags, &py_stack, &value)) {
        return NULL;
    }
    kth_script_const_t script_handle = (kth_script_const_t)PyCapsule_GetPointer(py_script, KTH_PY_CAPSULE_CHAIN_SCRIPT);
    if (script_handle == NULL) return NULL;
    kth_transaction_const_t transaction_handle = (kth_transaction_const_t)PyCapsule_GetPointer(py_transaction, KTH_PY_CAPSULE_CHAIN_TRANSACTION);
    if (transaction_handle == NULL) return NULL;
    kth_data_stack_const_t stack_handle = (kth_data_stack_const_t)PyCapsule_GetPointer(py_stack, KTH_PY_CAPSULE_CHAIN_DATA_STACK);
    if (stack_handle == NULL) return NULL;
    auto const result = kth_vm_program_construct_from_script_transaction_input_index_flags_stack_value(script_handle, transaction_handle, (uint32_t)input_index, (kth_script_flags_t)flags, stack_handle, (uint64_t)value);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_VM_PROGRAM, kth_py_native_vm_program_capsule_dtor);
    if (capsule == NULL) {
        kth_vm_program_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_vm_program_construct_from_script_program(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"script", (char*)"x", NULL};
    PyObject* py_script = NULL;
    PyObject* py_x = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_script, &py_x)) {
        return NULL;
    }
    kth_script_const_t script_handle = (kth_script_const_t)PyCapsule_GetPointer(py_script, KTH_PY_CAPSULE_CHAIN_SCRIPT);
    if (script_handle == NULL) return NULL;
    kth_program_const_t x_handle = (kth_program_const_t)PyCapsule_GetPointer(py_x, KTH_PY_CAPSULE_VM_PROGRAM);
    if (x_handle == NULL) return NULL;
    auto const result = kth_vm_program_construct_from_script_program(script_handle, x_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_VM_PROGRAM, kth_py_native_vm_program_capsule_dtor);
    if (capsule == NULL) {
        kth_vm_program_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_vm_program_construct_from_script_program_move(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"script", (char*)"x", (char*)"move", NULL};
    PyObject* py_script = NULL;
    PyObject* py_x = NULL;
    int move = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OOp", kwlist, &py_script, &py_x, &move)) {
        return NULL;
    }
    kth_script_const_t script_handle = (kth_script_const_t)PyCapsule_GetPointer(py_script, KTH_PY_CAPSULE_CHAIN_SCRIPT);
    if (script_handle == NULL) return NULL;
    kth_program_const_t x_handle = (kth_program_const_t)PyCapsule_GetPointer(py_x, KTH_PY_CAPSULE_VM_PROGRAM);
    if (x_handle == NULL) return NULL;
    auto const result = kth_vm_program_construct_from_script_program_move(script_handle, x_handle, (kth_bool_t)move);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_VM_PROGRAM, kth_py_native_vm_program_capsule_dtor);
    if (capsule == NULL) {
        kth_vm_program_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_vm_program_copy(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_program_const_t self_handle = (kth_program_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_PROGRAM);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_program_copy(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_VM_PROGRAM, kth_py_native_vm_program_capsule_dtor);
    if (capsule == NULL) {
        kth_vm_program_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_vm_program_destruct(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_program_mut_t self_handle = (kth_program_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_PROGRAM);
    if (self_handle == NULL) return NULL;
    kth_vm_program_destruct(self_handle);
    PyCapsule_SetName(py_self, "kth.destroyed");
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_vm_program_get_metrics(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_program_const_t self_handle = (kth_program_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_PROGRAM);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_program_get_metrics(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_METRICS, kth_py_native_borrowed_parent_dtor);
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
kth_py_native_vm_program_is_valid(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_program_const_t self_handle = (kth_program_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_PROGRAM);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_program_is_valid(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_vm_program_flags(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_program_const_t self_handle = (kth_program_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_PROGRAM);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_program_flags(self_handle);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyObject*
kth_py_native_vm_program_max_script_element_size(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_program_const_t self_handle = (kth_program_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_PROGRAM);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_program_max_script_element_size(self_handle);
    return PyLong_FromSize_t((size_t)result);
}

PyObject*
kth_py_native_vm_program_max_integer_size_legacy(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_program_const_t self_handle = (kth_program_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_PROGRAM);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_program_max_integer_size_legacy(self_handle);
    return PyLong_FromSize_t((size_t)result);
}

PyObject*
kth_py_native_vm_program_max_integer_size(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_program_const_t self_handle = (kth_program_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_PROGRAM);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_program_max_integer_size(self_handle);
    return PyLong_FromSize_t((size_t)result);
}

PyObject*
kth_py_native_vm_program_is_chip_vm_limits_enabled(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_program_const_t self_handle = (kth_program_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_PROGRAM);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_program_is_chip_vm_limits_enabled(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_vm_program_is_bigint_enabled(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_program_const_t self_handle = (kth_program_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_PROGRAM);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_program_is_bigint_enabled(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_vm_program_input_index(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_program_const_t self_handle = (kth_program_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_PROGRAM);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_program_input_index(self_handle);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyObject*
kth_py_native_vm_program_value(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_program_const_t self_handle = (kth_program_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_PROGRAM);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_program_value(self_handle);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyObject*
kth_py_native_vm_program_transaction(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_program_const_t self_handle = (kth_program_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_PROGRAM);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_program_transaction(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_TRANSACTION, kth_py_native_borrowed_parent_dtor);
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
kth_py_native_vm_program_get_script(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_program_const_t self_handle = (kth_program_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_PROGRAM);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_program_get_script(self_handle);
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
kth_py_native_vm_program_reset_active_script(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_program_mut_t self_handle = (kth_program_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_PROGRAM);
    if (self_handle == NULL) return NULL;
    kth_vm_program_reset_active_script(self_handle);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_vm_program_operation_count(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_program_const_t self_handle = (kth_program_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_PROGRAM);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_program_operation_count(self_handle);
    return PyLong_FromSize_t((size_t)result);
}

PyObject*
kth_py_native_vm_program_evaluate_simple(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_program_mut_t self_handle = (kth_program_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_PROGRAM);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_program_evaluate_simple(self_handle);
    return PyLong_FromLong((long)result);
}

PyObject*
kth_py_native_vm_program_evaluate(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"op", NULL};
    PyObject* py_self = NULL;
    PyObject* py_op = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_op)) {
        return NULL;
    }
    kth_program_mut_t self_handle = (kth_program_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_PROGRAM);
    if (self_handle == NULL) return NULL;
    kth_operation_const_t op_handle = (kth_operation_const_t)PyCapsule_GetPointer(py_op, KTH_PY_CAPSULE_CHAIN_OPERATION);
    if (op_handle == NULL) return NULL;
    auto const result = kth_vm_program_evaluate(self_handle, op_handle);
    return PyLong_FromLong((long)result);
}

PyObject*
kth_py_native_vm_program_increment_operation_count_operation(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"op", NULL};
    PyObject* py_self = NULL;
    PyObject* py_op = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_op)) {
        return NULL;
    }
    kth_program_mut_t self_handle = (kth_program_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_PROGRAM);
    if (self_handle == NULL) return NULL;
    kth_operation_const_t op_handle = (kth_operation_const_t)PyCapsule_GetPointer(py_op, KTH_PY_CAPSULE_CHAIN_OPERATION);
    if (op_handle == NULL) return NULL;
    auto const result = kth_vm_program_increment_operation_count_operation(self_handle, op_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_vm_program_increment_operation_count_int32(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"public_keys", NULL};
    PyObject* py_self = NULL;
    int public_keys = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Oi", kwlist, &py_self, &public_keys)) {
        return NULL;
    }
    kth_program_mut_t self_handle = (kth_program_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_PROGRAM);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_program_increment_operation_count_int32(self_handle, (int32_t)public_keys);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_vm_program_mark_code_separator(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"pc", NULL};
    PyObject* py_self = NULL;
    Py_ssize_t pc = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "On", kwlist, &py_self, &pc)) {
        return NULL;
    }
    kth_program_mut_t self_handle = (kth_program_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_PROGRAM);
    if (self_handle == NULL) return NULL;
    if (pc < 0) {
        PyErr_Format(PyExc_ValueError, "pc must be non-negative, got %zd", pc);
        return NULL;
    }
    auto const result = kth_vm_program_mark_code_separator(self_handle, (kth_size_t)pc);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_vm_program_push(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    int value = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Op", kwlist, &py_self, &value)) {
        return NULL;
    }
    kth_program_mut_t self_handle = (kth_program_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_PROGRAM);
    if (self_handle == NULL) return NULL;
    kth_vm_program_push(self_handle, (kth_bool_t)value);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_vm_program_push_move(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"item", NULL};
    PyObject* py_self = NULL;
    char const* item_buf = NULL;
    Py_ssize_t item_size = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Oy#", kwlist, &py_self, &item_buf, &item_size)) {
        return NULL;
    }
    kth_program_mut_t self_handle = (kth_program_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_PROGRAM);
    if (self_handle == NULL) return NULL;
    kth_vm_program_push_move(self_handle, (uint8_t const*)item_buf, (kth_size_t)item_size);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_vm_program_push_copy(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"item", NULL};
    PyObject* py_self = NULL;
    char const* item_buf = NULL;
    Py_ssize_t item_size = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Oy#", kwlist, &py_self, &item_buf, &item_size)) {
        return NULL;
    }
    kth_program_mut_t self_handle = (kth_program_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_PROGRAM);
    if (self_handle == NULL) return NULL;
    kth_vm_program_push_copy(self_handle, (uint8_t const*)item_buf, (kth_size_t)item_size);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_vm_program_drop(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_program_mut_t self_handle = (kth_program_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_PROGRAM);
    if (self_handle == NULL) return NULL;
    kth_vm_program_drop(self_handle);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_vm_program_pop(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_program_mut_t self_handle = (kth_program_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_PROGRAM);
    if (self_handle == NULL) return NULL;
    kth_size_t out_size = 0;
    auto const result = kth_vm_program_pop(self_handle, &out_size);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: serialization failed");
        return NULL;
    }
    PyObject* py_result = Py_BuildValue("y#", result, (Py_ssize_t)out_size);
    kth_core_destruct_array(result);
    return py_result;
}

PyObject*
kth_py_native_vm_program_duplicate(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"index", NULL};
    PyObject* py_self = NULL;
    Py_ssize_t index = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "On", kwlist, &py_self, &index)) {
        return NULL;
    }
    kth_program_mut_t self_handle = (kth_program_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_PROGRAM);
    if (self_handle == NULL) return NULL;
    if (index < 0) {
        PyErr_Format(PyExc_ValueError, "index must be non-negative, got %zd", index);
        return NULL;
    }
    kth_vm_program_duplicate(self_handle, (kth_size_t)index);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_vm_program_swap(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"index_left", (char*)"index_right", NULL};
    PyObject* py_self = NULL;
    Py_ssize_t index_left = 0;
    Py_ssize_t index_right = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Onn", kwlist, &py_self, &index_left, &index_right)) {
        return NULL;
    }
    kth_program_mut_t self_handle = (kth_program_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_PROGRAM);
    if (self_handle == NULL) return NULL;
    if (index_left < 0) {
        PyErr_Format(PyExc_ValueError, "index_left must be non-negative, got %zd", index_left);
        return NULL;
    }
    if (index_right < 0) {
        PyErr_Format(PyExc_ValueError, "index_right must be non-negative, got %zd", index_right);
        return NULL;
    }
    kth_vm_program_swap(self_handle, (kth_size_t)index_left, (kth_size_t)index_right);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_vm_program_empty(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_program_const_t self_handle = (kth_program_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_PROGRAM);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_program_empty(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_vm_program_stack_true(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"clean", NULL};
    PyObject* py_self = NULL;
    int clean = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Op", kwlist, &py_self, &clean)) {
        return NULL;
    }
    kth_program_const_t self_handle = (kth_program_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_PROGRAM);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_program_stack_true(self_handle, (kth_bool_t)clean);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_vm_program_stack_result(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"clean", NULL};
    PyObject* py_self = NULL;
    int clean = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Op", kwlist, &py_self, &clean)) {
        return NULL;
    }
    kth_program_const_t self_handle = (kth_program_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_PROGRAM);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_program_stack_result(self_handle, (kth_bool_t)clean);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_vm_program_is_stack_overflow_simple(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_program_const_t self_handle = (kth_program_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_PROGRAM);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_program_is_stack_overflow_simple(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_vm_program_is_stack_overflow(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"extra", NULL};
    PyObject* py_self = NULL;
    Py_ssize_t extra = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "On", kwlist, &py_self, &extra)) {
        return NULL;
    }
    kth_program_const_t self_handle = (kth_program_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_PROGRAM);
    if (self_handle == NULL) return NULL;
    if (extra < 0) {
        PyErr_Format(PyExc_ValueError, "extra must be non-negative, got %zd", extra);
        return NULL;
    }
    auto const result = kth_vm_program_is_stack_overflow(self_handle, (kth_size_t)extra);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_vm_program_if_(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"op", NULL};
    PyObject* py_self = NULL;
    PyObject* py_op = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_op)) {
        return NULL;
    }
    kth_program_const_t self_handle = (kth_program_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_PROGRAM);
    if (self_handle == NULL) return NULL;
    kth_operation_const_t op_handle = (kth_operation_const_t)PyCapsule_GetPointer(py_op, KTH_PY_CAPSULE_CHAIN_OPERATION);
    if (op_handle == NULL) return NULL;
    auto const result = kth_vm_program_if_(self_handle, op_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_vm_program_item(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"index", NULL};
    PyObject* py_self = NULL;
    Py_ssize_t index = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "On", kwlist, &py_self, &index)) {
        return NULL;
    }
    kth_program_const_t self_handle = (kth_program_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_PROGRAM);
    if (self_handle == NULL) return NULL;
    if (index < 0) {
        PyErr_Format(PyExc_ValueError, "index must be non-negative, got %zd", index);
        return NULL;
    }
    kth_size_t out_size = 0;
    auto const result = kth_vm_program_item(self_handle, (kth_size_t)index, &out_size);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: serialization failed");
        return NULL;
    }
    PyObject* py_result = Py_BuildValue("y#", result, (Py_ssize_t)out_size);
    kth_core_destruct_array(result);
    return py_result;
}

PyObject*
kth_py_native_vm_program_top(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_program_const_t self_handle = (kth_program_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_PROGRAM);
    if (self_handle == NULL) return NULL;
    kth_size_t out_size = 0;
    auto const result = kth_vm_program_top(self_handle, &out_size);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: serialization failed");
        return NULL;
    }
    PyObject* py_result = Py_BuildValue("y#", result, (Py_ssize_t)out_size);
    kth_core_destruct_array(result);
    return py_result;
}

PyObject*
kth_py_native_vm_program_subscript(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_program_const_t self_handle = (kth_program_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_PROGRAM);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_program_subscript(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL list returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_OPERATION_LIST, kth_py_native_chain_operation_list_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_operation_list_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_vm_program_size(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_program_const_t self_handle = (kth_program_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_PROGRAM);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_program_size(self_handle);
    return PyLong_FromSize_t((size_t)result);
}

PyObject*
kth_py_native_vm_program_conditional_stack_size(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_program_const_t self_handle = (kth_program_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_PROGRAM);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_program_conditional_stack_size(self_handle);
    return PyLong_FromSize_t((size_t)result);
}

PyObject*
kth_py_native_vm_program_empty_alternate(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_program_const_t self_handle = (kth_program_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_PROGRAM);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_program_empty_alternate(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_vm_program_push_alternate(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    char const* value_buf = NULL;
    Py_ssize_t value_size = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Oy#", kwlist, &py_self, &value_buf, &value_size)) {
        return NULL;
    }
    kth_program_mut_t self_handle = (kth_program_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_PROGRAM);
    if (self_handle == NULL) return NULL;
    kth_vm_program_push_alternate(self_handle, (uint8_t const*)value_buf, (kth_size_t)value_size);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_vm_program_pop_alternate(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_program_mut_t self_handle = (kth_program_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_PROGRAM);
    if (self_handle == NULL) return NULL;
    kth_size_t out_size = 0;
    auto const result = kth_vm_program_pop_alternate(self_handle, &out_size);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: serialization failed");
        return NULL;
    }
    PyObject* py_result = Py_BuildValue("y#", result, (Py_ssize_t)out_size);
    kth_core_destruct_array(result);
    return py_result;
}

PyObject*
kth_py_native_vm_program_open(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    int value = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Op", kwlist, &py_self, &value)) {
        return NULL;
    }
    kth_program_mut_t self_handle = (kth_program_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_PROGRAM);
    if (self_handle == NULL) return NULL;
    kth_vm_program_open(self_handle, (kth_bool_t)value);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_vm_program_negate(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_program_mut_t self_handle = (kth_program_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_PROGRAM);
    if (self_handle == NULL) return NULL;
    kth_vm_program_negate(self_handle);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_vm_program_close(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_program_mut_t self_handle = (kth_program_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_PROGRAM);
    if (self_handle == NULL) return NULL;
    kth_vm_program_close(self_handle);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_vm_program_closed(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_program_const_t self_handle = (kth_program_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_PROGRAM);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_program_closed(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_vm_program_succeeded(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_program_const_t self_handle = (kth_program_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_VM_PROGRAM);
    if (self_handle == NULL) return NULL;
    auto const result = kth_vm_program_succeeded(self_handle);
    return PyBool_FromLong((long)result);
}

PyMethodDef kth_py_native_vm_program_methods[] = {
    {"vm_program_construct_default", (PyCFunction)kth_py_native_vm_program_construct_default, METH_NOARGS, NULL},
    {"vm_program_construct_from_script", (PyCFunction)kth_py_native_vm_program_construct_from_script, METH_O, NULL},
    {"vm_program_construct_from_script_transaction_input_index_flags_value", (PyCFunction)kth_py_native_vm_program_construct_from_script_transaction_input_index_flags_value, METH_VARARGS | METH_KEYWORDS, NULL},
    {"vm_program_construct_from_script_transaction_input_index_flags_stack_value", (PyCFunction)kth_py_native_vm_program_construct_from_script_transaction_input_index_flags_stack_value, METH_VARARGS | METH_KEYWORDS, NULL},
    {"vm_program_construct_from_script_program", (PyCFunction)kth_py_native_vm_program_construct_from_script_program, METH_VARARGS | METH_KEYWORDS, NULL},
    {"vm_program_construct_from_script_program_move", (PyCFunction)kth_py_native_vm_program_construct_from_script_program_move, METH_VARARGS | METH_KEYWORDS, NULL},
    {"vm_program_copy", (PyCFunction)kth_py_native_vm_program_copy, METH_O, NULL},
    {"vm_program_destruct", (PyCFunction)kth_py_native_vm_program_destruct, METH_O, NULL},
    {"vm_program_get_metrics", (PyCFunction)kth_py_native_vm_program_get_metrics, METH_O, NULL},
    {"vm_program_is_valid", (PyCFunction)kth_py_native_vm_program_is_valid, METH_O, NULL},
    {"vm_program_flags", (PyCFunction)kth_py_native_vm_program_flags, METH_O, NULL},
    {"vm_program_max_script_element_size", (PyCFunction)kth_py_native_vm_program_max_script_element_size, METH_O, NULL},
    {"vm_program_max_integer_size_legacy", (PyCFunction)kth_py_native_vm_program_max_integer_size_legacy, METH_O, NULL},
    {"vm_program_max_integer_size", (PyCFunction)kth_py_native_vm_program_max_integer_size, METH_O, NULL},
    {"vm_program_is_chip_vm_limits_enabled", (PyCFunction)kth_py_native_vm_program_is_chip_vm_limits_enabled, METH_O, NULL},
    {"vm_program_is_bigint_enabled", (PyCFunction)kth_py_native_vm_program_is_bigint_enabled, METH_O, NULL},
    {"vm_program_input_index", (PyCFunction)kth_py_native_vm_program_input_index, METH_O, NULL},
    {"vm_program_value", (PyCFunction)kth_py_native_vm_program_value, METH_O, NULL},
    {"vm_program_transaction", (PyCFunction)kth_py_native_vm_program_transaction, METH_O, NULL},
    {"vm_program_get_script", (PyCFunction)kth_py_native_vm_program_get_script, METH_O, NULL},
    {"vm_program_reset_active_script", (PyCFunction)kth_py_native_vm_program_reset_active_script, METH_O, NULL},
    {"vm_program_operation_count", (PyCFunction)kth_py_native_vm_program_operation_count, METH_O, NULL},
    {"vm_program_evaluate_simple", (PyCFunction)kth_py_native_vm_program_evaluate_simple, METH_O, NULL},
    {"vm_program_evaluate", (PyCFunction)kth_py_native_vm_program_evaluate, METH_VARARGS | METH_KEYWORDS, NULL},
    {"vm_program_increment_operation_count_operation", (PyCFunction)kth_py_native_vm_program_increment_operation_count_operation, METH_VARARGS | METH_KEYWORDS, NULL},
    {"vm_program_increment_operation_count_int32", (PyCFunction)kth_py_native_vm_program_increment_operation_count_int32, METH_VARARGS | METH_KEYWORDS, NULL},
    {"vm_program_mark_code_separator", (PyCFunction)kth_py_native_vm_program_mark_code_separator, METH_VARARGS | METH_KEYWORDS, NULL},
    {"vm_program_push", (PyCFunction)kth_py_native_vm_program_push, METH_VARARGS | METH_KEYWORDS, NULL},
    {"vm_program_push_move", (PyCFunction)kth_py_native_vm_program_push_move, METH_VARARGS | METH_KEYWORDS, NULL},
    {"vm_program_push_copy", (PyCFunction)kth_py_native_vm_program_push_copy, METH_VARARGS | METH_KEYWORDS, NULL},
    {"vm_program_drop", (PyCFunction)kth_py_native_vm_program_drop, METH_O, NULL},
    {"vm_program_pop", (PyCFunction)kth_py_native_vm_program_pop, METH_O, NULL},
    {"vm_program_duplicate", (PyCFunction)kth_py_native_vm_program_duplicate, METH_VARARGS | METH_KEYWORDS, NULL},
    {"vm_program_swap", (PyCFunction)kth_py_native_vm_program_swap, METH_VARARGS | METH_KEYWORDS, NULL},
    {"vm_program_empty", (PyCFunction)kth_py_native_vm_program_empty, METH_O, NULL},
    {"vm_program_stack_true", (PyCFunction)kth_py_native_vm_program_stack_true, METH_VARARGS | METH_KEYWORDS, NULL},
    {"vm_program_stack_result", (PyCFunction)kth_py_native_vm_program_stack_result, METH_VARARGS | METH_KEYWORDS, NULL},
    {"vm_program_is_stack_overflow_simple", (PyCFunction)kth_py_native_vm_program_is_stack_overflow_simple, METH_O, NULL},
    {"vm_program_is_stack_overflow", (PyCFunction)kth_py_native_vm_program_is_stack_overflow, METH_VARARGS | METH_KEYWORDS, NULL},
    {"vm_program_if_", (PyCFunction)kth_py_native_vm_program_if_, METH_VARARGS | METH_KEYWORDS, NULL},
    {"vm_program_item", (PyCFunction)kth_py_native_vm_program_item, METH_VARARGS | METH_KEYWORDS, NULL},
    {"vm_program_top", (PyCFunction)kth_py_native_vm_program_top, METH_O, NULL},
    {"vm_program_subscript", (PyCFunction)kth_py_native_vm_program_subscript, METH_O, NULL},
    {"vm_program_size", (PyCFunction)kth_py_native_vm_program_size, METH_O, NULL},
    {"vm_program_conditional_stack_size", (PyCFunction)kth_py_native_vm_program_conditional_stack_size, METH_O, NULL},
    {"vm_program_empty_alternate", (PyCFunction)kth_py_native_vm_program_empty_alternate, METH_O, NULL},
    {"vm_program_push_alternate", (PyCFunction)kth_py_native_vm_program_push_alternate, METH_VARARGS | METH_KEYWORDS, NULL},
    {"vm_program_pop_alternate", (PyCFunction)kth_py_native_vm_program_pop_alternate, METH_O, NULL},
    {"vm_program_open", (PyCFunction)kth_py_native_vm_program_open, METH_VARARGS | METH_KEYWORDS, NULL},
    {"vm_program_negate", (PyCFunction)kth_py_native_vm_program_negate, METH_O, NULL},
    {"vm_program_close", (PyCFunction)kth_py_native_vm_program_close, METH_O, NULL},
    {"vm_program_closed", (PyCFunction)kth_py_native_vm_program_closed, METH_O, NULL},
    {"vm_program_succeeded", (PyCFunction)kth_py_native_vm_program_succeeded, METH_O, NULL},
    {NULL, NULL, 0, NULL}  // sentinel
};

#ifdef __cplusplus
} // extern "C"
#endif
