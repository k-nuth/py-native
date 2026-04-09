// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

// AUTO-GENERATED — do not edit. Run generate_capi_v2.py to regenerate.
//
// One `KTH_PY_CAPSULE_<GROUP>_<CLASS>` macro per migrated class and
// per generated list. The per-class .cpp files include this header
// and reference the macros by name, so cross-class PyCapsule_New /
// PyCapsule_GetPointer calls stay in sync automatically.
//
// Each per-class .cpp also defines a PyCapsule destructor function
// (`kth_py_native_<group>_<class>_capsule_dtor`) so owned handles
// free their native resources on GC. This header forward-declares
// every destructor so any wrapper that returns an owned handle of
// a foreign class can reference the right one by name.

#ifndef KTH_PY_NATIVE_CAPSULE_NAMES_H_
#define KTH_PY_NATIVE_CAPSULE_NAMES_H_

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#ifdef __cplusplus
extern "C" {
#endif

#define KTH_PY_CAPSULE_CHAIN_BLOCK "kth.chain.block"
#define KTH_PY_CAPSULE_CHAIN_BLOCK_INDEXES "kth.chain.block_indexes"
#define KTH_PY_CAPSULE_CHAIN_BLOCK_LIST "kth.chain.block_list"
#define KTH_PY_CAPSULE_CHAIN_CHAIN_STATE "kth.chain.chain_state"
#define KTH_PY_CAPSULE_CHAIN_DATA_STACK "kth.chain.data_stack"
#define KTH_PY_CAPSULE_CHAIN_HEADER "kth.chain.header"
#define KTH_PY_CAPSULE_CHAIN_INPUT "kth.chain.input"
#define KTH_PY_CAPSULE_CHAIN_INPUT_LIST "kth.chain.input_list"
#define KTH_PY_CAPSULE_CHAIN_OPERATION "kth.chain.operation"
#define KTH_PY_CAPSULE_CHAIN_OPERATION_LIST "kth.chain.operation_list"
#define KTH_PY_CAPSULE_CHAIN_OUTPUT "kth.chain.output"
#define KTH_PY_CAPSULE_CHAIN_OUTPUT_LIST "kth.chain.output_list"
#define KTH_PY_CAPSULE_CHAIN_OUTPUT_POINT "kth.chain.output_point"
#define KTH_PY_CAPSULE_CHAIN_OUTPUT_POINT_LIST "kth.chain.output_point_list"
#define KTH_PY_CAPSULE_CHAIN_POINT "kth.chain.point"
#define KTH_PY_CAPSULE_CHAIN_POINT_LIST "kth.chain.point_list"
#define KTH_PY_CAPSULE_CHAIN_SCRIPT "kth.chain.script"
#define KTH_PY_CAPSULE_CHAIN_TRANSACTION "kth.chain.transaction"
#define KTH_PY_CAPSULE_CHAIN_TRANSACTION_LIST "kth.chain.transaction_list"
#define KTH_PY_CAPSULE_CORE_HASH_LIST "kth.core.hash_list"
#define KTH_PY_CAPSULE_WALLET_EC_COMPRESSED_LIST "kth.wallet.ec_compressed_list"
#define KTH_PY_CAPSULE_WALLET_PAYMENT_ADDRESS "kth.wallet.payment_address"
#define KTH_PY_CAPSULE_WALLET_PAYMENT_ADDRESS_LIST "kth.wallet.payment_address_list"

void kth_py_native_chain_block_capsule_dtor(PyObject* capsule);
void kth_py_native_chain_block_list_capsule_dtor(PyObject* capsule);
void kth_py_native_chain_header_capsule_dtor(PyObject* capsule);
void kth_py_native_chain_input_capsule_dtor(PyObject* capsule);
void kth_py_native_chain_input_list_capsule_dtor(PyObject* capsule);
void kth_py_native_chain_output_capsule_dtor(PyObject* capsule);
void kth_py_native_chain_output_list_capsule_dtor(PyObject* capsule);
void kth_py_native_chain_output_point_capsule_dtor(PyObject* capsule);
void kth_py_native_chain_output_point_list_capsule_dtor(PyObject* capsule);
void kth_py_native_chain_point_capsule_dtor(PyObject* capsule);
void kth_py_native_chain_point_list_capsule_dtor(PyObject* capsule);
void kth_py_native_chain_script_capsule_dtor(PyObject* capsule);
void kth_py_native_chain_transaction_capsule_dtor(PyObject* capsule);
void kth_py_native_chain_transaction_list_capsule_dtor(PyObject* capsule);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_PY_NATIVE_CAPSULE_NAMES_H_
