// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_PY_NATIVE_CHAIN_ABLA_STATE_H_
#define KTH_PY_NATIVE_CHAIN_ABLA_STATE_H_

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#ifdef __cplusplus
extern "C" {
#endif

PyObject* kth_py_native_chain_abla_state_construct_default(PyObject* self, PyObject* args);
PyObject* kth_py_native_chain_abla_state_construct(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_abla_state_copy(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_abla_state_destruct(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_abla_state_block_size(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_abla_state_set_block_size(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_abla_state_control_block_size(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_abla_state_set_control_block_size(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_abla_state_elastic_buffer_size(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_abla_state_set_elastic_buffer_size(PyObject* self, PyObject* args, PyObject* kwds);

extern PyMethodDef kth_py_native_chain_abla_state_methods[];

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_PY_NATIVE_CHAIN_ABLA_STATE_H_
