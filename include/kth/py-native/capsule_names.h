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
#define KTH_PY_CAPSULE_CHAIN_BLOCK_LIST "kth.chain.block_list"
#define KTH_PY_CAPSULE_CHAIN_CHAIN_STATE "kth.chain.chain_state"
#define KTH_PY_CAPSULE_CHAIN_COMPACT_BLOCK "kth.chain.compact_block"
#define KTH_PY_CAPSULE_CHAIN_DATA_STACK "kth.chain.data_stack"
#define KTH_PY_CAPSULE_CHAIN_DOUBLE_SPEND_PROOF "kth.chain.double_spend_proof"
#define KTH_PY_CAPSULE_CHAIN_DOUBLE_SPEND_PROOF_SPENDER "kth.chain.double_spend_proof_spender"
#define KTH_PY_CAPSULE_CHAIN_GET_BLOCKS "kth.chain.get_blocks"
#define KTH_PY_CAPSULE_CHAIN_GET_HEADERS "kth.chain.get_headers"
#define KTH_PY_CAPSULE_CHAIN_HEADER "kth.chain.header"
#define KTH_PY_CAPSULE_CHAIN_HISTORY_COMPACT "kth.chain.history_compact"
#define KTH_PY_CAPSULE_CHAIN_HISTORY_COMPACT_LIST "kth.chain.history_compact_list"
#define KTH_PY_CAPSULE_CHAIN_INPUT "kth.chain.input"
#define KTH_PY_CAPSULE_CHAIN_INPUT_LIST "kth.chain.input_list"
#define KTH_PY_CAPSULE_CHAIN_MERKLE_BLOCK "kth.chain.merkle_block"
#define KTH_PY_CAPSULE_CHAIN_METRICS "kth.chain.metrics"
#define KTH_PY_CAPSULE_CHAIN_OPERATION "kth.chain.operation"
#define KTH_PY_CAPSULE_CHAIN_OPERATION_LIST "kth.chain.operation_list"
#define KTH_PY_CAPSULE_CHAIN_OUTPUT "kth.chain.output"
#define KTH_PY_CAPSULE_CHAIN_OUTPUT_LIST "kth.chain.output_list"
#define KTH_PY_CAPSULE_CHAIN_OUTPUT_POINT "kth.chain.output_point"
#define KTH_PY_CAPSULE_CHAIN_OUTPUT_POINT_LIST "kth.chain.output_point_list"
#define KTH_PY_CAPSULE_CHAIN_POINT "kth.chain.point"
#define KTH_PY_CAPSULE_CHAIN_POINT_LIST "kth.chain.point_list"
#define KTH_PY_CAPSULE_CHAIN_PREFILLED_TRANSACTION "kth.chain.prefilled_transaction"
#define KTH_PY_CAPSULE_CHAIN_PREFILLED_TRANSACTION_LIST "kth.chain.prefilled_transaction_list"
#define KTH_PY_CAPSULE_CHAIN_SCRIPT "kth.chain.script"
#define KTH_PY_CAPSULE_CHAIN_STEALTH_COMPACT "kth.chain.stealth_compact"
#define KTH_PY_CAPSULE_CHAIN_STEALTH_COMPACT_LIST "kth.chain.stealth_compact_list"
#define KTH_PY_CAPSULE_CHAIN_TOKEN_DATA "kth.chain.token_data"
#define KTH_PY_CAPSULE_CHAIN_TRANSACTION "kth.chain.transaction"
#define KTH_PY_CAPSULE_CHAIN_TRANSACTION_LIST "kth.chain.transaction_list"
#define KTH_PY_CAPSULE_CHAIN_UTXO "kth.chain.utxo"
#define KTH_PY_CAPSULE_CHAIN_UTXO_LIST "kth.chain.utxo_list"
#define KTH_PY_CAPSULE_CORE_BINARY "kth.core.binary"
#define KTH_PY_CAPSULE_CORE_BOOL_LIST "kth.core.bool_list"
#define KTH_PY_CAPSULE_CORE_HASH_LIST "kth.core.hash_list"
#define KTH_PY_CAPSULE_CORE_STRING_LIST "kth.core.string_list"
#define KTH_PY_CAPSULE_CORE_U64_LIST "kth.core.u64_list"
#define KTH_PY_CAPSULE_VM_DEBUG_SNAPSHOT "kth.vm.debug_snapshot"
#define KTH_PY_CAPSULE_VM_DEBUG_SNAPSHOT_LIST "kth.vm.debug_snapshot_list"
#define KTH_PY_CAPSULE_VM_INTERPRETER "kth.vm.interpreter"
#define KTH_PY_CAPSULE_VM_PROGRAM "kth.vm.program"
#define KTH_PY_CAPSULE_WALLET_EC_COMPRESSED_LIST "kth.wallet.ec_compressed_list"
#define KTH_PY_CAPSULE_WALLET_EC_PRIVATE "kth.wallet.ec_private"
#define KTH_PY_CAPSULE_WALLET_EC_PUBLIC "kth.wallet.ec_public"
#define KTH_PY_CAPSULE_WALLET_HD_PRIVATE "kth.wallet.hd_private"
#define KTH_PY_CAPSULE_WALLET_HD_PUBLIC "kth.wallet.hd_public"
#define KTH_PY_CAPSULE_WALLET_PAYMENT_ADDRESS "kth.wallet.payment_address"
#define KTH_PY_CAPSULE_WALLET_PAYMENT_ADDRESS_LIST "kth.wallet.payment_address_list"
#define KTH_PY_CAPSULE_WALLET_WALLET_DATA "kth.wallet.wallet_data"

void kth_py_native_chain_block_capsule_dtor(PyObject* capsule);
void kth_py_native_chain_block_list_capsule_dtor(PyObject* capsule);
void kth_py_native_chain_compact_block_capsule_dtor(PyObject* capsule);
void kth_py_native_chain_double_spend_proof_capsule_dtor(PyObject* capsule);
void kth_py_native_chain_double_spend_proof_spender_capsule_dtor(PyObject* capsule);
void kth_py_native_chain_get_blocks_capsule_dtor(PyObject* capsule);
void kth_py_native_chain_get_headers_capsule_dtor(PyObject* capsule);
void kth_py_native_chain_header_capsule_dtor(PyObject* capsule);
void kth_py_native_chain_history_compact_capsule_dtor(PyObject* capsule);
void kth_py_native_chain_history_compact_list_capsule_dtor(PyObject* capsule);
void kth_py_native_chain_input_capsule_dtor(PyObject* capsule);
void kth_py_native_chain_input_list_capsule_dtor(PyObject* capsule);
void kth_py_native_chain_merkle_block_capsule_dtor(PyObject* capsule);
void kth_py_native_chain_operation_capsule_dtor(PyObject* capsule);
void kth_py_native_chain_operation_list_capsule_dtor(PyObject* capsule);
void kth_py_native_chain_output_capsule_dtor(PyObject* capsule);
void kth_py_native_chain_output_list_capsule_dtor(PyObject* capsule);
void kth_py_native_chain_output_point_capsule_dtor(PyObject* capsule);
void kth_py_native_chain_output_point_list_capsule_dtor(PyObject* capsule);
void kth_py_native_chain_point_capsule_dtor(PyObject* capsule);
void kth_py_native_chain_point_list_capsule_dtor(PyObject* capsule);
void kth_py_native_chain_prefilled_transaction_capsule_dtor(PyObject* capsule);
void kth_py_native_chain_prefilled_transaction_list_capsule_dtor(PyObject* capsule);
void kth_py_native_chain_script_capsule_dtor(PyObject* capsule);
void kth_py_native_chain_stealth_compact_capsule_dtor(PyObject* capsule);
void kth_py_native_chain_stealth_compact_list_capsule_dtor(PyObject* capsule);
void kth_py_native_chain_token_data_capsule_dtor(PyObject* capsule);
void kth_py_native_chain_transaction_capsule_dtor(PyObject* capsule);
void kth_py_native_chain_transaction_list_capsule_dtor(PyObject* capsule);
void kth_py_native_chain_utxo_capsule_dtor(PyObject* capsule);
void kth_py_native_chain_utxo_list_capsule_dtor(PyObject* capsule);
void kth_py_native_core_binary_capsule_dtor(PyObject* capsule);
void kth_py_native_vm_debug_snapshot_capsule_dtor(PyObject* capsule);
void kth_py_native_vm_debug_snapshot_list_capsule_dtor(PyObject* capsule);
void kth_py_native_vm_program_capsule_dtor(PyObject* capsule);
void kth_py_native_wallet_ec_private_capsule_dtor(PyObject* capsule);
void kth_py_native_wallet_ec_public_capsule_dtor(PyObject* capsule);
void kth_py_native_wallet_hd_private_capsule_dtor(PyObject* capsule);
void kth_py_native_wallet_hd_public_capsule_dtor(PyObject* capsule);
void kth_py_native_wallet_payment_address_capsule_dtor(PyObject* capsule);
void kth_py_native_wallet_payment_address_list_capsule_dtor(PyObject* capsule);
void kth_py_native_wallet_wallet_data_capsule_dtor(PyObject* capsule);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_PY_NATIVE_CAPSULE_NAMES_H_
