// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/py-native/wallet/coin_selection.h>

#include <string.h>
#include <kth/capi.h>
#include <kth/capi/wallet/coin_selection.h>
#include <kth/py-native/capsule_names.h>
#include <kth/py-native/utils.h>

#ifdef __cplusplus
extern "C" {
#endif

PyObject*
kth_py_native_wallet_coin_selection_select_utxos(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"available_utxos", (char*)"amount", (char*)"outputs_size", (char*)"category", (char*)"strategy", NULL};
    PyObject* py_available_utxos = NULL;
    unsigned long long amount = 0;
    Py_ssize_t outputs_size = 0;
    char const* category_buf = NULL;
    Py_ssize_t category_size = 0;
    unsigned long long strategy = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OKny#K", kwlist, &py_available_utxos, &amount, &outputs_size, &category_buf, &category_size, &strategy)) {
        return NULL;
    }
    kth_utxo_list_const_t available_utxos_handle = (kth_utxo_list_const_t)PyCapsule_GetPointer(py_available_utxos, KTH_PY_CAPSULE_CHAIN_UTXO_LIST);
    if (available_utxos_handle == NULL) return NULL;
    if (outputs_size < 0) {
        PyErr_Format(PyExc_ValueError, "outputs_size must be non-negative, got %zd", outputs_size);
        return NULL;
    }
    if (category_size != (Py_ssize_t)KTH_BITCOIN_HASH_SIZE) {
        PyErr_Format(PyExc_ValueError, "expected %d-byte category, got %zd", (int)KTH_BITCOIN_HASH_SIZE, category_size);
        return NULL;
    }
    kth_hash_t category;
    memcpy(category.hash, category_buf, (size_t)KTH_BITCOIN_HASH_SIZE);
    kth_coin_selection_result_mut_t out = NULL;
    kth_error_code_t result = kth_wallet_coin_selection_select_utxos(available_utxos_handle, (uint64_t)amount, (kth_size_t)outputs_size, &category, (kth_coin_selection_strategy_t)strategy, &out);
    if (result != kth_ec_success) {
        PyErr_Format(PyExc_RuntimeError, "kth error code %d", (int)result);
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)out, KTH_PY_CAPSULE_WALLET_COIN_SELECTION_RESULT, kth_py_native_wallet_coin_selection_result_capsule_dtor);
    if (capsule == NULL) {
        kth_wallet_coin_selection_result_destruct(out);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_wallet_coin_selection_select_utxos_send_all(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"available_utxos", (char*)"outputs_size", (char*)"category", NULL};
    PyObject* py_available_utxos = NULL;
    Py_ssize_t outputs_size = 0;
    char const* category_buf = NULL;
    Py_ssize_t category_size = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "Ony#", kwlist, &py_available_utxos, &outputs_size, &category_buf, &category_size)) {
        return NULL;
    }
    kth_utxo_list_const_t available_utxos_handle = (kth_utxo_list_const_t)PyCapsule_GetPointer(py_available_utxos, KTH_PY_CAPSULE_CHAIN_UTXO_LIST);
    if (available_utxos_handle == NULL) return NULL;
    if (outputs_size < 0) {
        PyErr_Format(PyExc_ValueError, "outputs_size must be non-negative, got %zd", outputs_size);
        return NULL;
    }
    if (category_size != (Py_ssize_t)KTH_BITCOIN_HASH_SIZE) {
        PyErr_Format(PyExc_ValueError, "expected %d-byte category, got %zd", (int)KTH_BITCOIN_HASH_SIZE, category_size);
        return NULL;
    }
    kth_hash_t category;
    memcpy(category.hash, category_buf, (size_t)KTH_BITCOIN_HASH_SIZE);
    kth_coin_selection_result_mut_t out = NULL;
    kth_error_code_t result = kth_wallet_coin_selection_select_utxos_send_all(available_utxos_handle, (kth_size_t)outputs_size, &category, &out);
    if (result != kth_ec_success) {
        PyErr_Format(PyExc_RuntimeError, "kth error code %d", (int)result);
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)out, KTH_PY_CAPSULE_WALLET_COIN_SELECTION_RESULT, kth_py_native_wallet_coin_selection_result_capsule_dtor);
    if (capsule == NULL) {
        kth_wallet_coin_selection_result_destruct(out);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_wallet_coin_selection_select_utxos_both(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"available_utxos", (char*)"bch_amount", (char*)"token_category", (char*)"token_amount", (char*)"outputs_size", (char*)"strategy", NULL};
    PyObject* py_available_utxos = NULL;
    unsigned long long bch_amount = 0;
    char const* token_category_buf = NULL;
    Py_ssize_t token_category_size = 0;
    unsigned long long token_amount = 0;
    Py_ssize_t outputs_size = 0;
    unsigned long long strategy = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OKy#KnK", kwlist, &py_available_utxos, &bch_amount, &token_category_buf, &token_category_size, &token_amount, &outputs_size, &strategy)) {
        return NULL;
    }
    kth_utxo_list_const_t available_utxos_handle = (kth_utxo_list_const_t)PyCapsule_GetPointer(py_available_utxos, KTH_PY_CAPSULE_CHAIN_UTXO_LIST);
    if (available_utxos_handle == NULL) return NULL;
    if (token_category_size != (Py_ssize_t)KTH_BITCOIN_HASH_SIZE) {
        PyErr_Format(PyExc_ValueError, "expected %d-byte token_category, got %zd", (int)KTH_BITCOIN_HASH_SIZE, token_category_size);
        return NULL;
    }
    kth_hash_t token_category;
    memcpy(token_category.hash, token_category_buf, (size_t)KTH_BITCOIN_HASH_SIZE);
    if (outputs_size < 0) {
        PyErr_Format(PyExc_ValueError, "outputs_size must be non-negative, got %zd", outputs_size);
        return NULL;
    }
    kth_coin_selection_result_mut_t out = NULL;
    kth_error_code_t result = kth_wallet_coin_selection_select_utxos_both(available_utxos_handle, (uint64_t)bch_amount, &token_category, (uint64_t)token_amount, (kth_size_t)outputs_size, (kth_coin_selection_strategy_t)strategy, &out);
    if (result != kth_ec_success) {
        PyErr_Format(PyExc_RuntimeError, "kth error code %d", (int)result);
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)out, KTH_PY_CAPSULE_WALLET_COIN_SELECTION_RESULT, kth_py_native_wallet_coin_selection_result_capsule_dtor);
    if (capsule == NULL) {
        kth_wallet_coin_selection_result_destruct(out);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_wallet_coin_selection_create_token_split_tx_template(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"outpoints_to_split", (char*)"available_utxos", (char*)"destination_address", NULL};
    PyObject* py_outpoints_to_split = NULL;
    PyObject* py_available_utxos = NULL;
    PyObject* py_destination_address = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OOO", kwlist, &py_outpoints_to_split, &py_available_utxos, &py_destination_address)) {
        return NULL;
    }
    kth_output_point_list_const_t outpoints_to_split_handle = (kth_output_point_list_const_t)PyCapsule_GetPointer(py_outpoints_to_split, KTH_PY_CAPSULE_CHAIN_OUTPUT_POINT_LIST);
    if (outpoints_to_split_handle == NULL) return NULL;
    kth_utxo_list_const_t available_utxos_handle = (kth_utxo_list_const_t)PyCapsule_GetPointer(py_available_utxos, KTH_PY_CAPSULE_CHAIN_UTXO_LIST);
    if (available_utxos_handle == NULL) return NULL;
    kth_payment_address_const_t destination_address_handle = (kth_payment_address_const_t)PyCapsule_GetPointer(py_destination_address, KTH_PY_CAPSULE_WALLET_PAYMENT_ADDRESS);
    if (destination_address_handle == NULL) return NULL;
    kth_transaction_mut_t out_0 = NULL;
    kth_payment_address_list_mut_t out_1 = NULL;
    kth_u64_list_mut_t out_2 = NULL;
    kth_error_code_t result = kth_wallet_coin_selection_create_token_split_tx_template(outpoints_to_split_handle, available_utxos_handle, destination_address_handle, &out_0, &out_1, &out_2);
    if (result != kth_ec_success) {
        PyErr_Format(PyExc_RuntimeError, "kth error code %d", (int)result);
        return NULL;
    }
    PyObject* capsule_0 = PyCapsule_New((void*)out_0, KTH_PY_CAPSULE_CHAIN_TRANSACTION, kth_py_native_chain_transaction_capsule_dtor);
    PyObject* capsule_1 = PyCapsule_New((void*)out_1, KTH_PY_CAPSULE_WALLET_PAYMENT_ADDRESS_LIST, kth_py_native_wallet_payment_address_list_capsule_dtor);
    PyObject* capsule_2 = PyCapsule_New((void*)out_2, KTH_PY_CAPSULE_CORE_U64_LIST, NULL);
    if (capsule_0 == NULL) {
        kth_chain_transaction_destruct(out_0);
        kth_wallet_payment_address_list_destruct(out_1);
        kth_core_u64_list_destruct(out_2);
        return NULL;
    }
    if (capsule_1 == NULL) {
        kth_wallet_payment_address_list_destruct(out_1);
        Py_DECREF(capsule_0);
        kth_core_u64_list_destruct(out_2);
        return NULL;
    }
    if (capsule_2 == NULL) {
        kth_core_u64_list_destruct(out_2);
        Py_DECREF(capsule_0);
        Py_DECREF(capsule_1);
        return NULL;
    }
    PyObject* py_result = Py_BuildValue("(OOO)", capsule_0, capsule_1, capsule_2);
    if (py_result == NULL) {
        Py_DECREF(capsule_0);
        Py_DECREF(capsule_1);
        Py_DECREF(capsule_2);
        return NULL;
    }
    Py_DECREF(capsule_0);
    Py_DECREF(capsule_1);
    Py_DECREF(capsule_2);
    return py_result;
}

PyObject*
kth_py_native_wallet_coin_selection_create_tx_template(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"available_utxos", (char*)"amount_to_send", (char*)"destination_address", (char*)"change_addresses", (char*)"change_ratios", (char*)"selection_algo", NULL};
    PyObject* py_available_utxos = NULL;
    unsigned long long amount_to_send = 0;
    PyObject* py_destination_address = NULL;
    PyObject* py_change_addresses = NULL;
    PyObject* py_change_ratios = NULL;
    unsigned long long selection_algo = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OKOOOK", kwlist, &py_available_utxos, &amount_to_send, &py_destination_address, &py_change_addresses, &py_change_ratios, &selection_algo)) {
        return NULL;
    }
    kth_utxo_list_const_t available_utxos_handle = (kth_utxo_list_const_t)PyCapsule_GetPointer(py_available_utxos, KTH_PY_CAPSULE_CHAIN_UTXO_LIST);
    if (available_utxos_handle == NULL) return NULL;
    kth_payment_address_const_t destination_address_handle = (kth_payment_address_const_t)PyCapsule_GetPointer(py_destination_address, KTH_PY_CAPSULE_WALLET_PAYMENT_ADDRESS);
    if (destination_address_handle == NULL) return NULL;
    kth_payment_address_list_const_t change_addresses_handle = (kth_payment_address_list_const_t)PyCapsule_GetPointer(py_change_addresses, KTH_PY_CAPSULE_WALLET_PAYMENT_ADDRESS_LIST);
    if (change_addresses_handle == NULL) return NULL;
    kth_double_list_const_t change_ratios_handle = (kth_double_list_const_t)PyCapsule_GetPointer(py_change_ratios, KTH_PY_CAPSULE_CORE_DOUBLE_LIST);
    if (change_ratios_handle == NULL) return NULL;
    kth_transaction_mut_t out_0 = NULL;
    kth_u32_list_mut_t out_1 = NULL;
    kth_payment_address_list_mut_t out_2 = NULL;
    kth_u64_list_mut_t out_3 = NULL;
    kth_error_code_t result = kth_wallet_coin_selection_create_tx_template(available_utxos_handle, (uint64_t)amount_to_send, destination_address_handle, change_addresses_handle, change_ratios_handle, (kth_coin_selection_algorithm_t)selection_algo, &out_0, &out_1, &out_2, &out_3);
    if (result != kth_ec_success) {
        PyErr_Format(PyExc_RuntimeError, "kth error code %d", (int)result);
        return NULL;
    }
    PyObject* capsule_0 = PyCapsule_New((void*)out_0, KTH_PY_CAPSULE_CHAIN_TRANSACTION, kth_py_native_chain_transaction_capsule_dtor);
    PyObject* capsule_1 = PyCapsule_New((void*)out_1, KTH_PY_CAPSULE_CORE_U32_LIST, NULL);
    PyObject* capsule_2 = PyCapsule_New((void*)out_2, KTH_PY_CAPSULE_WALLET_PAYMENT_ADDRESS_LIST, kth_py_native_wallet_payment_address_list_capsule_dtor);
    PyObject* capsule_3 = PyCapsule_New((void*)out_3, KTH_PY_CAPSULE_CORE_U64_LIST, NULL);
    if (capsule_0 == NULL) {
        kth_chain_transaction_destruct(out_0);
        kth_core_u32_list_destruct(out_1);
        kth_wallet_payment_address_list_destruct(out_2);
        kth_core_u64_list_destruct(out_3);
        return NULL;
    }
    if (capsule_1 == NULL) {
        kth_core_u32_list_destruct(out_1);
        Py_DECREF(capsule_0);
        kth_wallet_payment_address_list_destruct(out_2);
        kth_core_u64_list_destruct(out_3);
        return NULL;
    }
    if (capsule_2 == NULL) {
        kth_wallet_payment_address_list_destruct(out_2);
        Py_DECREF(capsule_0);
        Py_DECREF(capsule_1);
        kth_core_u64_list_destruct(out_3);
        return NULL;
    }
    if (capsule_3 == NULL) {
        kth_core_u64_list_destruct(out_3);
        Py_DECREF(capsule_0);
        Py_DECREF(capsule_1);
        Py_DECREF(capsule_2);
        return NULL;
    }
    PyObject* py_result = Py_BuildValue("(OOOO)", capsule_0, capsule_1, capsule_2, capsule_3);
    if (py_result == NULL) {
        Py_DECREF(capsule_0);
        Py_DECREF(capsule_1);
        Py_DECREF(capsule_2);
        Py_DECREF(capsule_3);
        return NULL;
    }
    Py_DECREF(capsule_0);
    Py_DECREF(capsule_1);
    Py_DECREF(capsule_2);
    Py_DECREF(capsule_3);
    return py_result;
}

PyObject*
kth_py_native_wallet_coin_selection_create_tx_template_default_ratios(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"available_utxos", (char*)"amount_to_send", (char*)"destination_address", (char*)"change_addresses", (char*)"selection_algo", NULL};
    PyObject* py_available_utxos = NULL;
    unsigned long long amount_to_send = 0;
    PyObject* py_destination_address = NULL;
    PyObject* py_change_addresses = NULL;
    unsigned long long selection_algo = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OKOOK", kwlist, &py_available_utxos, &amount_to_send, &py_destination_address, &py_change_addresses, &selection_algo)) {
        return NULL;
    }
    kth_utxo_list_const_t available_utxos_handle = (kth_utxo_list_const_t)PyCapsule_GetPointer(py_available_utxos, KTH_PY_CAPSULE_CHAIN_UTXO_LIST);
    if (available_utxos_handle == NULL) return NULL;
    kth_payment_address_const_t destination_address_handle = (kth_payment_address_const_t)PyCapsule_GetPointer(py_destination_address, KTH_PY_CAPSULE_WALLET_PAYMENT_ADDRESS);
    if (destination_address_handle == NULL) return NULL;
    kth_payment_address_list_const_t change_addresses_handle = (kth_payment_address_list_const_t)PyCapsule_GetPointer(py_change_addresses, KTH_PY_CAPSULE_WALLET_PAYMENT_ADDRESS_LIST);
    if (change_addresses_handle == NULL) return NULL;
    kth_transaction_mut_t out_0 = NULL;
    kth_u32_list_mut_t out_1 = NULL;
    kth_payment_address_list_mut_t out_2 = NULL;
    kth_u64_list_mut_t out_3 = NULL;
    kth_error_code_t result = kth_wallet_coin_selection_create_tx_template_default_ratios(available_utxos_handle, (uint64_t)amount_to_send, destination_address_handle, change_addresses_handle, (kth_coin_selection_algorithm_t)selection_algo, &out_0, &out_1, &out_2, &out_3);
    if (result != kth_ec_success) {
        PyErr_Format(PyExc_RuntimeError, "kth error code %d", (int)result);
        return NULL;
    }
    PyObject* capsule_0 = PyCapsule_New((void*)out_0, KTH_PY_CAPSULE_CHAIN_TRANSACTION, kth_py_native_chain_transaction_capsule_dtor);
    PyObject* capsule_1 = PyCapsule_New((void*)out_1, KTH_PY_CAPSULE_CORE_U32_LIST, NULL);
    PyObject* capsule_2 = PyCapsule_New((void*)out_2, KTH_PY_CAPSULE_WALLET_PAYMENT_ADDRESS_LIST, kth_py_native_wallet_payment_address_list_capsule_dtor);
    PyObject* capsule_3 = PyCapsule_New((void*)out_3, KTH_PY_CAPSULE_CORE_U64_LIST, NULL);
    if (capsule_0 == NULL) {
        kth_chain_transaction_destruct(out_0);
        kth_core_u32_list_destruct(out_1);
        kth_wallet_payment_address_list_destruct(out_2);
        kth_core_u64_list_destruct(out_3);
        return NULL;
    }
    if (capsule_1 == NULL) {
        kth_core_u32_list_destruct(out_1);
        Py_DECREF(capsule_0);
        kth_wallet_payment_address_list_destruct(out_2);
        kth_core_u64_list_destruct(out_3);
        return NULL;
    }
    if (capsule_2 == NULL) {
        kth_wallet_payment_address_list_destruct(out_2);
        Py_DECREF(capsule_0);
        Py_DECREF(capsule_1);
        kth_core_u64_list_destruct(out_3);
        return NULL;
    }
    if (capsule_3 == NULL) {
        kth_core_u64_list_destruct(out_3);
        Py_DECREF(capsule_0);
        Py_DECREF(capsule_1);
        Py_DECREF(capsule_2);
        return NULL;
    }
    PyObject* py_result = Py_BuildValue("(OOOO)", capsule_0, capsule_1, capsule_2, capsule_3);
    if (py_result == NULL) {
        Py_DECREF(capsule_0);
        Py_DECREF(capsule_1);
        Py_DECREF(capsule_2);
        Py_DECREF(capsule_3);
        return NULL;
    }
    Py_DECREF(capsule_0);
    Py_DECREF(capsule_1);
    Py_DECREF(capsule_2);
    Py_DECREF(capsule_3);
    return py_result;
}

PyObject*
kth_py_native_wallet_coin_selection_make_change_ratios(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"change_count", NULL};
    Py_ssize_t change_count = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "n", kwlist, &change_count)) {
        return NULL;
    }
    if (change_count < 0) {
        PyErr_Format(PyExc_ValueError, "change_count must be non-negative, got %zd", change_count);
        return NULL;
    }
    auto const result = kth_wallet_coin_selection_make_change_ratios((kth_size_t)change_count);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL list returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CORE_DOUBLE_LIST, NULL);
    if (capsule == NULL) {
        kth_core_double_list_destruct(result);
        return NULL;
    }
    return capsule;
}

PyMethodDef kth_py_native_wallet_coin_selection_methods[] = {
    {"wallet_coin_selection_select_utxos", (PyCFunction)kth_py_native_wallet_coin_selection_select_utxos, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_coin_selection_select_utxos_send_all", (PyCFunction)kth_py_native_wallet_coin_selection_select_utxos_send_all, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_coin_selection_select_utxos_both", (PyCFunction)kth_py_native_wallet_coin_selection_select_utxos_both, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_coin_selection_create_token_split_tx_template", (PyCFunction)kth_py_native_wallet_coin_selection_create_token_split_tx_template, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_coin_selection_create_tx_template", (PyCFunction)kth_py_native_wallet_coin_selection_create_tx_template, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_coin_selection_create_tx_template_default_ratios", (PyCFunction)kth_py_native_wallet_coin_selection_create_tx_template_default_ratios, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_coin_selection_make_change_ratios", (PyCFunction)kth_py_native_wallet_coin_selection_make_change_ratios, METH_VARARGS | METH_KEYWORDS, NULL},
    {NULL, NULL, 0, NULL}  // sentinel
};

#ifdef __cplusplus
} // extern "C"
#endif
