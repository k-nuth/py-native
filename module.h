// Copyright (c) 2016-2022 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_PY_NATIVE_MODULE_H_
#define KTH_PY_NATIVE_MODULE_H_

#include <Python.h>

#ifdef __cplusplus
extern "C" {
#endif

PyObject* kth_py_native_executor_construct(PyObject* self, PyObject* args);
PyObject* kth_py_native_executor_destruct(PyObject* self, PyObject* args);
PyObject* kth_py_native_executor_initchain(PyObject* self, PyObject* args);
PyObject* kth_py_native_executor_run(PyObject* self, PyObject* args);
PyObject* kth_py_native_executor_run_wait(PyObject* self, PyObject* args);
PyObject* kth_py_native_executor_stopped(PyObject* self, PyObject* args);
PyObject* kth_py_native_executor_stop(PyObject* self, PyObject* args);
PyObject* kth_py_native_executor_get_chain(PyObject* self, PyObject* args);
PyObject* kth_py_native_executor_get_p2p(PyObject* self, PyObject* args);
PyObject* kth_py_native_wallet_mnemonics_to_seed(PyObject* self, PyObject* args);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_PY_NATIVE_MODULE_H_
