// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_PY_NATIVE_CHAIN_ABLA_H_
#define KTH_PY_NATIVE_CHAIN_ABLA_H_

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#ifdef __cplusplus
extern "C" {
#endif

PyObject* kth_py_native_chain_abla_set_max(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_abla_default_config(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_abla_validate_config(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_abla_block_size_limit(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_abla_validate_state(PyObject* self, PyObject* args, PyObject* kwds);

extern PyMethodDef kth_py_native_chain_abla_methods[];

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_PY_NATIVE_CHAIN_ABLA_H_
