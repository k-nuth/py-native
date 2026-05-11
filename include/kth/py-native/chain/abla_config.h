// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_PY_NATIVE_CHAIN_ABLA_CONFIG_H_
#define KTH_PY_NATIVE_CHAIN_ABLA_CONFIG_H_

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#ifdef __cplusplus
extern "C" {
#endif

PyObject* kth_py_native_chain_abla_config_copy(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_abla_config_destruct(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_abla_config_epsilon0(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_abla_config_set_epsilon0(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_abla_config_beta0(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_abla_config_set_beta0(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_abla_config_n0(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_abla_config_set_n0(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_abla_config_gamma_reciprocal(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_abla_config_set_gamma_reciprocal(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_abla_config_zeta_xB7(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_abla_config_set_zeta_xB7(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_abla_config_theta_reciprocal(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_abla_config_set_theta_reciprocal(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_abla_config_delta(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_abla_config_set_delta(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_abla_config_epsilon_max(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_abla_config_set_epsilon_max(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* kth_py_native_chain_abla_config_beta_max(PyObject* self, PyObject* arg);
PyObject* kth_py_native_chain_abla_config_set_beta_max(PyObject* self, PyObject* args, PyObject* kwds);

extern PyMethodDef kth_py_native_chain_abla_config_methods[];

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_PY_NATIVE_CHAIN_ABLA_CONFIG_H_
