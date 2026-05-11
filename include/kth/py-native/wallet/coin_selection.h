// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_PY_NATIVE_WALLET_COIN_SELECTION_H_
#define KTH_PY_NATIVE_WALLET_COIN_SELECTION_H_

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#ifdef __cplusplus
extern "C" {
#endif

PyObject* kth_py_native_wallet_coin_selection_select_utxos(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_coin_selection_select_utxos_send_all(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_coin_selection_select_utxos_both(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_coin_selection_create_token_split_tx_template(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_coin_selection_create_tx_template(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_coin_selection_create_tx_template_default_ratios(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_coin_selection_make_change_ratios(PyObject* self, PyObject* args, PyObject* kwds);

extern PyMethodDef kth_py_native_wallet_coin_selection_methods[];

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_PY_NATIVE_WALLET_COIN_SELECTION_H_
