// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/py-native/wallet/language.h>

#include <string.h>
#include <kth/capi.h>
#include <kth/capi/wallet/language.h>
#include <kth/py-native/capsule_names.h>
#include <kth/py-native/utils.h>

#ifdef __cplusplus
extern "C" {
#endif

PyObject*
kth_py_native_wallet_language_en(PyObject* self, PyObject* Py_UNUSED(args)) {
    auto const result = kth_wallet_language_en();
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
        return NULL;
    }
    return PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_DICTIONARY, NULL);
}

PyObject*
kth_py_native_wallet_language_es(PyObject* self, PyObject* Py_UNUSED(args)) {
    auto const result = kth_wallet_language_es();
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
        return NULL;
    }
    return PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_DICTIONARY, NULL);
}

PyObject*
kth_py_native_wallet_language_ja(PyObject* self, PyObject* Py_UNUSED(args)) {
    auto const result = kth_wallet_language_ja();
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
        return NULL;
    }
    return PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_DICTIONARY, NULL);
}

PyObject*
kth_py_native_wallet_language_it(PyObject* self, PyObject* Py_UNUSED(args)) {
    auto const result = kth_wallet_language_it();
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
        return NULL;
    }
    return PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_DICTIONARY, NULL);
}

PyObject*
kth_py_native_wallet_language_fr(PyObject* self, PyObject* Py_UNUSED(args)) {
    auto const result = kth_wallet_language_fr();
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
        return NULL;
    }
    return PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_DICTIONARY, NULL);
}

PyObject*
kth_py_native_wallet_language_cs(PyObject* self, PyObject* Py_UNUSED(args)) {
    auto const result = kth_wallet_language_cs();
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
        return NULL;
    }
    return PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_DICTIONARY, NULL);
}

PyObject*
kth_py_native_wallet_language_ru(PyObject* self, PyObject* Py_UNUSED(args)) {
    auto const result = kth_wallet_language_ru();
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
        return NULL;
    }
    return PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_DICTIONARY, NULL);
}

PyObject*
kth_py_native_wallet_language_uk(PyObject* self, PyObject* Py_UNUSED(args)) {
    auto const result = kth_wallet_language_uk();
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
        return NULL;
    }
    return PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_DICTIONARY, NULL);
}

PyObject*
kth_py_native_wallet_language_zh_Hans(PyObject* self, PyObject* Py_UNUSED(args)) {
    auto const result = kth_wallet_language_zh_Hans();
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
        return NULL;
    }
    return PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_DICTIONARY, NULL);
}

PyObject*
kth_py_native_wallet_language_zh_Hant(PyObject* self, PyObject* Py_UNUSED(args)) {
    auto const result = kth_wallet_language_zh_Hant();
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
        return NULL;
    }
    return PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_DICTIONARY, NULL);
}

PyObject*
kth_py_native_wallet_language_all(PyObject* self, PyObject* Py_UNUSED(args)) {
    auto const result = kth_wallet_language_all();
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
        return NULL;
    }
    return PyCapsule_New((void*)result, KTH_PY_CAPSULE_WALLET_DICTIONARY_LIST, NULL);
}

PyMethodDef kth_py_native_wallet_language_methods[] = {
    {"wallet_language_en", (PyCFunction)kth_py_native_wallet_language_en, METH_NOARGS, NULL},
    {"wallet_language_es", (PyCFunction)kth_py_native_wallet_language_es, METH_NOARGS, NULL},
    {"wallet_language_ja", (PyCFunction)kth_py_native_wallet_language_ja, METH_NOARGS, NULL},
    {"wallet_language_it", (PyCFunction)kth_py_native_wallet_language_it, METH_NOARGS, NULL},
    {"wallet_language_fr", (PyCFunction)kth_py_native_wallet_language_fr, METH_NOARGS, NULL},
    {"wallet_language_cs", (PyCFunction)kth_py_native_wallet_language_cs, METH_NOARGS, NULL},
    {"wallet_language_ru", (PyCFunction)kth_py_native_wallet_language_ru, METH_NOARGS, NULL},
    {"wallet_language_uk", (PyCFunction)kth_py_native_wallet_language_uk, METH_NOARGS, NULL},
    {"wallet_language_zh_Hans", (PyCFunction)kth_py_native_wallet_language_zh_Hans, METH_NOARGS, NULL},
    {"wallet_language_zh_Hant", (PyCFunction)kth_py_native_wallet_language_zh_Hant, METH_NOARGS, NULL},
    {"wallet_language_all", (PyCFunction)kth_py_native_wallet_language_all, METH_NOARGS, NULL},
    {NULL, NULL, 0, NULL}  // sentinel
};

#ifdef __cplusplus
} // extern "C"
#endif
