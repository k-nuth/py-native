// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/py-native/chain/transaction.h>

#include <string.h>
#include <kth/capi.h>
#include <kth/capi/chain/transaction.h>
#include <kth/py-native/capsule_names.h>
#include <kth/py-native/utils.h>

#ifdef __cplusplus
extern "C" {
#endif

// PyCapsule destructor — released by GC when the capsule is
// collected. Explicit `destruct` calls set the capsule name to
// "kth.destroyed", so PyCapsule_IsValid returns false and this
// destructor becomes a no-op (no double-free).
void kth_py_native_chain_transaction_capsule_dtor(PyObject* capsule) {
    if ( ! PyCapsule_IsValid(capsule, KTH_PY_CAPSULE_CHAIN_TRANSACTION)) return;
    kth_transaction_mut_t handle = (kth_transaction_mut_t)PyCapsule_GetPointer(capsule, KTH_PY_CAPSULE_CHAIN_TRANSACTION);
    if (handle != NULL) kth_chain_transaction_destruct(handle);
}

PyObject*
kth_py_native_chain_transaction_construct_default(PyObject* self, PyObject* Py_UNUSED(args)) {
    auto const result = kth_chain_transaction_construct_default();
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_TRANSACTION, kth_py_native_chain_transaction_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_transaction_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_transaction_construct_from_data(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"reader", (char*)"wire", NULL};
    char const* reader_buf = NULL;
    Py_ssize_t reader_size = 0;
    int wire = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "y#p", kwlist, &reader_buf, &reader_size, &wire)) {
        return NULL;
    }
    kth_transaction_mut_t out = NULL;
    kth_error_code_t result = kth_chain_transaction_construct_from_data((uint8_t const*)reader_buf, (kth_size_t)reader_size, (kth_bool_t)wire, &out);
    if (result != kth_ec_success) {
        PyErr_Format(PyExc_RuntimeError, "kth error code %d", (int)result);
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)out, KTH_PY_CAPSULE_CHAIN_TRANSACTION, kth_py_native_chain_transaction_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_transaction_destruct(out);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_transaction_construct_from_version_locktime_inputs_outputs(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"version", (char*)"locktime", (char*)"inputs", (char*)"outputs", NULL};
    unsigned int version = 0;
    unsigned int locktime = 0;
    PyObject* py_inputs = NULL;
    PyObject* py_outputs = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "IIOO", kwlist, &version, &locktime, &py_inputs, &py_outputs)) {
        return NULL;
    }
    kth_input_list_const_t inputs_handle = (kth_input_list_const_t)PyCapsule_GetPointer(py_inputs, KTH_PY_CAPSULE_CHAIN_INPUT_LIST);
    if (inputs_handle == NULL) return NULL;
    kth_output_list_const_t outputs_handle = (kth_output_list_const_t)PyCapsule_GetPointer(py_outputs, KTH_PY_CAPSULE_CHAIN_OUTPUT_LIST);
    if (outputs_handle == NULL) return NULL;
    auto const result = kth_chain_transaction_construct_from_version_locktime_inputs_outputs((uint32_t)version, (uint32_t)locktime, inputs_handle, outputs_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_TRANSACTION, kth_py_native_chain_transaction_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_transaction_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_transaction_construct_from_transaction_hash(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"x", (char*)"hash", NULL};
    PyObject* py_x = NULL;
    char const* hash_buf = NULL;
    Py_ssize_t hash_size = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Oy#", kwlist, &py_x, &hash_buf, &hash_size)) {
        return NULL;
    }
    kth_transaction_const_t x_handle = (kth_transaction_const_t)PyCapsule_GetPointer(py_x, KTH_PY_CAPSULE_CHAIN_TRANSACTION);
    if (x_handle == NULL) return NULL;
    if (hash_size != (Py_ssize_t)KTH_BITCOIN_HASH_SIZE) {
        PyErr_Format(PyExc_ValueError, "expected %d-byte hash, got %zd", (int)KTH_BITCOIN_HASH_SIZE, hash_size);
        return NULL;
    }
    kth_hash_t hash;
    memcpy(hash.hash, hash_buf, (size_t)KTH_BITCOIN_HASH_SIZE);
    auto const result = kth_chain_transaction_construct_from_transaction_hash(x_handle, &hash);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_TRANSACTION, kth_py_native_chain_transaction_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_transaction_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_transaction_copy(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_transaction_const_t self_handle = (kth_transaction_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_TRANSACTION);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_transaction_copy(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_TRANSACTION, kth_py_native_chain_transaction_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_transaction_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_transaction_destruct(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_transaction_mut_t self_handle = (kth_transaction_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_TRANSACTION);
    if (self_handle == NULL) return NULL;
    kth_chain_transaction_destruct(self_handle);
    PyCapsule_SetName(py_self, "kth.destroyed");
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_transaction_to_data(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"wire", NULL};
    PyObject* py_self = NULL;
    int wire = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Op", kwlist, &py_self, &wire)) {
        return NULL;
    }
    kth_transaction_const_t self_handle = (kth_transaction_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_TRANSACTION);
    if (self_handle == NULL) return NULL;
    kth_size_t out_size = 0;
    auto const result = kth_chain_transaction_to_data(self_handle, (kth_bool_t)wire, &out_size);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: serialization failed");
        return NULL;
    }
    PyObject* py_result = Py_BuildValue("y#", result, (Py_ssize_t)out_size);
    kth_core_destruct_array(result);
    return py_result;
}

PyObject*
kth_py_native_chain_transaction_serialized_size(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"wire", NULL};
    PyObject* py_self = NULL;
    int wire = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Op", kwlist, &py_self, &wire)) {
        return NULL;
    }
    kth_transaction_const_t self_handle = (kth_transaction_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_TRANSACTION);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_transaction_serialized_size(self_handle, (kth_bool_t)wire);
    return PyLong_FromSize_t((size_t)result);
}

PyObject*
kth_py_native_chain_transaction_set_version(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    unsigned int value = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OI", kwlist, &py_self, &value)) {
        return NULL;
    }
    kth_transaction_mut_t self_handle = (kth_transaction_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_TRANSACTION);
    if (self_handle == NULL) return NULL;
    kth_chain_transaction_set_version(self_handle, (uint32_t)value);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_transaction_set_locktime(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    unsigned int value = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OI", kwlist, &py_self, &value)) {
        return NULL;
    }
    kth_transaction_mut_t self_handle = (kth_transaction_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_TRANSACTION);
    if (self_handle == NULL) return NULL;
    kth_chain_transaction_set_locktime(self_handle, (uint32_t)value);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_transaction_set_inputs(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    PyObject* py_value = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_value)) {
        return NULL;
    }
    kth_transaction_mut_t self_handle = (kth_transaction_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_TRANSACTION);
    if (self_handle == NULL) return NULL;
    kth_input_list_const_t value_handle = (kth_input_list_const_t)PyCapsule_GetPointer(py_value, KTH_PY_CAPSULE_CHAIN_INPUT_LIST);
    if (value_handle == NULL) return NULL;
    kth_chain_transaction_set_inputs(self_handle, value_handle);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_transaction_set_outputs(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    PyObject* py_value = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_value)) {
        return NULL;
    }
    kth_transaction_mut_t self_handle = (kth_transaction_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_TRANSACTION);
    if (self_handle == NULL) return NULL;
    kth_output_list_const_t value_handle = (kth_output_list_const_t)PyCapsule_GetPointer(py_value, KTH_PY_CAPSULE_CHAIN_OUTPUT_LIST);
    if (value_handle == NULL) return NULL;
    kth_chain_transaction_set_outputs(self_handle, value_handle);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_transaction_outputs_hash(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_transaction_const_t self_handle = (kth_transaction_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_TRANSACTION);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_transaction_outputs_hash(self_handle);
    return Py_BuildValue("y#", result.hash, (Py_ssize_t)KTH_BITCOIN_HASH_SIZE);
}

PyObject*
kth_py_native_chain_transaction_inpoints_hash(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_transaction_const_t self_handle = (kth_transaction_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_TRANSACTION);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_transaction_inpoints_hash(self_handle);
    return Py_BuildValue("y#", result.hash, (Py_ssize_t)KTH_BITCOIN_HASH_SIZE);
}

PyObject*
kth_py_native_chain_transaction_sequences_hash(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_transaction_const_t self_handle = (kth_transaction_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_TRANSACTION);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_transaction_sequences_hash(self_handle);
    return Py_BuildValue("y#", result.hash, (Py_ssize_t)KTH_BITCOIN_HASH_SIZE);
}

PyObject*
kth_py_native_chain_transaction_utxos_hash(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_transaction_const_t self_handle = (kth_transaction_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_TRANSACTION);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_transaction_utxos_hash(self_handle);
    return Py_BuildValue("y#", result.hash, (Py_ssize_t)KTH_BITCOIN_HASH_SIZE);
}

PyObject*
kth_py_native_chain_transaction_hash(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_transaction_const_t self_handle = (kth_transaction_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_TRANSACTION);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_transaction_hash(self_handle);
    return Py_BuildValue("y#", result.hash, (Py_ssize_t)KTH_BITCOIN_HASH_SIZE);
}

PyObject*
kth_py_native_chain_transaction_recompute_hash(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_transaction_mut_t self_handle = (kth_transaction_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_TRANSACTION);
    if (self_handle == NULL) return NULL;
    kth_chain_transaction_recompute_hash(self_handle);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_transaction_fees(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_transaction_const_t self_handle = (kth_transaction_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_TRANSACTION);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_transaction_fees(self_handle);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyObject*
kth_py_native_chain_transaction_total_input_value(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_transaction_const_t self_handle = (kth_transaction_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_TRANSACTION);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_transaction_total_input_value(self_handle);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyObject*
kth_py_native_chain_transaction_total_output_value(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_transaction_const_t self_handle = (kth_transaction_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_TRANSACTION);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_transaction_total_output_value(self_handle);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyObject*
kth_py_native_chain_transaction_signature_operations_simple(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_transaction_const_t self_handle = (kth_transaction_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_TRANSACTION);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_transaction_signature_operations_simple(self_handle);
    return PyLong_FromSize_t((size_t)result);
}

PyObject*
kth_py_native_chain_transaction_is_overspent(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_transaction_const_t self_handle = (kth_transaction_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_TRANSACTION);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_transaction_is_overspent(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_transaction_check(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"max_block_size", (char*)"transaction_pool", (char*)"retarget", NULL};
    PyObject* py_self = NULL;
    Py_ssize_t max_block_size = 0;
    int transaction_pool = 0;
    int retarget = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Onpp", kwlist, &py_self, &max_block_size, &transaction_pool, &retarget)) {
        return NULL;
    }
    kth_transaction_const_t self_handle = (kth_transaction_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_TRANSACTION);
    if (self_handle == NULL) return NULL;
    if (max_block_size < 0) {
        PyErr_Format(PyExc_ValueError, "max_block_size must be non-negative, got %zd", max_block_size);
        return NULL;
    }
    auto const result = kth_chain_transaction_check(self_handle, (kth_size_t)max_block_size, (kth_bool_t)transaction_pool, (kth_bool_t)retarget);
    return PyLong_FromLong((long)result);
}

PyObject*
kth_py_native_chain_transaction_accept(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"flags", (char*)"height", (char*)"median_time_past", (char*)"max_sigops", (char*)"is_under_checkpoint", (char*)"transaction_pool", NULL};
    PyObject* py_self = NULL;
    unsigned long long flags = 0;
    Py_ssize_t height = 0;
    unsigned int median_time_past = 0;
    Py_ssize_t max_sigops = 0;
    int is_under_checkpoint = 0;
    int transaction_pool = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OKnInpp", kwlist, &py_self, &flags, &height, &median_time_past, &max_sigops, &is_under_checkpoint, &transaction_pool)) {
        return NULL;
    }
    kth_transaction_const_t self_handle = (kth_transaction_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_TRANSACTION);
    if (self_handle == NULL) return NULL;
    if (height < 0) {
        PyErr_Format(PyExc_ValueError, "height must be non-negative, got %zd", height);
        return NULL;
    }
    if (max_sigops < 0) {
        PyErr_Format(PyExc_ValueError, "max_sigops must be non-negative, got %zd", max_sigops);
        return NULL;
    }
    auto const result = kth_chain_transaction_accept(self_handle, (kth_script_flags_t)flags, (kth_size_t)height, (uint32_t)median_time_past, (kth_size_t)max_sigops, (kth_bool_t)is_under_checkpoint, (kth_bool_t)transaction_pool);
    return PyLong_FromLong((long)result);
}

PyObject*
kth_py_native_chain_transaction_connect_simple(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_transaction_const_t self_handle = (kth_transaction_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_TRANSACTION);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_transaction_connect_simple(self_handle);
    return PyLong_FromLong((long)result);
}

PyObject*
kth_py_native_chain_transaction_connect(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"state", NULL};
    PyObject* py_self = NULL;
    PyObject* py_state = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_state)) {
        return NULL;
    }
    kth_transaction_const_t self_handle = (kth_transaction_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_TRANSACTION);
    if (self_handle == NULL) return NULL;
    kth_chain_state_const_t state_handle = (kth_chain_state_const_t)PyCapsule_GetPointer(py_state, KTH_PY_CAPSULE_CHAIN_CHAIN_STATE);
    if (state_handle == NULL) return NULL;
    auto const result = kth_chain_transaction_connect(self_handle, state_handle);
    return PyLong_FromLong((long)result);
}

PyObject*
kth_py_native_chain_transaction_connect_input(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"state", (char*)"input_index", NULL};
    PyObject* py_self = NULL;
    PyObject* py_state = NULL;
    Py_ssize_t input_index = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OOn", kwlist, &py_self, &py_state, &input_index)) {
        return NULL;
    }
    kth_transaction_const_t self_handle = (kth_transaction_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_TRANSACTION);
    if (self_handle == NULL) return NULL;
    kth_chain_state_const_t state_handle = (kth_chain_state_const_t)PyCapsule_GetPointer(py_state, KTH_PY_CAPSULE_CHAIN_CHAIN_STATE);
    if (state_handle == NULL) return NULL;
    if (input_index < 0) {
        PyErr_Format(PyExc_ValueError, "input_index must be non-negative, got %zd", input_index);
        return NULL;
    }
    auto const result = kth_chain_transaction_connect_input(self_handle, state_handle, (kth_size_t)input_index);
    return PyLong_FromLong((long)result);
}

PyObject*
kth_py_native_chain_transaction_reset(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_transaction_mut_t self_handle = (kth_transaction_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_TRANSACTION);
    if (self_handle == NULL) return NULL;
    kth_chain_transaction_reset(self_handle);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_transaction_equals(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"other", NULL};
    PyObject* py_self = NULL;
    PyObject* py_other = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_other)) {
        return NULL;
    }
    kth_transaction_const_t self_handle = (kth_transaction_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_TRANSACTION);
    if (self_handle == NULL) return NULL;
    kth_transaction_const_t other_handle = (kth_transaction_const_t)PyCapsule_GetPointer(py_other, KTH_PY_CAPSULE_CHAIN_TRANSACTION);
    if (other_handle == NULL) return NULL;
    auto const result = kth_chain_transaction_equals(self_handle, other_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_transaction_is_valid(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_transaction_const_t self_handle = (kth_transaction_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_TRANSACTION);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_transaction_is_valid(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_transaction_version(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_transaction_const_t self_handle = (kth_transaction_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_TRANSACTION);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_transaction_version(self_handle);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyObject*
kth_py_native_chain_transaction_locktime(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_transaction_const_t self_handle = (kth_transaction_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_TRANSACTION);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_transaction_locktime(self_handle);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyObject*
kth_py_native_chain_transaction_inputs(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_transaction_const_t self_handle = (kth_transaction_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_TRANSACTION);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_transaction_inputs(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL list returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_INPUT_LIST, kth_py_native_borrowed_parent_dtor);
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
kth_py_native_chain_transaction_outputs(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_transaction_const_t self_handle = (kth_transaction_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_TRANSACTION);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_transaction_outputs(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL list returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_OUTPUT_LIST, kth_py_native_borrowed_parent_dtor);
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
kth_py_native_chain_transaction_previous_outputs(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_transaction_const_t self_handle = (kth_transaction_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_TRANSACTION);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_transaction_previous_outputs(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL list returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_POINT_LIST, kth_py_native_chain_point_list_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_point_list_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_transaction_missing_previous_outputs(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_transaction_const_t self_handle = (kth_transaction_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_TRANSACTION);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_transaction_missing_previous_outputs(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL list returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_POINT_LIST, kth_py_native_chain_point_list_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_point_list_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_transaction_missing_previous_transactions(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_transaction_const_t self_handle = (kth_transaction_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_TRANSACTION);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_transaction_missing_previous_transactions(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL list returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CORE_HASH_LIST, NULL);
    if (capsule == NULL) {
        kth_core_hash_list_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_transaction_signature_operations(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"bip16", (char*)"bip141", NULL};
    PyObject* py_self = NULL;
    int bip16 = 0;
    int bip141 = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Opp", kwlist, &py_self, &bip16, &bip141)) {
        return NULL;
    }
    kth_transaction_const_t self_handle = (kth_transaction_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_TRANSACTION);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_transaction_signature_operations(self_handle, (kth_bool_t)bip16, (kth_bool_t)bip141);
    return PyLong_FromSize_t((size_t)result);
}

PyObject*
kth_py_native_chain_transaction_is_coinbase(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_transaction_const_t self_handle = (kth_transaction_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_TRANSACTION);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_transaction_is_coinbase(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_transaction_is_null_non_coinbase(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_transaction_const_t self_handle = (kth_transaction_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_TRANSACTION);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_transaction_is_null_non_coinbase(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_transaction_is_oversized_coinbase(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_transaction_const_t self_handle = (kth_transaction_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_TRANSACTION);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_transaction_is_oversized_coinbase(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_transaction_is_mature(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"height", NULL};
    PyObject* py_self = NULL;
    Py_ssize_t height = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "On", kwlist, &py_self, &height)) {
        return NULL;
    }
    kth_transaction_const_t self_handle = (kth_transaction_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_TRANSACTION);
    if (self_handle == NULL) return NULL;
    if (height < 0) {
        PyErr_Format(PyExc_ValueError, "height must be non-negative, got %zd", height);
        return NULL;
    }
    auto const result = kth_chain_transaction_is_mature(self_handle, (kth_size_t)height);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_transaction_is_internal_double_spend(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_transaction_const_t self_handle = (kth_transaction_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_TRANSACTION);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_transaction_is_internal_double_spend(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_transaction_is_double_spend(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"include_unconfirmed", NULL};
    PyObject* py_self = NULL;
    int include_unconfirmed = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Op", kwlist, &py_self, &include_unconfirmed)) {
        return NULL;
    }
    kth_transaction_const_t self_handle = (kth_transaction_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_TRANSACTION);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_transaction_is_double_spend(self_handle, (kth_bool_t)include_unconfirmed);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_transaction_is_dusty(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"minimum_output_value", NULL};
    PyObject* py_self = NULL;
    unsigned long long minimum_output_value = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OK", kwlist, &py_self, &minimum_output_value)) {
        return NULL;
    }
    kth_transaction_const_t self_handle = (kth_transaction_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_TRANSACTION);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_transaction_is_dusty(self_handle, (uint64_t)minimum_output_value);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_transaction_is_missing_previous_outputs(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_transaction_const_t self_handle = (kth_transaction_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_TRANSACTION);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_transaction_is_missing_previous_outputs(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_transaction_is_final(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"block_height", (char*)"block_time", NULL};
    PyObject* py_self = NULL;
    Py_ssize_t block_height = 0;
    unsigned int block_time = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OnI", kwlist, &py_self, &block_height, &block_time)) {
        return NULL;
    }
    kth_transaction_const_t self_handle = (kth_transaction_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_TRANSACTION);
    if (self_handle == NULL) return NULL;
    if (block_height < 0) {
        PyErr_Format(PyExc_ValueError, "block_height must be non-negative, got %zd", block_height);
        return NULL;
    }
    auto const result = kth_chain_transaction_is_final(self_handle, (kth_size_t)block_height, (uint32_t)block_time);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_transaction_is_locked(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"block_height", (char*)"median_time_past", NULL};
    PyObject* py_self = NULL;
    Py_ssize_t block_height = 0;
    unsigned int median_time_past = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OnI", kwlist, &py_self, &block_height, &median_time_past)) {
        return NULL;
    }
    kth_transaction_const_t self_handle = (kth_transaction_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_TRANSACTION);
    if (self_handle == NULL) return NULL;
    if (block_height < 0) {
        PyErr_Format(PyExc_ValueError, "block_height must be non-negative, got %zd", block_height);
        return NULL;
    }
    auto const result = kth_chain_transaction_is_locked(self_handle, (kth_size_t)block_height, (uint32_t)median_time_past);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_transaction_is_locktime_conflict(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_transaction_const_t self_handle = (kth_transaction_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_TRANSACTION);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_transaction_is_locktime_conflict(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_transaction_min_tx_size(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"flags", NULL};
    PyObject* py_self = NULL;
    unsigned long long flags = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OK", kwlist, &py_self, &flags)) {
        return NULL;
    }
    kth_transaction_const_t self_handle = (kth_transaction_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_TRANSACTION);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_transaction_min_tx_size(self_handle, (kth_script_flags_t)flags);
    return PyLong_FromSize_t((size_t)result);
}

PyObject*
kth_py_native_chain_transaction_is_standard_simple(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_transaction_const_t self_handle = (kth_transaction_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_TRANSACTION);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_transaction_is_standard_simple(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_transaction_is_standard(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"flags", NULL};
    PyObject* py_self = NULL;
    unsigned long long flags = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OK", kwlist, &py_self, &flags)) {
        return NULL;
    }
    kth_transaction_const_t self_handle = (kth_transaction_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_TRANSACTION);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_transaction_is_standard(self_handle, (kth_script_flags_t)flags);
    return PyBool_FromLong((long)result);
}

PyMethodDef kth_py_native_chain_transaction_methods[] = {
    {"chain_transaction_construct_default", (PyCFunction)kth_py_native_chain_transaction_construct_default, METH_NOARGS, NULL},
    {"chain_transaction_construct_from_data", (PyCFunction)kth_py_native_chain_transaction_construct_from_data, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_transaction_construct_from_version_locktime_inputs_outputs", (PyCFunction)kth_py_native_chain_transaction_construct_from_version_locktime_inputs_outputs, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_transaction_construct_from_transaction_hash", (PyCFunction)kth_py_native_chain_transaction_construct_from_transaction_hash, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_transaction_copy", (PyCFunction)kth_py_native_chain_transaction_copy, METH_O, NULL},
    {"chain_transaction_destruct", (PyCFunction)kth_py_native_chain_transaction_destruct, METH_O, NULL},
    {"chain_transaction_to_data", (PyCFunction)kth_py_native_chain_transaction_to_data, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_transaction_serialized_size", (PyCFunction)kth_py_native_chain_transaction_serialized_size, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_transaction_set_version", (PyCFunction)kth_py_native_chain_transaction_set_version, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_transaction_set_locktime", (PyCFunction)kth_py_native_chain_transaction_set_locktime, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_transaction_set_inputs", (PyCFunction)kth_py_native_chain_transaction_set_inputs, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_transaction_set_outputs", (PyCFunction)kth_py_native_chain_transaction_set_outputs, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_transaction_outputs_hash", (PyCFunction)kth_py_native_chain_transaction_outputs_hash, METH_O, NULL},
    {"chain_transaction_inpoints_hash", (PyCFunction)kth_py_native_chain_transaction_inpoints_hash, METH_O, NULL},
    {"chain_transaction_sequences_hash", (PyCFunction)kth_py_native_chain_transaction_sequences_hash, METH_O, NULL},
    {"chain_transaction_utxos_hash", (PyCFunction)kth_py_native_chain_transaction_utxos_hash, METH_O, NULL},
    {"chain_transaction_hash", (PyCFunction)kth_py_native_chain_transaction_hash, METH_O, NULL},
    {"chain_transaction_recompute_hash", (PyCFunction)kth_py_native_chain_transaction_recompute_hash, METH_O, NULL},
    {"chain_transaction_fees", (PyCFunction)kth_py_native_chain_transaction_fees, METH_O, NULL},
    {"chain_transaction_total_input_value", (PyCFunction)kth_py_native_chain_transaction_total_input_value, METH_O, NULL},
    {"chain_transaction_total_output_value", (PyCFunction)kth_py_native_chain_transaction_total_output_value, METH_O, NULL},
    {"chain_transaction_signature_operations_simple", (PyCFunction)kth_py_native_chain_transaction_signature_operations_simple, METH_O, NULL},
    {"chain_transaction_is_overspent", (PyCFunction)kth_py_native_chain_transaction_is_overspent, METH_O, NULL},
    {"chain_transaction_check", (PyCFunction)kth_py_native_chain_transaction_check, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_transaction_accept", (PyCFunction)kth_py_native_chain_transaction_accept, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_transaction_connect_simple", (PyCFunction)kth_py_native_chain_transaction_connect_simple, METH_O, NULL},
    {"chain_transaction_connect", (PyCFunction)kth_py_native_chain_transaction_connect, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_transaction_connect_input", (PyCFunction)kth_py_native_chain_transaction_connect_input, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_transaction_reset", (PyCFunction)kth_py_native_chain_transaction_reset, METH_O, NULL},
    {"chain_transaction_equals", (PyCFunction)kth_py_native_chain_transaction_equals, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_transaction_is_valid", (PyCFunction)kth_py_native_chain_transaction_is_valid, METH_O, NULL},
    {"chain_transaction_version", (PyCFunction)kth_py_native_chain_transaction_version, METH_O, NULL},
    {"chain_transaction_locktime", (PyCFunction)kth_py_native_chain_transaction_locktime, METH_O, NULL},
    {"chain_transaction_inputs", (PyCFunction)kth_py_native_chain_transaction_inputs, METH_O, NULL},
    {"chain_transaction_outputs", (PyCFunction)kth_py_native_chain_transaction_outputs, METH_O, NULL},
    {"chain_transaction_previous_outputs", (PyCFunction)kth_py_native_chain_transaction_previous_outputs, METH_O, NULL},
    {"chain_transaction_missing_previous_outputs", (PyCFunction)kth_py_native_chain_transaction_missing_previous_outputs, METH_O, NULL},
    {"chain_transaction_missing_previous_transactions", (PyCFunction)kth_py_native_chain_transaction_missing_previous_transactions, METH_O, NULL},
    {"chain_transaction_signature_operations", (PyCFunction)kth_py_native_chain_transaction_signature_operations, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_transaction_is_coinbase", (PyCFunction)kth_py_native_chain_transaction_is_coinbase, METH_O, NULL},
    {"chain_transaction_is_null_non_coinbase", (PyCFunction)kth_py_native_chain_transaction_is_null_non_coinbase, METH_O, NULL},
    {"chain_transaction_is_oversized_coinbase", (PyCFunction)kth_py_native_chain_transaction_is_oversized_coinbase, METH_O, NULL},
    {"chain_transaction_is_mature", (PyCFunction)kth_py_native_chain_transaction_is_mature, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_transaction_is_internal_double_spend", (PyCFunction)kth_py_native_chain_transaction_is_internal_double_spend, METH_O, NULL},
    {"chain_transaction_is_double_spend", (PyCFunction)kth_py_native_chain_transaction_is_double_spend, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_transaction_is_dusty", (PyCFunction)kth_py_native_chain_transaction_is_dusty, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_transaction_is_missing_previous_outputs", (PyCFunction)kth_py_native_chain_transaction_is_missing_previous_outputs, METH_O, NULL},
    {"chain_transaction_is_final", (PyCFunction)kth_py_native_chain_transaction_is_final, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_transaction_is_locked", (PyCFunction)kth_py_native_chain_transaction_is_locked, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_transaction_is_locktime_conflict", (PyCFunction)kth_py_native_chain_transaction_is_locktime_conflict, METH_O, NULL},
    {"chain_transaction_min_tx_size", (PyCFunction)kth_py_native_chain_transaction_min_tx_size, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_transaction_is_standard_simple", (PyCFunction)kth_py_native_chain_transaction_is_standard_simple, METH_O, NULL},
    {"chain_transaction_is_standard", (PyCFunction)kth_py_native_chain_transaction_is_standard, METH_VARARGS | METH_KEYWORDS, NULL},
    {NULL, NULL, 0, NULL}  // sentinel
};

#ifdef __cplusplus
} // extern "C"
#endif
