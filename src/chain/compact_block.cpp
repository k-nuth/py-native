#include <kth/py-native/chain/compact_block.h>

#ifdef __cplusplus
extern "C" {
#endif

PyObject* kth_py_native_chain_compact_block_header(PyObject* self, PyObject* args){
    PyObject* py_compact_block;

    if ( ! PyArg_ParseTuple(args, "O", &py_compact_block)) {
        return NULL;
    }

    kth_compact_block_t compact_block = (kth_compact_block_t)get_ptr(py_compact_block);
    kth_header_t header = (kth_header_t)kth_chain_compact_block_header(compact_block);
    return to_py_obj(header);
}

PyObject* kth_py_native_chain_compact_block_is_valid(PyObject* self, PyObject* args){
    PyObject* py_compact_block;

    if ( ! PyArg_ParseTuple(args, "O", &py_compact_block)) {
        return NULL;
    }

    kth_compact_block_t compact_block = (kth_compact_block_t)get_ptr(py_compact_block);
    int res = kth_chain_compact_block_is_valid(compact_block);
    return Py_BuildValue("i", res);
}

PyObject* kth_py_native_chain_compact_block_serialized_size(PyObject* self, PyObject* args){
    PyObject* py_compact_block;
    uint32_t py_version;

    if ( ! PyArg_ParseTuple(args, "OI", &py_compact_block, &py_version)) {
        return NULL;
    }

    kth_compact_block_t compact_block = (kth_compact_block_t)get_ptr(py_compact_block);
    uint64_t res = kth_chain_compact_block_serialized_size(compact_block, py_version);
    return Py_BuildValue("K", res);
}

PyObject* kth_py_native_chain_compact_block_transaction_count(PyObject* self, PyObject* args){
    PyObject* py_compact_block;

    if ( ! PyArg_ParseTuple(args, "O", &py_compact_block)) {
        return NULL;
    }

    kth_compact_block_t compact_block = (kth_compact_block_t)get_ptr(py_compact_block);
    uint64_t res = kth_chain_compact_block_transaction_count(compact_block);
    return Py_BuildValue("K", res);
}

PyObject* kth_py_native_chain_compact_block_transaction_nth(PyObject* self, PyObject* args){
    PyObject* py_compact_block;
    uint64_t py_n;

    if ( ! PyArg_ParseTuple(args, "OI", &py_compact_block, &py_n)) {
        return NULL;
    }

    kth_compact_block_t compact_block = (kth_compact_block_t)get_ptr(py_compact_block);
    kth_transaction_t res = kth_chain_compact_block_transaction_nth(compact_block, py_n);
    return to_py_obj(res);
}

PyObject* kth_py_native_chain_compact_block_nonce(PyObject* self, PyObject* args){
    PyObject* py_compact_block;

    if ( ! PyArg_ParseTuple(args, "O", &py_compact_block)) {
        return NULL;
    }

    kth_compact_block_t compact_block = (kth_compact_block_t)get_ptr(py_compact_block);
    uint64_t res = kth_chain_compact_block_nonce(compact_block);
    return Py_BuildValue("K", res);
}

PyObject* kth_py_native_chain_compact_block_destruct(PyObject* self, PyObject* args){
    PyObject* py_compact_block;

    if ( ! PyArg_ParseTuple(args, "O", &py_compact_block)) {
        return NULL;
    }

    kth_compact_block_t compact_block = (kth_compact_block_t)get_ptr(py_compact_block);
    kth_chain_compact_block_destruct(compact_block);
    Py_RETURN_NONE;
}

PyObject* kth_py_native_chain_compact_block_reset(PyObject* self, PyObject* args){
    PyObject* py_compact_block;

    if ( ! PyArg_ParseTuple(args, "O", &py_compact_block)) {
        return NULL;
    }

    kth_compact_block_t compact_block = (kth_compact_block_t)get_ptr(py_compact_block);
    kth_chain_compact_block_reset(compact_block);
    Py_RETURN_NONE;
}

#ifdef __cplusplus
} //extern "C"
#endif
