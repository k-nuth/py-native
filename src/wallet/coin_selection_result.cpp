// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/py-native/wallet/coin_selection_result.h>

#include <string.h>
#include <kth/capi.h>
#include <kth/capi/wallet/coin_selection_result.h>
#include <kth/py-native/capsule_names.h>
#include <kth/py-native/utils.h>

#ifdef __cplusplus
extern "C" {
#endif

// PyCapsule destructor — released by GC when the capsule is
// collected. Explicit `destruct` calls set the capsule name to
// "kth.destroyed", so PyCapsule_IsValid returns false and this
// destructor becomes a no-op (no double-free).
void kth_py_native_wallet_coin_selection_result_capsule_dtor(PyObject* capsule) {
    if ( ! PyCapsule_IsValid(capsule, KTH_PY_CAPSULE_WALLET_COIN_SELECTION_RESULT)) return;
    kth_coin_selection_result_mut_t handle = (kth_coin_selection_result_mut_t)PyCapsule_GetPointer(capsule, KTH_PY_CAPSULE_WALLET_COIN_SELECTION_RESULT);
    if (handle != NULL) kth_wallet_coin_selection_result_destruct(handle);
}

PyObject*
kth_py_native_wallet_coin_selection_result_copy(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_coin_selection_result_const_t self_handle = (kth_coin_selection_result_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_COIN_SELECTION_RESULT);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_coin_selection_result_copy(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_COIN_SELECTION_RESULT, kth_py_native_wallet_coin_selection_result_capsule_dtor);
    if (capsule == NULL) {
        kth_wallet_coin_selection_result_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_wallet_coin_selection_result_destruct(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_coin_selection_result_mut_t self_handle = (kth_coin_selection_result_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_COIN_SELECTION_RESULT);
    if (self_handle == NULL) return NULL;
    kth_wallet_coin_selection_result_destruct(self_handle);
    PyCapsule_SetName(py_self, "kth.destroyed");
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_wallet_coin_selection_result_total_selected_bch(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_coin_selection_result_const_t self_handle = (kth_coin_selection_result_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_COIN_SELECTION_RESULT);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_coin_selection_result_total_selected_bch(self_handle);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyObject*
kth_py_native_wallet_coin_selection_result_total_selected_token(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_coin_selection_result_const_t self_handle = (kth_coin_selection_result_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_COIN_SELECTION_RESULT);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_coin_selection_result_total_selected_token(self_handle);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyObject*
kth_py_native_wallet_coin_selection_result_estimated_size(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_coin_selection_result_const_t self_handle = (kth_coin_selection_result_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_WALLET_COIN_SELECTION_RESULT);
    if (self_handle == NULL) return NULL;
    auto const result = kth_wallet_coin_selection_result_estimated_size(self_handle);
    return PyLong_FromUnsignedLongLong((unsigned long long)result);
}

PyMethodDef kth_py_native_wallet_coin_selection_result_methods[] = {
    {"wallet_coin_selection_result_copy", (PyCFunction)kth_py_native_wallet_coin_selection_result_copy, METH_O, NULL},
    {"wallet_coin_selection_result_destruct", (PyCFunction)kth_py_native_wallet_coin_selection_result_destruct, METH_O, NULL},
    {"wallet_coin_selection_result_total_selected_bch", (PyCFunction)kth_py_native_wallet_coin_selection_result_total_selected_bch, METH_O, NULL},
    {"wallet_coin_selection_result_total_selected_token", (PyCFunction)kth_py_native_wallet_coin_selection_result_total_selected_token, METH_O, NULL},
    {"wallet_coin_selection_result_estimated_size", (PyCFunction)kth_py_native_wallet_coin_selection_result_estimated_size, METH_O, NULL},
    {NULL, NULL, 0, NULL}  // sentinel
};

#ifdef __cplusplus
} // extern "C"
#endif
