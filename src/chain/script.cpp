// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/py-native/chain/script.h>

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
void kth_py_native_chain_script_capsule_dtor(PyObject* capsule) {
    if ( ! PyCapsule_IsValid(capsule, KTH_PY_CAPSULE_CHAIN_SCRIPT)) return;
    kth_script_mut_t handle = (kth_script_mut_t)PyCapsule_GetPointer(capsule, KTH_PY_CAPSULE_CHAIN_SCRIPT);
    if (handle != NULL) kth_chain_script_destruct(handle);
}

PyObject*
kth_py_native_chain_script_construct_default(PyObject* self, PyObject* Py_UNUSED(args)) {
    auto const result = kth_chain_script_construct_default();
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_SCRIPT, kth_py_native_chain_script_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_script_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_script_construct_from_data(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"reader", (char*)"wire", NULL};
    char const* reader_buf = NULL;
    Py_ssize_t reader_size = 0;
    int wire = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "y#p", kwlist, &reader_buf, &reader_size, &wire)) {
        return NULL;
    }
    kth_script_mut_t out = NULL;
    kth_error_code_t result = kth_chain_script_construct_from_data((uint8_t const*)reader_buf, (kth_size_t)reader_size, (kth_bool_t)wire, &out);
    if (result != kth_ec_success) {
        PyErr_Format(PyExc_RuntimeError, "kth error code %d", (int)result);
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)out, KTH_PY_CAPSULE_CHAIN_SCRIPT, kth_py_native_chain_script_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_script_destruct(out);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_script_construct_from_operations(PyObject* self, PyObject* py_arg0) {
    PyObject* py_ops = py_arg0;
    kth_operation_list_const_t ops_handle = (kth_operation_list_const_t)PyCapsule_GetPointer(py_ops, KTH_PY_CAPSULE_CHAIN_OPERATION_LIST);
    if (ops_handle == NULL) return NULL;
    auto const result = kth_chain_script_construct_from_operations(ops_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_SCRIPT, kth_py_native_chain_script_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_script_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_script_construct_from_encoded_prefix(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"encoded", (char*)"prefix", NULL};
    char const* encoded_buf = NULL;
    Py_ssize_t encoded_size = 0;
    int prefix = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "y#p", kwlist, &encoded_buf, &encoded_size, &prefix)) {
        return NULL;
    }
    auto const result = kth_chain_script_construct_from_encoded_prefix((uint8_t const*)encoded_buf, (kth_size_t)encoded_size, (kth_bool_t)prefix);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_SCRIPT, kth_py_native_chain_script_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_script_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_script_copy(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_script_const_t self_handle = (kth_script_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_SCRIPT);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_script_copy(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_SCRIPT, kth_py_native_chain_script_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_script_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_script_destruct(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_script_mut_t self_handle = (kth_script_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_SCRIPT);
    if (self_handle == NULL) return NULL;
    kth_chain_script_destruct(self_handle);
    PyCapsule_SetName(py_self, "kth.destroyed");
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_script_from_data_with_size(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"reader", (char*)"size", NULL};
    char const* reader_buf = NULL;
    Py_ssize_t reader_size = 0;
    Py_ssize_t size = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "y#n", kwlist, &reader_buf, &reader_size, &size)) {
        return NULL;
    }
    if (size < 0) {
        PyErr_Format(PyExc_ValueError, "size must be non-negative, got %zd", size);
        return NULL;
    }
    kth_script_mut_t out = NULL;
    kth_error_code_t result = kth_chain_script_from_data_with_size((uint8_t const*)reader_buf, (kth_size_t)reader_size, (kth_size_t)size, &out);
    if (result != kth_ec_success) {
        PyErr_Format(PyExc_RuntimeError, "kth error code %d", (int)result);
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)out, KTH_PY_CAPSULE_CHAIN_SCRIPT, kth_py_native_chain_script_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_script_destruct(out);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_script_from_operations(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"ops", NULL};
    PyObject* py_self = NULL;
    PyObject* py_ops = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_ops)) {
        return NULL;
    }
    kth_script_mut_t self_handle = (kth_script_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_SCRIPT);
    if (self_handle == NULL) return NULL;
    kth_operation_list_const_t ops_handle = (kth_operation_list_const_t)PyCapsule_GetPointer(py_ops, KTH_PY_CAPSULE_CHAIN_OPERATION_LIST);
    if (ops_handle == NULL) return NULL;
    kth_chain_script_from_operations(self_handle, ops_handle);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_script_from_string(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"mnemonic", NULL};
    PyObject* py_self = NULL;
    char const* mnemonic = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Os", kwlist, &py_self, &mnemonic)) {
        return NULL;
    }
    kth_script_mut_t self_handle = (kth_script_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_SCRIPT);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_script_from_string(self_handle, mnemonic);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_script_is_valid_operations(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_script_const_t self_handle = (kth_script_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_SCRIPT);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_script_is_valid_operations(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_script_to_string(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"active_flags", NULL};
    PyObject* py_self = NULL;
    unsigned long long active_flags = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OK", kwlist, &py_self, &active_flags)) {
        return NULL;
    }
    kth_script_const_t self_handle = (kth_script_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_SCRIPT);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_script_to_string(self_handle, (kth_script_flags_t)active_flags);
    if (result == NULL) Py_RETURN_NONE;
    PyObject* py_result = Py_BuildValue("s", result);
    kth_core_destruct_string(result);
    return py_result;
}

PyObject*
kth_py_native_chain_script_clear(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_script_mut_t self_handle = (kth_script_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_SCRIPT);
    if (self_handle == NULL) return NULL;
    kth_chain_script_clear(self_handle);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_script_empty(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_script_const_t self_handle = (kth_script_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_SCRIPT);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_script_empty(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_script_size(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_script_const_t self_handle = (kth_script_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_SCRIPT);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_script_size(self_handle);
    return PyLong_FromSize_t((size_t)result);
}

PyObject*
kth_py_native_chain_script_front(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_script_const_t self_handle = (kth_script_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_SCRIPT);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_script_front(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_OPERATION, kth_py_native_borrowed_parent_dtor);
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
kth_py_native_chain_script_back(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_script_const_t self_handle = (kth_script_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_SCRIPT);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_script_back(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_OPERATION, kth_py_native_borrowed_parent_dtor);
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
kth_py_native_chain_script_at(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"index", NULL};
    PyObject* py_self = NULL;
    Py_ssize_t index = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "On", kwlist, &py_self, &index)) {
        return NULL;
    }
    kth_script_const_t self_handle = (kth_script_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_SCRIPT);
    if (self_handle == NULL) return NULL;
    if (index < 0) {
        PyErr_Format(PyExc_ValueError, "index must be non-negative, got %zd", index);
        return NULL;
    }
    auto const result = kth_chain_script_at(self_handle, (kth_size_t)index);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_OPERATION, kth_py_native_borrowed_parent_dtor);
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
kth_py_native_chain_script_operations(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_script_const_t self_handle = (kth_script_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_SCRIPT);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_script_operations(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL list returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_OPERATION_LIST, kth_py_native_borrowed_parent_dtor);
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
kth_py_native_chain_script_first_operation(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_script_const_t self_handle = (kth_script_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_SCRIPT);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_script_first_operation(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
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
kth_py_native_chain_script_create_endorsement(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"secret", (char*)"prevout_script", (char*)"tx", (char*)"input_index", (char*)"sighash_type", (char*)"active_flags", (char*)"value", (char*)"type", NULL};
    char const* secret_buf = NULL;
    Py_ssize_t secret_size = 0;
    PyObject* py_prevout_script = NULL;
    PyObject* py_tx = NULL;
    unsigned int input_index = 0;
    unsigned char sighash_type = 0;
    unsigned long long active_flags = 0;
    unsigned long long value = 0;
    unsigned long long type = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "y#OOIBKKK", kwlist, &secret_buf, &secret_size, &py_prevout_script, &py_tx, &input_index, &sighash_type, &active_flags, &value, &type)) {
        return NULL;
    }
    if (secret_size != (Py_ssize_t)KTH_BITCOIN_HASH_SIZE) {
        PyErr_Format(PyExc_ValueError, "expected %d-byte secret, got %zd", (int)KTH_BITCOIN_HASH_SIZE, secret_size);
        return NULL;
    }
    kth_hash_t secret;
    memcpy(secret.hash, secret_buf, (size_t)KTH_BITCOIN_HASH_SIZE);
    kth_script_const_t prevout_script_handle = (kth_script_const_t)PyCapsule_GetPointer(py_prevout_script, KTH_PY_CAPSULE_CHAIN_SCRIPT);
    if (prevout_script_handle == NULL) return NULL;
    kth_transaction_const_t tx_handle = (kth_transaction_const_t)PyCapsule_GetPointer(py_tx, KTH_PY_CAPSULE_CHAIN_TRANSACTION);
    if (tx_handle == NULL) return NULL;
    uint8_t* out = NULL;
    kth_size_t out_size = 0;
    kth_error_code_t result = kth_chain_script_create_endorsement(&secret, prevout_script_handle, tx_handle, (uint32_t)input_index, (uint8_t)sighash_type, (kth_script_flags_t)active_flags, (uint64_t)value, (kth_endorsement_type_t)type, &out, &out_size);
    kth_core_secure_zero((void*)&secret, sizeof(kth_hash_t));
    if (result != kth_ec_success) {
        PyErr_Format(PyExc_RuntimeError, "kth error code %d", (int)result);
        return NULL;
    }
    PyObject* py_result = Py_BuildValue("y#", out, (Py_ssize_t)out_size);
    kth_core_destruct_array(out);
    return py_result;
}

PyObject*
kth_py_native_chain_script_is_push_only(PyObject* self, PyObject* py_arg0) {
    PyObject* py_ops = py_arg0;
    kth_operation_list_const_t ops_handle = (kth_operation_list_const_t)PyCapsule_GetPointer(py_ops, KTH_PY_CAPSULE_CHAIN_OPERATION_LIST);
    if (ops_handle == NULL) return NULL;
    auto const result = kth_chain_script_is_push_only(ops_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_script_is_relaxed_push(PyObject* self, PyObject* py_arg0) {
    PyObject* py_ops = py_arg0;
    kth_operation_list_const_t ops_handle = (kth_operation_list_const_t)PyCapsule_GetPointer(py_ops, KTH_PY_CAPSULE_CHAIN_OPERATION_LIST);
    if (ops_handle == NULL) return NULL;
    auto const result = kth_chain_script_is_relaxed_push(ops_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_script_is_coinbase_pattern(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"ops", (char*)"height", NULL};
    PyObject* py_ops = NULL;
    Py_ssize_t height = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "On", kwlist, &py_ops, &height)) {
        return NULL;
    }
    kth_operation_list_const_t ops_handle = (kth_operation_list_const_t)PyCapsule_GetPointer(py_ops, KTH_PY_CAPSULE_CHAIN_OPERATION_LIST);
    if (ops_handle == NULL) return NULL;
    if (height < 0) {
        PyErr_Format(PyExc_ValueError, "height must be non-negative, got %zd", height);
        return NULL;
    }
    auto const result = kth_chain_script_is_coinbase_pattern(ops_handle, (kth_size_t)height);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_script_is_null_data_pattern(PyObject* self, PyObject* py_arg0) {
    PyObject* py_ops = py_arg0;
    kth_operation_list_const_t ops_handle = (kth_operation_list_const_t)PyCapsule_GetPointer(py_ops, KTH_PY_CAPSULE_CHAIN_OPERATION_LIST);
    if (ops_handle == NULL) return NULL;
    auto const result = kth_chain_script_is_null_data_pattern(ops_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_script_is_pay_multisig_pattern(PyObject* self, PyObject* py_arg0) {
    PyObject* py_ops = py_arg0;
    kth_operation_list_const_t ops_handle = (kth_operation_list_const_t)PyCapsule_GetPointer(py_ops, KTH_PY_CAPSULE_CHAIN_OPERATION_LIST);
    if (ops_handle == NULL) return NULL;
    auto const result = kth_chain_script_is_pay_multisig_pattern(ops_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_script_is_pay_public_key_pattern(PyObject* self, PyObject* py_arg0) {
    PyObject* py_ops = py_arg0;
    kth_operation_list_const_t ops_handle = (kth_operation_list_const_t)PyCapsule_GetPointer(py_ops, KTH_PY_CAPSULE_CHAIN_OPERATION_LIST);
    if (ops_handle == NULL) return NULL;
    auto const result = kth_chain_script_is_pay_public_key_pattern(ops_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_script_is_pay_public_key_hash_pattern(PyObject* self, PyObject* py_arg0) {
    PyObject* py_ops = py_arg0;
    kth_operation_list_const_t ops_handle = (kth_operation_list_const_t)PyCapsule_GetPointer(py_ops, KTH_PY_CAPSULE_CHAIN_OPERATION_LIST);
    if (ops_handle == NULL) return NULL;
    auto const result = kth_chain_script_is_pay_public_key_hash_pattern(ops_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_script_is_pay_script_hash_pattern(PyObject* self, PyObject* py_arg0) {
    PyObject* py_ops = py_arg0;
    kth_operation_list_const_t ops_handle = (kth_operation_list_const_t)PyCapsule_GetPointer(py_ops, KTH_PY_CAPSULE_CHAIN_OPERATION_LIST);
    if (ops_handle == NULL) return NULL;
    auto const result = kth_chain_script_is_pay_script_hash_pattern(ops_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_script_is_pay_script_hash_32_pattern(PyObject* self, PyObject* py_arg0) {
    PyObject* py_ops = py_arg0;
    kth_operation_list_const_t ops_handle = (kth_operation_list_const_t)PyCapsule_GetPointer(py_ops, KTH_PY_CAPSULE_CHAIN_OPERATION_LIST);
    if (ops_handle == NULL) return NULL;
    auto const result = kth_chain_script_is_pay_script_hash_32_pattern(ops_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_script_is_sign_multisig_pattern(PyObject* self, PyObject* py_arg0) {
    PyObject* py_ops = py_arg0;
    kth_operation_list_const_t ops_handle = (kth_operation_list_const_t)PyCapsule_GetPointer(py_ops, KTH_PY_CAPSULE_CHAIN_OPERATION_LIST);
    if (ops_handle == NULL) return NULL;
    auto const result = kth_chain_script_is_sign_multisig_pattern(ops_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_script_is_sign_public_key_pattern(PyObject* self, PyObject* py_arg0) {
    PyObject* py_ops = py_arg0;
    kth_operation_list_const_t ops_handle = (kth_operation_list_const_t)PyCapsule_GetPointer(py_ops, KTH_PY_CAPSULE_CHAIN_OPERATION_LIST);
    if (ops_handle == NULL) return NULL;
    auto const result = kth_chain_script_is_sign_public_key_pattern(ops_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_script_is_sign_public_key_hash_pattern(PyObject* self, PyObject* py_arg0) {
    PyObject* py_ops = py_arg0;
    kth_operation_list_const_t ops_handle = (kth_operation_list_const_t)PyCapsule_GetPointer(py_ops, KTH_PY_CAPSULE_CHAIN_OPERATION_LIST);
    if (ops_handle == NULL) return NULL;
    auto const result = kth_chain_script_is_sign_public_key_hash_pattern(ops_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_script_is_sign_script_hash_pattern(PyObject* self, PyObject* py_arg0) {
    PyObject* py_ops = py_arg0;
    kth_operation_list_const_t ops_handle = (kth_operation_list_const_t)PyCapsule_GetPointer(py_ops, KTH_PY_CAPSULE_CHAIN_OPERATION_LIST);
    if (ops_handle == NULL) return NULL;
    auto const result = kth_chain_script_is_sign_script_hash_pattern(ops_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_script_to_null_data_pattern(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"data", NULL};
    char const* data_buf = NULL;
    Py_ssize_t data_size = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "y#", kwlist, &data_buf, &data_size)) {
        return NULL;
    }
    auto const result = kth_chain_script_to_null_data_pattern((uint8_t const*)data_buf, (kth_size_t)data_size);
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
kth_py_native_chain_script_to_pay_public_key_pattern(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"point", NULL};
    char const* point_buf = NULL;
    Py_ssize_t point_size = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "y#", kwlist, &point_buf, &point_size)) {
        return NULL;
    }
    auto const result = kth_chain_script_to_pay_public_key_pattern((uint8_t const*)point_buf, (kth_size_t)point_size);
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
kth_py_native_chain_script_to_pay_public_key_hash_pattern(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"hash", NULL};
    char const* hash_buf = NULL;
    Py_ssize_t hash_size = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "y#", kwlist, &hash_buf, &hash_size)) {
        return NULL;
    }
    if (hash_size != (Py_ssize_t)KTH_BITCOIN_SHORT_HASH_SIZE) {
        PyErr_Format(PyExc_ValueError, "expected %d-byte hash, got %zd", (int)KTH_BITCOIN_SHORT_HASH_SIZE, hash_size);
        return NULL;
    }
    kth_shorthash_t hash;
    memcpy(hash.hash, hash_buf, (size_t)KTH_BITCOIN_SHORT_HASH_SIZE);
    auto const result = kth_chain_script_to_pay_public_key_hash_pattern(&hash);
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
kth_py_native_chain_script_to_pay_public_key_hash_pattern_unlocking(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"end", (char*)"pubkey", NULL};
    char const* end_buf = NULL;
    Py_ssize_t end_size = 0;
    PyObject* py_pubkey = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "y#O", kwlist, &end_buf, &end_size, &py_pubkey)) {
        return NULL;
    }
    kth_ec_public_const_t pubkey_handle = (kth_ec_public_const_t)PyCapsule_GetPointer(py_pubkey, KTH_PY_CAPSULE_WALLET_EC_PUBLIC);
    if (pubkey_handle == NULL) return NULL;
    auto const result = kth_chain_script_to_pay_public_key_hash_pattern_unlocking((uint8_t const*)end_buf, (kth_size_t)end_size, pubkey_handle);
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
kth_py_native_chain_script_to_pay_public_key_hash_pattern_unlocking_placeholder(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"endorsement_size", (char*)"pubkey_size", NULL};
    Py_ssize_t endorsement_size = 0;
    Py_ssize_t pubkey_size = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "nn", kwlist, &endorsement_size, &pubkey_size)) {
        return NULL;
    }
    if (endorsement_size < 0) {
        PyErr_Format(PyExc_ValueError, "endorsement_size must be non-negative, got %zd", endorsement_size);
        return NULL;
    }
    if (pubkey_size < 0) {
        PyErr_Format(PyExc_ValueError, "pubkey_size must be non-negative, got %zd", pubkey_size);
        return NULL;
    }
    auto const result = kth_chain_script_to_pay_public_key_hash_pattern_unlocking_placeholder((kth_size_t)endorsement_size, (kth_size_t)pubkey_size);
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
kth_py_native_chain_script_to_pay_script_hash_pattern_unlocking_placeholder(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"script_size", (char*)"multisig", NULL};
    Py_ssize_t script_size = 0;
    int multisig = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "np", kwlist, &script_size, &multisig)) {
        return NULL;
    }
    if (script_size < 0) {
        PyErr_Format(PyExc_ValueError, "script_size must be non-negative, got %zd", script_size);
        return NULL;
    }
    auto const result = kth_chain_script_to_pay_script_hash_pattern_unlocking_placeholder((kth_size_t)script_size, (kth_bool_t)multisig);
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
kth_py_native_chain_script_to_pay_script_hash_pattern(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"hash", NULL};
    char const* hash_buf = NULL;
    Py_ssize_t hash_size = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "y#", kwlist, &hash_buf, &hash_size)) {
        return NULL;
    }
    if (hash_size != (Py_ssize_t)KTH_BITCOIN_SHORT_HASH_SIZE) {
        PyErr_Format(PyExc_ValueError, "expected %d-byte hash, got %zd", (int)KTH_BITCOIN_SHORT_HASH_SIZE, hash_size);
        return NULL;
    }
    kth_shorthash_t hash;
    memcpy(hash.hash, hash_buf, (size_t)KTH_BITCOIN_SHORT_HASH_SIZE);
    auto const result = kth_chain_script_to_pay_script_hash_pattern(&hash);
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
kth_py_native_chain_script_to_pay_script_hash_32_pattern(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"hash", NULL};
    char const* hash_buf = NULL;
    Py_ssize_t hash_size = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "y#", kwlist, &hash_buf, &hash_size)) {
        return NULL;
    }
    if (hash_size != (Py_ssize_t)KTH_BITCOIN_HASH_SIZE) {
        PyErr_Format(PyExc_ValueError, "expected %d-byte hash, got %zd", (int)KTH_BITCOIN_HASH_SIZE, hash_size);
        return NULL;
    }
    kth_hash_t hash;
    memcpy(hash.hash, hash_buf, (size_t)KTH_BITCOIN_HASH_SIZE);
    auto const result = kth_chain_script_to_pay_script_hash_32_pattern(&hash);
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
kth_py_native_chain_script_to_pay_multisig_pattern_ec_compressed_list(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"signatures", (char*)"points", NULL};
    unsigned char signatures = 0;
    PyObject* py_points = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "BO", kwlist, &signatures, &py_points)) {
        return NULL;
    }
    kth_ec_compressed_list_const_t points_handle = (kth_ec_compressed_list_const_t)PyCapsule_GetPointer(py_points, KTH_PY_CAPSULE_WALLET_EC_COMPRESSED_LIST);
    if (points_handle == NULL) return NULL;
    auto const result = kth_chain_script_to_pay_multisig_pattern_ec_compressed_list((uint8_t)signatures, points_handle);
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
kth_py_native_chain_script_to_pay_multisig_pattern_data_stack(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"signatures", (char*)"points", NULL};
    unsigned char signatures = 0;
    PyObject* py_points = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "BO", kwlist, &signatures, &py_points)) {
        return NULL;
    }
    kth_data_stack_const_t points_handle = (kth_data_stack_const_t)PyCapsule_GetPointer(py_points, KTH_PY_CAPSULE_CHAIN_DATA_STACK);
    if (points_handle == NULL) return NULL;
    auto const result = kth_chain_script_to_pay_multisig_pattern_data_stack((uint8_t)signatures, points_handle);
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
kth_py_native_chain_script_pattern(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_script_const_t self_handle = (kth_script_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_SCRIPT);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_script_pattern(self_handle);
    return PyLong_FromLong((long)result);
}

PyObject*
kth_py_native_chain_script_output_pattern_simple(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_script_const_t self_handle = (kth_script_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_SCRIPT);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_script_output_pattern_simple(self_handle);
    return PyLong_FromLong((long)result);
}

PyObject*
kth_py_native_chain_script_output_pattern(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"flags", NULL};
    PyObject* py_self = NULL;
    unsigned long long flags = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OK", kwlist, &py_self, &flags)) {
        return NULL;
    }
    kth_script_const_t self_handle = (kth_script_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_SCRIPT);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_script_output_pattern(self_handle, (kth_script_flags_t)flags);
    return PyLong_FromLong((long)result);
}

PyObject*
kth_py_native_chain_script_input_pattern(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_script_const_t self_handle = (kth_script_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_SCRIPT);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_script_input_pattern(self_handle);
    return PyLong_FromLong((long)result);
}

PyObject*
kth_py_native_chain_script_sigops(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"accurate", NULL};
    PyObject* py_self = NULL;
    int accurate = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Op", kwlist, &py_self, &accurate)) {
        return NULL;
    }
    kth_script_const_t self_handle = (kth_script_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_SCRIPT);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_script_sigops(self_handle, (kth_bool_t)accurate);
    return PyLong_FromSize_t((size_t)result);
}

PyObject*
kth_py_native_chain_script_is_unspendable(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_script_const_t self_handle = (kth_script_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_SCRIPT);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_script_is_unspendable(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_script_reset(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_script_mut_t self_handle = (kth_script_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_SCRIPT);
    if (self_handle == NULL) return NULL;
    kth_chain_script_reset(self_handle);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_script_is_pay_to_script_hash(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"flags", NULL};
    PyObject* py_self = NULL;
    unsigned long long flags = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OK", kwlist, &py_self, &flags)) {
        return NULL;
    }
    kth_script_const_t self_handle = (kth_script_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_SCRIPT);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_script_is_pay_to_script_hash(self_handle, (kth_script_flags_t)flags);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_script_is_pay_to_script_hash_32(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"flags", NULL};
    PyObject* py_self = NULL;
    unsigned long long flags = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OK", kwlist, &py_self, &flags)) {
        return NULL;
    }
    kth_script_const_t self_handle = (kth_script_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_SCRIPT);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_script_is_pay_to_script_hash_32(self_handle, (kth_script_flags_t)flags);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_script_verify(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"tx", (char*)"input_index", (char*)"flags", (char*)"input_script", (char*)"prevout_script", (char*)"value", NULL};
    PyObject* py_tx = NULL;
    unsigned int input_index = 0;
    unsigned long long flags = 0;
    PyObject* py_input_script = NULL;
    PyObject* py_prevout_script = NULL;
    unsigned long long value = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OIKOOK", kwlist, &py_tx, &input_index, &flags, &py_input_script, &py_prevout_script, &value)) {
        return NULL;
    }
    kth_transaction_const_t tx_handle = (kth_transaction_const_t)PyCapsule_GetPointer(py_tx, KTH_PY_CAPSULE_CHAIN_TRANSACTION);
    if (tx_handle == NULL) return NULL;
    kth_script_const_t input_script_handle = (kth_script_const_t)PyCapsule_GetPointer(py_input_script, KTH_PY_CAPSULE_CHAIN_SCRIPT);
    if (input_script_handle == NULL) return NULL;
    kth_script_const_t prevout_script_handle = (kth_script_const_t)PyCapsule_GetPointer(py_prevout_script, KTH_PY_CAPSULE_CHAIN_SCRIPT);
    if (prevout_script_handle == NULL) return NULL;
    auto const result = kth_chain_script_verify(tx_handle, (uint32_t)input_index, (kth_script_flags_t)flags, input_script_handle, prevout_script_handle, (uint64_t)value);
    return PyLong_FromLong((long)result);
}

PyObject*
kth_py_native_chain_script_verify_simple(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"tx", (char*)"input", (char*)"flags", NULL};
    PyObject* py_tx = NULL;
    unsigned int input = 0;
    unsigned long long flags = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OIK", kwlist, &py_tx, &input, &flags)) {
        return NULL;
    }
    kth_transaction_const_t tx_handle = (kth_transaction_const_t)PyCapsule_GetPointer(py_tx, KTH_PY_CAPSULE_CHAIN_TRANSACTION);
    if (tx_handle == NULL) return NULL;
    auto const result = kth_chain_script_verify_simple(tx_handle, (uint32_t)input, (kth_script_flags_t)flags);
    return PyLong_FromLong((long)result);
}

PyObject*
kth_py_native_chain_script_equals(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"other", NULL};
    PyObject* py_self = NULL;
    PyObject* py_other = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_other)) {
        return NULL;
    }
    kth_script_const_t self_handle = (kth_script_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_SCRIPT);
    if (self_handle == NULL) return NULL;
    kth_script_const_t other_handle = (kth_script_const_t)PyCapsule_GetPointer(py_other, KTH_PY_CAPSULE_CHAIN_SCRIPT);
    if (other_handle == NULL) return NULL;
    auto const result = kth_chain_script_equals(self_handle, other_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_script_is_valid(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_script_const_t self_handle = (kth_script_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_SCRIPT);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_script_is_valid(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_script_to_data(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"prefix", NULL};
    PyObject* py_self = NULL;
    int prefix = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Op", kwlist, &py_self, &prefix)) {
        return NULL;
    }
    kth_script_const_t self_handle = (kth_script_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_SCRIPT);
    if (self_handle == NULL) return NULL;
    kth_size_t out_size = 0;
    auto const result = kth_chain_script_to_data(self_handle, (kth_bool_t)prefix, &out_size);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: serialization failed");
        return NULL;
    }
    PyObject* py_result = Py_BuildValue("y#", result, (Py_ssize_t)out_size);
    kth_core_destruct_array(result);
    return py_result;
}

PyObject*
kth_py_native_chain_script_serialized_size(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"prefix", NULL};
    PyObject* py_self = NULL;
    int prefix = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Op", kwlist, &py_self, &prefix)) {
        return NULL;
    }
    kth_script_const_t self_handle = (kth_script_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_SCRIPT);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_script_serialized_size(self_handle, (kth_bool_t)prefix);
    return PyLong_FromSize_t((size_t)result);
}

PyObject*
kth_py_native_chain_script_bytes(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_script_const_t self_handle = (kth_script_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_SCRIPT);
    if (self_handle == NULL) return NULL;
    kth_size_t out_size = 0;
    auto const result = kth_chain_script_bytes(self_handle, &out_size);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: serialization failed");
        return NULL;
    }
    PyObject* py_result = Py_BuildValue("y#", result, (Py_ssize_t)out_size);
    kth_core_destruct_array(result);
    return py_result;
}

PyObject*
kth_py_native_chain_script_is_enabled(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"active_flags", (char*)"fork", NULL};
    unsigned long long active_flags = 0;
    unsigned long long fork = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "KK", kwlist, &active_flags, &fork)) {
        return NULL;
    }
    auto const result = kth_chain_script_is_enabled((kth_script_flags_t)active_flags, (kth_script_flags_t)fork);
    return PyBool_FromLong((long)result);
}

PyMethodDef kth_py_native_chain_script_methods[] = {
    {"chain_script_construct_default", (PyCFunction)kth_py_native_chain_script_construct_default, METH_NOARGS, NULL},
    {"chain_script_construct_from_data", (PyCFunction)kth_py_native_chain_script_construct_from_data, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_script_construct_from_operations", (PyCFunction)kth_py_native_chain_script_construct_from_operations, METH_O, NULL},
    {"chain_script_construct_from_encoded_prefix", (PyCFunction)kth_py_native_chain_script_construct_from_encoded_prefix, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_script_copy", (PyCFunction)kth_py_native_chain_script_copy, METH_O, NULL},
    {"chain_script_destruct", (PyCFunction)kth_py_native_chain_script_destruct, METH_O, NULL},
    {"chain_script_from_data_with_size", (PyCFunction)kth_py_native_chain_script_from_data_with_size, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_script_from_operations", (PyCFunction)kth_py_native_chain_script_from_operations, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_script_from_string", (PyCFunction)kth_py_native_chain_script_from_string, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_script_is_valid_operations", (PyCFunction)kth_py_native_chain_script_is_valid_operations, METH_O, NULL},
    {"chain_script_to_string", (PyCFunction)kth_py_native_chain_script_to_string, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_script_clear", (PyCFunction)kth_py_native_chain_script_clear, METH_O, NULL},
    {"chain_script_empty", (PyCFunction)kth_py_native_chain_script_empty, METH_O, NULL},
    {"chain_script_size", (PyCFunction)kth_py_native_chain_script_size, METH_O, NULL},
    {"chain_script_front", (PyCFunction)kth_py_native_chain_script_front, METH_O, NULL},
    {"chain_script_back", (PyCFunction)kth_py_native_chain_script_back, METH_O, NULL},
    {"chain_script_at", (PyCFunction)kth_py_native_chain_script_at, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_script_operations", (PyCFunction)kth_py_native_chain_script_operations, METH_O, NULL},
    {"chain_script_first_operation", (PyCFunction)kth_py_native_chain_script_first_operation, METH_O, NULL},
    {"chain_script_create_endorsement", (PyCFunction)kth_py_native_chain_script_create_endorsement, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_script_is_push_only", (PyCFunction)kth_py_native_chain_script_is_push_only, METH_O, NULL},
    {"chain_script_is_relaxed_push", (PyCFunction)kth_py_native_chain_script_is_relaxed_push, METH_O, NULL},
    {"chain_script_is_coinbase_pattern", (PyCFunction)kth_py_native_chain_script_is_coinbase_pattern, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_script_is_null_data_pattern", (PyCFunction)kth_py_native_chain_script_is_null_data_pattern, METH_O, NULL},
    {"chain_script_is_pay_multisig_pattern", (PyCFunction)kth_py_native_chain_script_is_pay_multisig_pattern, METH_O, NULL},
    {"chain_script_is_pay_public_key_pattern", (PyCFunction)kth_py_native_chain_script_is_pay_public_key_pattern, METH_O, NULL},
    {"chain_script_is_pay_public_key_hash_pattern", (PyCFunction)kth_py_native_chain_script_is_pay_public_key_hash_pattern, METH_O, NULL},
    {"chain_script_is_pay_script_hash_pattern", (PyCFunction)kth_py_native_chain_script_is_pay_script_hash_pattern, METH_O, NULL},
    {"chain_script_is_pay_script_hash_32_pattern", (PyCFunction)kth_py_native_chain_script_is_pay_script_hash_32_pattern, METH_O, NULL},
    {"chain_script_is_sign_multisig_pattern", (PyCFunction)kth_py_native_chain_script_is_sign_multisig_pattern, METH_O, NULL},
    {"chain_script_is_sign_public_key_pattern", (PyCFunction)kth_py_native_chain_script_is_sign_public_key_pattern, METH_O, NULL},
    {"chain_script_is_sign_public_key_hash_pattern", (PyCFunction)kth_py_native_chain_script_is_sign_public_key_hash_pattern, METH_O, NULL},
    {"chain_script_is_sign_script_hash_pattern", (PyCFunction)kth_py_native_chain_script_is_sign_script_hash_pattern, METH_O, NULL},
    {"chain_script_to_null_data_pattern", (PyCFunction)kth_py_native_chain_script_to_null_data_pattern, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_script_to_pay_public_key_pattern", (PyCFunction)kth_py_native_chain_script_to_pay_public_key_pattern, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_script_to_pay_public_key_hash_pattern", (PyCFunction)kth_py_native_chain_script_to_pay_public_key_hash_pattern, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_script_to_pay_public_key_hash_pattern_unlocking", (PyCFunction)kth_py_native_chain_script_to_pay_public_key_hash_pattern_unlocking, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_script_to_pay_public_key_hash_pattern_unlocking_placeholder", (PyCFunction)kth_py_native_chain_script_to_pay_public_key_hash_pattern_unlocking_placeholder, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_script_to_pay_script_hash_pattern_unlocking_placeholder", (PyCFunction)kth_py_native_chain_script_to_pay_script_hash_pattern_unlocking_placeholder, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_script_to_pay_script_hash_pattern", (PyCFunction)kth_py_native_chain_script_to_pay_script_hash_pattern, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_script_to_pay_script_hash_32_pattern", (PyCFunction)kth_py_native_chain_script_to_pay_script_hash_32_pattern, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_script_to_pay_multisig_pattern_ec_compressed_list", (PyCFunction)kth_py_native_chain_script_to_pay_multisig_pattern_ec_compressed_list, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_script_to_pay_multisig_pattern_data_stack", (PyCFunction)kth_py_native_chain_script_to_pay_multisig_pattern_data_stack, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_script_pattern", (PyCFunction)kth_py_native_chain_script_pattern, METH_O, NULL},
    {"chain_script_output_pattern_simple", (PyCFunction)kth_py_native_chain_script_output_pattern_simple, METH_O, NULL},
    {"chain_script_output_pattern", (PyCFunction)kth_py_native_chain_script_output_pattern, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_script_input_pattern", (PyCFunction)kth_py_native_chain_script_input_pattern, METH_O, NULL},
    {"chain_script_sigops", (PyCFunction)kth_py_native_chain_script_sigops, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_script_is_unspendable", (PyCFunction)kth_py_native_chain_script_is_unspendable, METH_O, NULL},
    {"chain_script_reset", (PyCFunction)kth_py_native_chain_script_reset, METH_O, NULL},
    {"chain_script_is_pay_to_script_hash", (PyCFunction)kth_py_native_chain_script_is_pay_to_script_hash, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_script_is_pay_to_script_hash_32", (PyCFunction)kth_py_native_chain_script_is_pay_to_script_hash_32, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_script_verify", (PyCFunction)kth_py_native_chain_script_verify, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_script_verify_simple", (PyCFunction)kth_py_native_chain_script_verify_simple, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_script_equals", (PyCFunction)kth_py_native_chain_script_equals, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_script_is_valid", (PyCFunction)kth_py_native_chain_script_is_valid, METH_O, NULL},
    {"chain_script_to_data", (PyCFunction)kth_py_native_chain_script_to_data, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_script_serialized_size", (PyCFunction)kth_py_native_chain_script_serialized_size, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_script_bytes", (PyCFunction)kth_py_native_chain_script_bytes, METH_O, NULL},
    {"chain_script_is_enabled", (PyCFunction)kth_py_native_chain_script_is_enabled, METH_VARARGS | METH_KEYWORDS, NULL},
    {NULL, NULL, 0, NULL}  // sentinel
};

#ifdef __cplusplus
} // extern "C"
#endif
