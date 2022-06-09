// Copyright (c) 2016-2022 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/py-native/word_list.h>
#include <kth/capi.h>
#include <kth/py-native/utils.h> //TODO(fernando): poner bien el dir del header

#ifdef __cplusplus
extern "C" {
#endif

// word_list_t word_list_construct() {
// void point_list_destruct(word_list_t word_list) {
// void word_list_add_word(word_list_t word_list, char const* word) {

PyObject* kth_py_native_word_list_construct(PyObject* self, PyObject* args) {
    word_list_t wl = word_list_construct();

    return to_py_obj(wl);

}

PyObject* kth_py_native_word_list_destruct(PyObject* self, PyObject* args) {
    PyObject* py_wl;

    if ( ! PyArg_ParseTuple(args, "O", &py_wl))
        return NULL;

    word_list_t wl = (word_list_t)get_ptr(py_wl);

    word_list_destruct(wl);
    Py_RETURN_NONE;
}

PyObject* kth_py_native_word_list_add_word(PyObject* self, PyObject* args) {
    PyObject* py_wl;
    char const* word;

    if ( ! PyArg_ParseTuple(args, "Os", &py_wl, &word))
        return NULL;

    word_list_t wl = (word_list_t)get_ptr(py_wl);

    word_list_add_word(wl, word);
    Py_RETURN_NONE;
}


#ifdef __cplusplus
} //extern "C"
#endif
