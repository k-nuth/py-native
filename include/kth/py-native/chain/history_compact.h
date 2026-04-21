// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_PY_NATIVE_CHAIN_HISTORY_COMPACT_H_
#define KTH_PY_NATIVE_CHAIN_HISTORY_COMPACT_H_

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#ifdef __cplusplus
extern "C" {
#endif

PyObject* kth_py_native_chain_history_compact_copy(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_history_compact_destruct(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_history_compact_kind(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_history_compact_set_kind(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_history_compact_point(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_history_compact_set_point(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_history_compact_height(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_history_compact_set_height(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_history_compact_value_or_previous_checksum(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_history_compact_set_value_or_previous_checksum(PyObject* self, PyObject* args, PyObject* kwds);

extern PyMethodDef kth_py_native_chain_history_compact_methods[];

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_PY_NATIVE_CHAIN_HISTORY_COMPACT_H_
