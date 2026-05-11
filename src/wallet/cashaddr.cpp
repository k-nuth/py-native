// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/py-native/wallet/cashaddr.h>

#include <string.h>
#include <kth/capi.h>
#include <kth/capi/wallet/cashaddr.h>
#include <kth/py-native/capsule_names.h>
#include <kth/py-native/utils.h>

#ifdef __cplusplus
extern "C" {
#endif

PyObject*
kth_py_native_wallet_cashaddr_encode(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"prefix", (char*)"payload", NULL};
    char const* prefix = NULL;
    char const* payload_buf = NULL;
    Py_ssize_t payload_size = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "sy#", kwlist, &prefix, &payload_buf, &payload_size)) {
        return NULL;
    }
    auto const result = kth_wallet_cashaddr_encode(prefix, (uint8_t const*)payload_buf, (kth_size_t)payload_size);
    if (result == NULL) Py_RETURN_NONE;
    PyObject* py_result = Py_BuildValue("s", result);
    kth_core_destruct_string(result);
    return py_result;
}

PyObject*
kth_py_native_wallet_cashaddr_decode(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"str", (char*)"default_prefix", NULL};
    char const* str = NULL;
    char const* default_prefix = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "ss", kwlist, &str, &default_prefix)) {
        return NULL;
    }
    uint8_t* out_payload = NULL;
    kth_size_t out_payload_size = 0;
    auto const result = kth_wallet_cashaddr_decode(str, default_prefix, &out_payload, &out_payload_size);
    if (result == NULL) {
        if (out_payload != NULL) kth_core_destruct_array(out_payload);
        Py_RETURN_NONE;
    }
    PyObject* py_prefix = Py_BuildValue("s", result);
    kth_core_destruct_string(result);
    if (py_prefix == NULL) {
        if (out_payload != NULL) kth_core_destruct_array(out_payload);
        return NULL;
    }
    PyObject* py_payload = Py_BuildValue("y#", out_payload, (Py_ssize_t)out_payload_size);
    kth_core_destruct_array(out_payload);
    if (py_payload == NULL) {
        Py_DECREF(py_prefix);
        return NULL;
    }
    PyObject* py_result = Py_BuildValue("(OO)", py_prefix, py_payload);
    Py_DECREF(py_prefix);
    Py_DECREF(py_payload);
    return py_result;
}

PyMethodDef kth_py_native_wallet_cashaddr_methods[] = {
    {"wallet_cashaddr_encode", (PyCFunction)kth_py_native_wallet_cashaddr_encode, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_cashaddr_decode", (PyCFunction)kth_py_native_wallet_cashaddr_decode, METH_VARARGS | METH_KEYWORDS, NULL},
    {NULL, NULL, 0, NULL}  // sentinel
};

#ifdef __cplusplus
} // extern "C"
#endif
