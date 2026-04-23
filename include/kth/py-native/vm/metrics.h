// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_PY_NATIVE_VM_METRICS_H_
#define KTH_PY_NATIVE_VM_METRICS_H_

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#ifdef __cplusplus
extern "C" {
#endif

PyObject* kth_py_native_vm_metrics_copy(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_metrics_destruct(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_metrics_sig_checks(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_metrics_op_cost(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_metrics_hash_digest_iterations(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_metrics_add_op_cost(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_vm_metrics_add_push_op(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_vm_metrics_add_hash_iterations(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_vm_metrics_add_sig_checks(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_vm_metrics_is_over_op_cost_limit(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_vm_metrics_is_over_op_cost_limit_simple(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_metrics_is_over_hash_iters_limit(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_metrics_has_valid_script_limits(PyObject* self, PyObject* arg);
PyObject* kth_py_native_vm_metrics_set_script_limits(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_vm_metrics_set_native_script_limits(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_vm_metrics_composite_op_cost_script_flags(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_vm_metrics_composite_op_cost_bool(PyObject* self, PyObject* args, PyObject* kwds);

extern PyMethodDef kth_py_native_vm_metrics_methods[];

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_PY_NATIVE_VM_METRICS_H_
