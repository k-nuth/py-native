// Copyright (c) 2016-2022 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <Python.h>
#include "node.h"
#include "utils.h"

#include <kth/capi.h>

#ifdef __cplusplus
extern "C" {
#endif

PyObject* kth_py_native_node_construct(PyObject* self, PyObject* args) {
    char const* path;
    PyObject* py_out;
    PyObject* py_err;


    if ( ! PyArg_ParseTuple(args, "sOO", &path, &py_out, &py_err))
        return NULL;

#if PY_MAJOR_VERSION >= 3
    int sout_fd = py_out == Py_None ? -1 : PyObject_AsFileDescriptor(py_out);
    int serr_fd = py_err == Py_None ? -1 : PyObject_AsFileDescriptor(py_err);

    kth_node_t node = kth_node_construct_fd(path, sout_fd, serr_fd);
    return PyCapsule_New(node, NULL, NULL);

#else /* PY_MAJOR_VERSION >= 3 */
    FILE* sout = py_out == Py_None ? NULL : PyFile_AsFile(py_out);
    FILE* serr = py_err == Py_None ? NULL : PyFile_AsFile(py_err);
//    PyFile_IncUseCount(p);
///* ... */
//    Py_BEGIN_ALLOW_THREADS
//        do_something(fp);
//    Py_END_ALLOW_THREADS
///* ... */
//        PyFile_DecUseCount(p);

    kth_node_t node = kth_node_construct(path, sout, serr);
    return PyCObject_FromVoidPtr(node, NULL);

#endif /* PY_MAJOR_VERSION >= 3 */

}

PyObject* kth_py_native_node_destruct(PyObject* self, PyObject* args) {
    PyObject* py_node;

    // PyGILState_STATE gstate;
    // gstate = PyGILState_Ensure();

    if ( ! PyArg_ParseTuple(args, "O", &py_node))
        return NULL;

    kth_node_t node = cast_node(py_node);

    kth_node_destruct(node);
    // PyGILState_Release(gstate);
    Py_RETURN_NONE;
}

PyObject* kth_py_native_node_initchain(PyObject* self, PyObject* args) {

    PyObject* py_node;

    if ( ! PyArg_ParseTuple(args, "O", &py_node)) {
        return NULL;
    }

    kth_node_t node = cast_node(py_node);

    int res = kth_node_initchain(node);

    return Py_BuildValue("i", res);
}

void kth_node_run_handler(kth_node_t node, void* ctx, int error) {

    PyObject* py_callback = (PyObject*)ctx;

    PyObject* arglist = Py_BuildValue("(i)", error);
    PyObject_CallObject(py_callback, arglist);
    Py_DECREF(arglist);
    Py_XDECREF(py_callback);  // Dispose of the call
}

PyObject* kth_py_native_node_run(PyObject* self, PyObject* args) {
    PyObject* py_node;
    PyObject* py_callback;

    if ( ! PyArg_ParseTuple(args, "OO:set_callback", &py_node, &py_callback)) {
        return NULL;
    }

    if ( ! PyCallable_Check(py_callback)) {
        PyErr_SetString(PyExc_TypeError, "parameter must be callable");
        return NULL;
    }

    kth_node_t node = cast_node(py_node);
    Py_XINCREF(py_callback);         // Add a reference to new callback
    kth_node_run(node, py_callback, kth_node_run_handler);
    Py_RETURN_NONE;
}

PyObject* kth_py_native_node_run_wait(PyObject* self, PyObject* args) {
    PyObject* py_node;

    if ( ! PyArg_ParseTuple(args, "O", &py_node))
        return NULL;

    kth_node_t node = cast_node(py_node);

    int res = kth_node_run_wait(node);
    return Py_BuildValue("i", res);
}

PyObject* kth_py_native_node_stopped(PyObject* self, PyObject* args) {
    PyObject* py_node;

    if ( ! PyArg_ParseTuple(args, "O", &py_node))
        return NULL;

    kth_node_t node = cast_node(py_node);

    int res = kth_node_stopped(node);
    return Py_BuildValue("i", res);
}

PyObject* kth_py_native_node_stop(PyObject* self, PyObject* args) {
    PyObject* py_node;

    // PyGILState_STATE gstate;
    // gstate = PyGILState_Ensure();

    if ( ! PyArg_ParseTuple(args, "O", &py_node))
        return NULL;

    kth_node_t node = cast_node(py_node);

    kth_node_stop(node);

    // PyGILState_Release(gstate);
    Py_RETURN_NONE;
}

PyObject* kth_py_native_node_get_chain(PyObject* self, PyObject* args) {
    PyObject* py_node;
    if ( ! PyArg_ParseTuple(args, "O", &py_node))
        return NULL;

    kth_node_t node = cast_node(py_node);
    kth_chain_t chain = kth_node_get_chain(node);

    PyObject* py_chain = to_py_obj(chain);
    return Py_BuildValue("O", py_chain);
}

PyObject* kth_py_native_node_get_p2p(PyObject* self, PyObject* args) {
    PyObject* py_node;
    if ( ! PyArg_ParseTuple(args, "O", &py_node))
        return NULL;

    kth_node_t node = cast_node(py_node);
    kth_p2p_t p2p = kth_node_get_p2p(node);

    PyObject* py_p2p = to_py_obj(p2p);
    return Py_BuildValue("O", py_p2p);
}

#ifdef __cplusplus
} // extern "C"
#endif
