// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/py-native/chain/block.h>

#include <string.h>
#include <kth/capi.h>
#include <kth/capi/chain/block.h>
#include <kth/py-native/capsule_names.h>
#include <kth/py-native/utils.h>

#ifdef __cplusplus
extern "C" {
#endif

// PyCapsule destructor — released by GC when the capsule is
// collected. Explicit `destruct` calls set the capsule name to
// "kth.destroyed", so PyCapsule_IsValid returns false and this
// destructor becomes a no-op (no double-free).
void kth_py_native_chain_block_capsule_dtor(PyObject* capsule) {
    if ( ! PyCapsule_IsValid(capsule, KTH_PY_CAPSULE_CHAIN_BLOCK)) return;
    kth_block_mut_t handle = (kth_block_mut_t)PyCapsule_GetPointer(capsule, KTH_PY_CAPSULE_CHAIN_BLOCK);
    if (handle != NULL) kth_chain_block_destruct(handle);
}

PyObject*
kth_py_native_chain_block_construct_default(PyObject* self, PyObject* Py_UNUSED(args)) {
    auto const result = kth_chain_block_construct_default();
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_BLOCK, kth_py_native_chain_block_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_block_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_block_construct_from_data(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"reader", (char*)"wire", NULL};
    char const* reader_buf = NULL;
    Py_ssize_t reader_size = 0;
    int wire = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "y#p", kwlist, &reader_buf, &reader_size, &wire)) {
        return NULL;
    }
    kth_block_mut_t out = NULL;
    kth_error_code_t result = kth_chain_block_construct_from_data((uint8_t const*)reader_buf, (kth_size_t)reader_size, (kth_bool_t)wire, &out);
    if (result != kth_ec_success) {
        PyErr_Format(PyExc_RuntimeError, "kth error code %d", (int)result);
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)out, KTH_PY_CAPSULE_CHAIN_BLOCK, kth_py_native_chain_block_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_block_destruct(out);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_block_construct(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"header", (char*)"transactions", NULL};
    PyObject* py_header = NULL;
    PyObject* py_transactions = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_header, &py_transactions)) {
        return NULL;
    }
    kth_header_const_t header_handle = (kth_header_const_t)PyCapsule_GetPointer(py_header, KTH_PY_CAPSULE_CHAIN_HEADER);
    if (header_handle == NULL) return NULL;
    kth_transaction_list_const_t transactions_handle = (kth_transaction_list_const_t)PyCapsule_GetPointer(py_transactions, KTH_PY_CAPSULE_CHAIN_TRANSACTION_LIST);
    if (transactions_handle == NULL) return NULL;
    auto const result = kth_chain_block_construct(header_handle, transactions_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_BLOCK, kth_py_native_chain_block_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_block_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_block_copy(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_block_const_t self_handle = (kth_block_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_BLOCK);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_block_copy(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_BLOCK, kth_py_native_chain_block_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_block_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_block_destruct(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_block_mut_t self_handle = (kth_block_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_BLOCK);
    if (self_handle == NULL) return NULL;
    kth_chain_block_destruct(self_handle);
    PyCapsule_SetName(py_self, "kth.destroyed");
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_block_to_data_simple(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_block_const_t self_handle = (kth_block_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_BLOCK);
    if (self_handle == NULL) return NULL;
    kth_size_t out_size = 0;
    auto const result = kth_chain_block_to_data_simple(self_handle, &out_size);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: serialization failed");
        return NULL;
    }
    PyObject* py_result = Py_BuildValue("y#", result, (Py_ssize_t)out_size);
    kth_core_destruct_array(result);
    return py_result;
}

PyObject*
kth_py_native_chain_block_serialized_size(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_block_const_t self_handle = (kth_block_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_BLOCK);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_block_serialized_size(self_handle);
    return PyLong_FromSize_t((size_t)result);
}

PyObject*
kth_py_native_chain_block_set_transactions(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    PyObject* py_value = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_value)) {
        return NULL;
    }
    kth_block_mut_t self_handle = (kth_block_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_BLOCK);
    if (self_handle == NULL) return NULL;
    kth_transaction_list_const_t value_handle = (kth_transaction_list_const_t)PyCapsule_GetPointer(py_value, KTH_PY_CAPSULE_CHAIN_TRANSACTION_LIST);
    if (value_handle == NULL) return NULL;
    kth_chain_block_set_transactions(self_handle, value_handle);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_block_genesis_mainnet(PyObject* self, PyObject* Py_UNUSED(args)) {
    auto const result = kth_chain_block_genesis_mainnet();
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_BLOCK, kth_py_native_chain_block_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_block_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_block_genesis_testnet(PyObject* self, PyObject* Py_UNUSED(args)) {
    auto const result = kth_chain_block_genesis_testnet();
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_BLOCK, kth_py_native_chain_block_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_block_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_block_genesis_regtest(PyObject* self, PyObject* Py_UNUSED(args)) {
    auto const result = kth_chain_block_genesis_regtest();
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_BLOCK, kth_py_native_chain_block_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_block_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_block_genesis_testnet4(PyObject* self, PyObject* Py_UNUSED(args)) {
    auto const result = kth_chain_block_genesis_testnet4();
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_BLOCK, kth_py_native_chain_block_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_block_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_block_genesis_scalenet(PyObject* self, PyObject* Py_UNUSED(args)) {
    auto const result = kth_chain_block_genesis_scalenet();
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_BLOCK, kth_py_native_chain_block_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_block_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_block_genesis_chipnet(PyObject* self, PyObject* Py_UNUSED(args)) {
    auto const result = kth_chain_block_genesis_chipnet();
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_BLOCK, kth_py_native_chain_block_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_block_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_block_locator_size(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"top", NULL};
    Py_ssize_t top = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "n", kwlist, &top)) {
        return NULL;
    }
    if (top < 0) {
        PyErr_Format(PyExc_ValueError, "top must be non-negative, got %zd", top);
        return NULL;
    }
    auto const result = kth_chain_block_locator_size((kth_size_t)top);
    return PyLong_FromSize_t((size_t)result);
}

PyObject*
kth_py_native_chain_block_locator_heights(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"top", NULL};
    Py_ssize_t top = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "n", kwlist, &top)) {
        return NULL;
    }
    if (top < 0) {
        PyErr_Format(PyExc_ValueError, "top must be non-negative, got %zd", top);
        return NULL;
    }
    auto const result = kth_chain_block_locator_heights((kth_size_t)top);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL list returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CORE_U64_LIST, NULL);
    if (capsule == NULL) {
        kth_core_u64_list_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_block_signature_operations_simple(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_block_const_t self_handle = (kth_block_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_BLOCK);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_block_signature_operations_simple(self_handle);
    return PyLong_FromSize_t((size_t)result);
}

PyObject*
kth_py_native_chain_block_total_inputs(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"with_coinbase", NULL};
    PyObject* py_self = NULL;
    int with_coinbase = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Op", kwlist, &py_self, &with_coinbase)) {
        return NULL;
    }
    kth_block_const_t self_handle = (kth_block_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_BLOCK);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_block_total_inputs(self_handle, (kth_bool_t)with_coinbase);
    return PyLong_FromSize_t((size_t)result);
}

PyObject*
kth_py_native_chain_block_check(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_block_const_t self_handle = (kth_block_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_BLOCK);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_block_check(self_handle);
    return PyLong_FromLong((long)result);
}

PyObject*
kth_py_native_chain_block_accept(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"flags", (char*)"height", (char*)"median_time_past", (char*)"max_block_size_dynamic", (char*)"max_sigops", (char*)"is_under_checkpoint", (char*)"transactions", NULL};
    PyObject* py_self = NULL;
    unsigned long long flags = 0;
    Py_ssize_t height = 0;
    unsigned int median_time_past = 0;
    Py_ssize_t max_block_size_dynamic = 0;
    Py_ssize_t max_sigops = 0;
    int is_under_checkpoint = 0;
    int transactions = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OKnInnpp", kwlist, &py_self, &flags, &height, &median_time_past, &max_block_size_dynamic, &max_sigops, &is_under_checkpoint, &transactions)) {
        return NULL;
    }
    kth_block_const_t self_handle = (kth_block_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_BLOCK);
    if (self_handle == NULL) return NULL;
    if (height < 0) {
        PyErr_Format(PyExc_ValueError, "height must be non-negative, got %zd", height);
        return NULL;
    }
    if (max_block_size_dynamic < 0) {
        PyErr_Format(PyExc_ValueError, "max_block_size_dynamic must be non-negative, got %zd", max_block_size_dynamic);
        return NULL;
    }
    if (max_sigops < 0) {
        PyErr_Format(PyExc_ValueError, "max_sigops must be non-negative, got %zd", max_sigops);
        return NULL;
    }
    auto const result = kth_chain_block_accept(self_handle, (kth_script_flags_t)flags, (kth_size_t)height, (uint32_t)median_time_past, (kth_size_t)max_block_size_dynamic, (kth_size_t)max_sigops, (kth_bool_t)is_under_checkpoint, (kth_bool_t)transactions);
    return PyLong_FromLong((long)result);
}

PyObject*
kth_py_native_chain_block_connect(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_block_const_t self_handle = (kth_block_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_BLOCK);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_block_connect(self_handle);
    return PyLong_FromLong((long)result);
}

PyObject*
kth_py_native_chain_block_equals(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"other", NULL};
    PyObject* py_self = NULL;
    PyObject* py_other = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_other)) {
        return NULL;
    }
    kth_block_const_t self_handle = (kth_block_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_BLOCK);
    if (self_handle == NULL) return NULL;
    kth_block_const_t other_handle = (kth_block_const_t)PyCapsule_GetPointer(py_other, KTH_PY_CAPSULE_CHAIN_BLOCK);
    if (other_handle == NULL) return NULL;
    auto const result = kth_chain_block_equals(self_handle, other_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_block_is_valid(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_block_const_t self_handle = (kth_block_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_BLOCK);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_block_is_valid(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_block_to_data(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"serialized_size", NULL};
    PyObject* py_self = NULL;
    Py_ssize_t serialized_size = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "On", kwlist, &py_self, &serialized_size)) {
        return NULL;
    }
    kth_block_const_t self_handle = (kth_block_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_BLOCK);
    if (self_handle == NULL) return NULL;
    if (serialized_size < 0) {
        PyErr_Format(PyExc_ValueError, "serialized_size must be non-negative, got %zd", serialized_size);
        return NULL;
    }
    kth_size_t out_size = 0;
    auto const result = kth_chain_block_to_data(self_handle, (kth_size_t)serialized_size, &out_size);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: serialization failed");
        return NULL;
    }
    PyObject* py_result = Py_BuildValue("y#", result, (Py_ssize_t)out_size);
    kth_core_destruct_array(result);
    return py_result;
}

PyObject*
kth_py_native_chain_block_to_hashes(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_block_const_t self_handle = (kth_block_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_BLOCK);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_block_to_hashes(self_handle);
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
kth_py_native_chain_block_header(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_block_const_t self_handle = (kth_block_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_BLOCK);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_block_header(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_HEADER, kth_py_native_borrowed_parent_dtor);
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
kth_py_native_chain_block_set_header(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"value", NULL};
    PyObject* py_self = NULL;
    PyObject* py_value = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_value)) {
        return NULL;
    }
    kth_block_mut_t self_handle = (kth_block_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_BLOCK);
    if (self_handle == NULL) return NULL;
    kth_header_const_t value_handle = (kth_header_const_t)PyCapsule_GetPointer(py_value, KTH_PY_CAPSULE_CHAIN_HEADER);
    if (value_handle == NULL) return NULL;
    kth_chain_block_set_header(self_handle, value_handle);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_block_transactions(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_block_const_t self_handle = (kth_block_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_BLOCK);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_block_transactions(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL list returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_TRANSACTION_LIST, kth_py_native_borrowed_parent_dtor);
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
kth_py_native_chain_block_hash(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_block_const_t self_handle = (kth_block_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_BLOCK);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_block_hash(self_handle);
    return Py_BuildValue("y#", result.hash, (Py_ssize_t)KTH_BITCOIN_HASH_SIZE);
}

PyObject*
kth_py_native_chain_block_subsidy(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"height", (char*)"retarget", NULL};
    Py_ssize_t height = 0;
    int retarget = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "np", kwlist, &height, &retarget)) {
        return NULL;
    }
    if (height < 0) {
        PyErr_Format(PyExc_ValueError, "height must be non-negative, got %zd", height);
        return NULL;
    }
    auto const result = kth_chain_block_subsidy((kth_size_t)height, (kth_bool_t)retarget);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyObject*
kth_py_native_chain_block_fees(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_block_const_t self_handle = (kth_block_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_BLOCK);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_block_fees(self_handle);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyObject*
kth_py_native_chain_block_claim(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_block_const_t self_handle = (kth_block_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_BLOCK);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_block_claim(self_handle);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyObject*
kth_py_native_chain_block_reward(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"height", NULL};
    PyObject* py_self = NULL;
    Py_ssize_t height = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "On", kwlist, &py_self, &height)) {
        return NULL;
    }
    kth_block_const_t self_handle = (kth_block_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_BLOCK);
    if (self_handle == NULL) return NULL;
    if (height < 0) {
        PyErr_Format(PyExc_ValueError, "height must be non-negative, got %zd", height);
        return NULL;
    }
    auto const result = kth_chain_block_reward(self_handle, (kth_size_t)height);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyObject*
kth_py_native_chain_block_generate_merkle_root(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_block_const_t self_handle = (kth_block_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_BLOCK);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_block_generate_merkle_root(self_handle);
    return Py_BuildValue("y#", result.hash, (Py_ssize_t)KTH_BITCOIN_HASH_SIZE);
}

PyObject*
kth_py_native_chain_block_signature_operations(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"bip16", (char*)"bip141", NULL};
    PyObject* py_self = NULL;
    int bip16 = 0;
    int bip141 = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Opp", kwlist, &py_self, &bip16, &bip141)) {
        return NULL;
    }
    kth_block_const_t self_handle = (kth_block_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_BLOCK);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_block_signature_operations(self_handle, (kth_bool_t)bip16, (kth_bool_t)bip141);
    return PyLong_FromSize_t((size_t)result);
}

PyObject*
kth_py_native_chain_block_is_extra_coinbases(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_block_const_t self_handle = (kth_block_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_BLOCK);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_block_is_extra_coinbases(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_block_is_final(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"height", (char*)"block_time", NULL};
    PyObject* py_self = NULL;
    Py_ssize_t height = 0;
    unsigned int block_time = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OnI", kwlist, &py_self, &height, &block_time)) {
        return NULL;
    }
    kth_block_const_t self_handle = (kth_block_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_BLOCK);
    if (self_handle == NULL) return NULL;
    if (height < 0) {
        PyErr_Format(PyExc_ValueError, "height must be non-negative, got %zd", height);
        return NULL;
    }
    auto const result = kth_chain_block_is_final(self_handle, (kth_size_t)height, (uint32_t)block_time);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_block_is_distinct_transaction_set(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_block_const_t self_handle = (kth_block_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_BLOCK);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_block_is_distinct_transaction_set(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_block_is_valid_coinbase_claim(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"height", NULL};
    PyObject* py_self = NULL;
    Py_ssize_t height = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "On", kwlist, &py_self, &height)) {
        return NULL;
    }
    kth_block_const_t self_handle = (kth_block_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_BLOCK);
    if (self_handle == NULL) return NULL;
    if (height < 0) {
        PyErr_Format(PyExc_ValueError, "height must be non-negative, got %zd", height);
        return NULL;
    }
    auto const result = kth_chain_block_is_valid_coinbase_claim(self_handle, (kth_size_t)height);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_block_is_valid_coinbase_script(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"height", NULL};
    PyObject* py_self = NULL;
    Py_ssize_t height = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "On", kwlist, &py_self, &height)) {
        return NULL;
    }
    kth_block_const_t self_handle = (kth_block_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_BLOCK);
    if (self_handle == NULL) return NULL;
    if (height < 0) {
        PyErr_Format(PyExc_ValueError, "height must be non-negative, got %zd", height);
        return NULL;
    }
    auto const result = kth_chain_block_is_valid_coinbase_script(self_handle, (kth_size_t)height);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_block_is_forward_reference(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_block_const_t self_handle = (kth_block_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_BLOCK);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_block_is_forward_reference(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_block_is_canonical_ordered(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_block_const_t self_handle = (kth_block_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_BLOCK);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_block_is_canonical_ordered(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_block_is_internal_double_spend(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_block_const_t self_handle = (kth_block_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_BLOCK);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_block_is_internal_double_spend(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_block_is_valid_merkle_root(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_block_const_t self_handle = (kth_block_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_BLOCK);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_block_is_valid_merkle_root(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_block_check_transactions(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_block_const_t self_handle = (kth_block_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_BLOCK);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_block_check_transactions(self_handle);
    return PyLong_FromLong((long)result);
}

PyObject*
kth_py_native_chain_block_accept_transactions(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"flags", (char*)"height", (char*)"median_time_past", (char*)"max_sigops", (char*)"is_under_checkpoint", NULL};
    PyObject* py_self = NULL;
    unsigned long long flags = 0;
    Py_ssize_t height = 0;
    unsigned int median_time_past = 0;
    Py_ssize_t max_sigops = 0;
    int is_under_checkpoint = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OKnInp", kwlist, &py_self, &flags, &height, &median_time_past, &max_sigops, &is_under_checkpoint)) {
        return NULL;
    }
    kth_block_const_t self_handle = (kth_block_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_BLOCK);
    if (self_handle == NULL) return NULL;
    if (height < 0) {
        PyErr_Format(PyExc_ValueError, "height must be non-negative, got %zd", height);
        return NULL;
    }
    if (max_sigops < 0) {
        PyErr_Format(PyExc_ValueError, "max_sigops must be non-negative, got %zd", max_sigops);
        return NULL;
    }
    auto const result = kth_chain_block_accept_transactions(self_handle, (kth_script_flags_t)flags, (kth_size_t)height, (uint32_t)median_time_past, (kth_size_t)max_sigops, (kth_bool_t)is_under_checkpoint);
    return PyLong_FromLong((long)result);
}

PyObject*
kth_py_native_chain_block_connect_transactions(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"state", NULL};
    PyObject* py_self = NULL;
    PyObject* py_state = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_state)) {
        return NULL;
    }
    kth_block_const_t self_handle = (kth_block_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_BLOCK);
    if (self_handle == NULL) return NULL;
    kth_chain_state_const_t state_handle = (kth_chain_state_const_t)PyCapsule_GetPointer(py_state, KTH_PY_CAPSULE_CHAIN_CHAIN_STATE);
    if (state_handle == NULL) return NULL;
    auto const result = kth_chain_block_connect_transactions(self_handle, state_handle);
    return PyLong_FromLong((long)result);
}

PyObject*
kth_py_native_chain_block_reset(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_block_mut_t self_handle = (kth_block_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_BLOCK);
    if (self_handle == NULL) return NULL;
    kth_chain_block_reset(self_handle);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_block_non_coinbase_input_count(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_block_const_t self_handle = (kth_block_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_BLOCK);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_block_non_coinbase_input_count(self_handle);
    return PyLong_FromSize_t((size_t)result);
}

PyMethodDef kth_py_native_chain_block_methods[] = {
    {"chain_block_construct_default", (PyCFunction)kth_py_native_chain_block_construct_default, METH_NOARGS, NULL},
    {"chain_block_construct_from_data", (PyCFunction)kth_py_native_chain_block_construct_from_data, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_block_construct", (PyCFunction)kth_py_native_chain_block_construct, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_block_copy", (PyCFunction)kth_py_native_chain_block_copy, METH_O, NULL},
    {"chain_block_destruct", (PyCFunction)kth_py_native_chain_block_destruct, METH_O, NULL},
    {"chain_block_to_data_simple", (PyCFunction)kth_py_native_chain_block_to_data_simple, METH_O, NULL},
    {"chain_block_serialized_size", (PyCFunction)kth_py_native_chain_block_serialized_size, METH_O, NULL},
    {"chain_block_set_transactions", (PyCFunction)kth_py_native_chain_block_set_transactions, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_block_genesis_mainnet", (PyCFunction)kth_py_native_chain_block_genesis_mainnet, METH_NOARGS, NULL},
    {"chain_block_genesis_testnet", (PyCFunction)kth_py_native_chain_block_genesis_testnet, METH_NOARGS, NULL},
    {"chain_block_genesis_regtest", (PyCFunction)kth_py_native_chain_block_genesis_regtest, METH_NOARGS, NULL},
    {"chain_block_genesis_testnet4", (PyCFunction)kth_py_native_chain_block_genesis_testnet4, METH_NOARGS, NULL},
    {"chain_block_genesis_scalenet", (PyCFunction)kth_py_native_chain_block_genesis_scalenet, METH_NOARGS, NULL},
    {"chain_block_genesis_chipnet", (PyCFunction)kth_py_native_chain_block_genesis_chipnet, METH_NOARGS, NULL},
    {"chain_block_locator_size", (PyCFunction)kth_py_native_chain_block_locator_size, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_block_locator_heights", (PyCFunction)kth_py_native_chain_block_locator_heights, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_block_signature_operations_simple", (PyCFunction)kth_py_native_chain_block_signature_operations_simple, METH_O, NULL},
    {"chain_block_total_inputs", (PyCFunction)kth_py_native_chain_block_total_inputs, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_block_check", (PyCFunction)kth_py_native_chain_block_check, METH_O, NULL},
    {"chain_block_accept", (PyCFunction)kth_py_native_chain_block_accept, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_block_connect", (PyCFunction)kth_py_native_chain_block_connect, METH_O, NULL},
    {"chain_block_equals", (PyCFunction)kth_py_native_chain_block_equals, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_block_is_valid", (PyCFunction)kth_py_native_chain_block_is_valid, METH_O, NULL},
    {"chain_block_to_data", (PyCFunction)kth_py_native_chain_block_to_data, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_block_to_hashes", (PyCFunction)kth_py_native_chain_block_to_hashes, METH_O, NULL},
    {"chain_block_header", (PyCFunction)kth_py_native_chain_block_header, METH_O, NULL},
    {"chain_block_set_header", (PyCFunction)kth_py_native_chain_block_set_header, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_block_transactions", (PyCFunction)kth_py_native_chain_block_transactions, METH_O, NULL},
    {"chain_block_hash", (PyCFunction)kth_py_native_chain_block_hash, METH_O, NULL},
    {"chain_block_subsidy", (PyCFunction)kth_py_native_chain_block_subsidy, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_block_fees", (PyCFunction)kth_py_native_chain_block_fees, METH_O, NULL},
    {"chain_block_claim", (PyCFunction)kth_py_native_chain_block_claim, METH_O, NULL},
    {"chain_block_reward", (PyCFunction)kth_py_native_chain_block_reward, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_block_generate_merkle_root", (PyCFunction)kth_py_native_chain_block_generate_merkle_root, METH_O, NULL},
    {"chain_block_signature_operations", (PyCFunction)kth_py_native_chain_block_signature_operations, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_block_is_extra_coinbases", (PyCFunction)kth_py_native_chain_block_is_extra_coinbases, METH_O, NULL},
    {"chain_block_is_final", (PyCFunction)kth_py_native_chain_block_is_final, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_block_is_distinct_transaction_set", (PyCFunction)kth_py_native_chain_block_is_distinct_transaction_set, METH_O, NULL},
    {"chain_block_is_valid_coinbase_claim", (PyCFunction)kth_py_native_chain_block_is_valid_coinbase_claim, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_block_is_valid_coinbase_script", (PyCFunction)kth_py_native_chain_block_is_valid_coinbase_script, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_block_is_forward_reference", (PyCFunction)kth_py_native_chain_block_is_forward_reference, METH_O, NULL},
    {"chain_block_is_canonical_ordered", (PyCFunction)kth_py_native_chain_block_is_canonical_ordered, METH_O, NULL},
    {"chain_block_is_internal_double_spend", (PyCFunction)kth_py_native_chain_block_is_internal_double_spend, METH_O, NULL},
    {"chain_block_is_valid_merkle_root", (PyCFunction)kth_py_native_chain_block_is_valid_merkle_root, METH_O, NULL},
    {"chain_block_check_transactions", (PyCFunction)kth_py_native_chain_block_check_transactions, METH_O, NULL},
    {"chain_block_accept_transactions", (PyCFunction)kth_py_native_chain_block_accept_transactions, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_block_connect_transactions", (PyCFunction)kth_py_native_chain_block_connect_transactions, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_block_reset", (PyCFunction)kth_py_native_chain_block_reset, METH_O, NULL},
    {"chain_block_non_coinbase_input_count", (PyCFunction)kth_py_native_chain_block_non_coinbase_input_count, METH_O, NULL},
    {NULL, NULL, 0, NULL}  // sentinel
};

#ifdef __cplusplus
} // extern "C"
#endif
