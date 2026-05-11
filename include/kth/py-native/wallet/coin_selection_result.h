// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_PY_NATIVE_WALLET_COIN_SELECTION_RESULT_H_
#define KTH_PY_NATIVE_WALLET_COIN_SELECTION_RESULT_H_

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#ifdef __cplusplus
extern "C" {
#endif

PyObject* kth_py_native_wallet_coin_selection_result_copy(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_coin_selection_result_destruct(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_coin_selection_result_total_selected_bch(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_coin_selection_result_total_selected_token(PyObject* self, PyObject* arg);
PyObject* kth_py_native_wallet_coin_selection_result_estimated_size(PyObject* self, PyObject* arg);

extern PyMethodDef kth_py_native_wallet_coin_selection_result_methods[];

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_PY_NATIVE_WALLET_COIN_SELECTION_RESULT_H_
