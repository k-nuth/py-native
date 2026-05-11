// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/py-native/wallet/mnemonic.h>

#include <string.h>
#include <kth/capi.h>
#include <kth/capi/wallet/mnemonic.h>
#include <kth/py-native/capsule_names.h>
#include <kth/py-native/utils.h>

#ifdef __cplusplus
extern "C" {
#endif

PyObject*
kth_py_native_wallet_mnemonic_create_mnemonic(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"entropy", (char*)"lexicon", NULL};
    char const* entropy_buf = NULL;
    Py_ssize_t entropy_size = 0;
    PyObject* py_lexicon = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "y#O", kwlist, &entropy_buf, &entropy_size, &py_lexicon)) {
        return NULL;
    }
    kth_dictionary_const_t lexicon_handle = (kth_dictionary_const_t)PyCapsule_GetPointer(py_lexicon, KTH_PY_CAPSULE_WALLET_DICTIONARY);
    if (lexicon_handle == NULL) return NULL;
    auto const result = kth_wallet_mnemonic_create_mnemonic((uint8_t const*)entropy_buf, (kth_size_t)entropy_size, lexicon_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL list returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CORE_STRING_LIST, NULL);
    if (capsule == NULL) {
        kth_core_string_list_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_wallet_mnemonic_validate_mnemonic_dictionary(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"words", (char*)"lexicon", NULL};
    PyObject* py_words = NULL;
    PyObject* py_lexicon = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_words, &py_lexicon)) {
        return NULL;
    }
    kth_string_list_const_t words_handle = (kth_string_list_const_t)PyCapsule_GetPointer(py_words, KTH_PY_CAPSULE_CORE_STRING_LIST);
    if (words_handle == NULL) return NULL;
    kth_dictionary_const_t lexicon_handle = (kth_dictionary_const_t)PyCapsule_GetPointer(py_lexicon, KTH_PY_CAPSULE_WALLET_DICTIONARY);
    if (lexicon_handle == NULL) return NULL;
    auto const result = kth_wallet_mnemonic_validate_mnemonic_dictionary(words_handle, lexicon_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_wallet_mnemonic_validate_mnemonic_dictionary_list(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"mnemonic", (char*)"lexicons", NULL};
    PyObject* py_mnemonic = NULL;
    PyObject* py_lexicons = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_mnemonic, &py_lexicons)) {
        return NULL;
    }
    kth_string_list_const_t mnemonic_handle = (kth_string_list_const_t)PyCapsule_GetPointer(py_mnemonic, KTH_PY_CAPSULE_CORE_STRING_LIST);
    if (mnemonic_handle == NULL) return NULL;
    kth_dictionary_list_const_t lexicons_handle = (kth_dictionary_list_const_t)PyCapsule_GetPointer(py_lexicons, KTH_PY_CAPSULE_WALLET_DICTIONARY_LIST);
    if (lexicons_handle == NULL) return NULL;
    auto const result = kth_wallet_mnemonic_validate_mnemonic_dictionary_list(mnemonic_handle, lexicons_handle);
    return PyBool_FromLong((long)result);
}

PyMethodDef kth_py_native_wallet_mnemonic_methods[] = {
    {"wallet_mnemonic_create_mnemonic", (PyCFunction)kth_py_native_wallet_mnemonic_create_mnemonic, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_mnemonic_validate_mnemonic_dictionary", (PyCFunction)kth_py_native_wallet_mnemonic_validate_mnemonic_dictionary, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wallet_mnemonic_validate_mnemonic_dictionary_list", (PyCFunction)kth_py_native_wallet_mnemonic_validate_mnemonic_dictionary_list, METH_VARARGS | METH_KEYWORDS, NULL},
    {NULL, NULL, 0, NULL}  // sentinel
};

#ifdef __cplusplus
} // extern "C"
#endif
