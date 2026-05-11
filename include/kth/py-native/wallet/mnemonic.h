// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_PY_NATIVE_WALLET_MNEMONIC_H_
#define KTH_PY_NATIVE_WALLET_MNEMONIC_H_

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#ifdef __cplusplus
extern "C" {
#endif

PyObject* kth_py_native_wallet_mnemonic_create_mnemonic(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_mnemonic_validate_mnemonic_dictionary(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_wallet_mnemonic_validate_mnemonic_dictionary_list(PyObject* self, PyObject* args, PyObject* kwds);

extern PyMethodDef kth_py_native_wallet_mnemonic_methods[];

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_PY_NATIVE_WALLET_MNEMONIC_H_
