#ifndef KTH_PY_NATIVE_CHAIN_OUTPUT_LIST_H_
#define KTH_PY_NATIVE_CHAIN_OUTPUT_LIST_H_

#include <Python.h>
#include <kth/capi.h>
#include <kth/py-native/utils.h>

#ifdef __cplusplus
extern "C" {
#endif

PyObject* kth_py_native_output_list_push_back(PyObject* self, PyObject* args);
PyObject* kth_py_native_output_list_count(PyObject* self, PyObject* args);
PyObject* kth_py_native_output_list_nth(PyObject* self, PyObject* args);


#ifdef __cplusplus
} //extern "C"
#endif

#endif
