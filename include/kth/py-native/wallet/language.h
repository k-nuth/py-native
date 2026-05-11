// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_PY_NATIVE_WALLET_LANGUAGE_H_
#define KTH_PY_NATIVE_WALLET_LANGUAGE_H_

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#ifdef __cplusplus
extern "C" {
#endif

PyObject* kth_py_native_wallet_language_en(PyObject* self, PyObject* args);
PyObject* kth_py_native_wallet_language_es(PyObject* self, PyObject* args);
PyObject* kth_py_native_wallet_language_ja(PyObject* self, PyObject* args);
PyObject* kth_py_native_wallet_language_it(PyObject* self, PyObject* args);
PyObject* kth_py_native_wallet_language_fr(PyObject* self, PyObject* args);
PyObject* kth_py_native_wallet_language_cs(PyObject* self, PyObject* args);
PyObject* kth_py_native_wallet_language_ru(PyObject* self, PyObject* args);
PyObject* kth_py_native_wallet_language_uk(PyObject* self, PyObject* args);
PyObject* kth_py_native_wallet_language_zh_Hans(PyObject* self, PyObject* args);
PyObject* kth_py_native_wallet_language_zh_Hant(PyObject* self, PyObject* args);
PyObject* kth_py_native_wallet_language_all(PyObject* self, PyObject* args);

extern PyMethodDef kth_py_native_wallet_language_methods[];

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_PY_NATIVE_WALLET_LANGUAGE_H_
