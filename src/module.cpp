// Copyright (c) 2016-2022 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

//TODO: migrate to the new API for Extension Modules
//          https://docs.python.org/3/howto/cporting.html

#include <Python.h>
#include <kth/py-native/node.h>
// #include <kth/py-native/binary.h>
#include <kth/py-native/utils.h>
#include <kth/py-native/chain/point.h>
#include <kth/py-native/chain/history.h>
#include <kth/py-native/chain/chain.h>
#include <kth/py-native/chain/block.h>
#include <kth/py-native/chain/header.h>
#include <kth/py-native/chain/merkle_block.h>
#include <kth/py-native/chain/word_list.h>
#include <kth/py-native/chain/transaction.h>
#include <kth/py-native/chain/output.h>
#include <kth/py-native/chain/output_list.h>
#include <kth/py-native/chain/input.h>
#include <kth/py-native/chain/input_list.h>
#include <kth/py-native/chain/script.h>
#include <kth/py-native/chain/output_point.h>
#include <kth/py-native/chain/compact_block.h>
#include <kth/py-native/chain/payment_address.h>
#include <kth/py-native/chain/block_list.h>
#include <kth/py-native/chain/transaction_list.h>
#include <kth/py-native/chain/stealth_compact.h>
#include <kth/py-native/chain/stealth_compact_list.h>

#include <kth/py-native/p2p/p2p.h>

#include <kth/capi.h>

#include <iostream>

#ifdef __cplusplus
extern "C" {
#endif


static
PyMethodDef KnuthNativeMethods[] = {

    {"construct",  kth_py_native_node_construct, METH_VARARGS, "Construct the executor object."},
    // {"construct_devnull",  kth_py_native_node_construct_devnull, METH_VARARGS, "Construct the executor object."},
    {"destruct",  kth_py_native_node_destruct, METH_VARARGS, "Destruct the executor object."},
    {"initchain",  kth_py_native_node_initchain, METH_VARARGS, "Directory Initialization."},
    {"run",  kth_py_native_node_run, METH_VARARGS, "Node run."},
    {"run_wait",  kth_py_native_node_run_wait, METH_VARARGS, "Node run."},
    {"stop",  kth_py_native_node_stop, METH_VARARGS, "Node stop."},
    {"stopped",  kth_py_native_node_stopped, METH_VARARGS, "Know if the Node stopped."},
    {"get_chain",  kth_py_native_node_get_chain, METH_VARARGS, "Get Blockchain API."},
    {"get_p2p",  kth_py_native_node_get_p2p, METH_VARARGS, "Get P2P Networking API."},

    {"p2p_address_count",  kth_py_native_p2p_address_count, METH_VARARGS, "..."},
    {"p2p_stop",  kth_py_native_p2p_stop, METH_VARARGS, "..."},
    {"p2p_close",  kth_py_native_p2p_close, METH_VARARGS, "..."},
    {"p2p_stopped",  kth_py_native_p2p_stopped, METH_VARARGS, "..."},

    {"chain_fetch_last_height",  kth_py_native_chain_fetch_last_height, METH_VARARGS, "..."},
    {"chain_fetch_history",  kth_py_native_chain_fetch_history, METH_VARARGS, "..."},
    {"chain_fetch_stealth",  kth_py_native_chain_fetch_stealth, METH_VARARGS, "..."},
    {"chain_fetch_block_height",  kth_py_native_chain_fetch_block_height, METH_VARARGS, "..."},
    {"chain_fetch_block_header_by_height",  kth_py_native_chain_fetch_block_header_by_height, METH_VARARGS, "..."},
    {"chain_fetch_block_header_by_hash",  kth_py_native_chain_fetch_block_header_by_hash, METH_VARARGS, "..."},
    {"chain_fetch_block_by_height",  kth_py_native_chain_fetch_block_by_height, METH_VARARGS, "..."},
    {"chain_fetch_block_by_hash",  kth_py_native_chain_fetch_block_by_hash, METH_VARARGS, "..."},
    {"chain_fetch_merkle_block_by_height",  kth_py_native_chain_fetch_merkle_block_by_height, METH_VARARGS, "..."},
    {"chain_fetch_merkle_block_by_hash",  kth_py_native_chain_fetch_merkle_block_by_hash, METH_VARARGS, "..."},
    {"chain_fetch_transaction",  kth_py_native_chain_fetch_transaction, METH_VARARGS, "..."},

    {"chain_fetch_transaction_position",  kth_py_native_chain_fetch_transaction_position, METH_VARARGS, "..."},
    {"chain_organize_block",  kth_py_native_chain_organize_block, METH_VARARGS, "..."},
    {"chain_organize_transaction",  kth_py_native_chain_organize_transaction, METH_VARARGS, "..."},
    {"chain_validate_tx",  kth_py_native_chain_validate_tx, METH_VARARGS, "..."},
    {"chain_fetch_compact_block_by_height",  kth_py_native_chain_fetch_compact_block_by_height, METH_VARARGS, "..."},
    {"chain_fetch_compact_block_by_hash",  kth_py_native_chain_fetch_compact_block_by_hash, METH_VARARGS, "..."},
    {"chain_fetch_spend",  kth_py_native_chain_fetch_spend, METH_VARARGS, "..."},
    {"chain_subscribe_blockchain",  kth_py_native_chain_subscribe_blockchain, METH_VARARGS, "..."},
    {"chain_subscribe_transaction",  kth_py_native_chain_subscribe_transaction, METH_VARARGS, "..."},
    {"chain_unsubscribe",  kth_py_native_chain_unsubscribe, METH_VARARGS, "..."},

    {"transaction_factory_from_data",  kth_py_native_chain_transaction_factory_from_data, METH_VARARGS, "..."},
    {"transaction_version",  kth_py_native_chain_transaction_version, METH_VARARGS, "..."},
    {"transaction_set_version",  kth_py_native_chain_transaction_set_version, METH_VARARGS, "..."},
    {"transaction_hash",  kth_py_native_chain_transaction_hash, METH_VARARGS, "..."},
    {"transaction_hash_sighash_type",  kth_py_native_chain_transaction_hash_sighash_type, METH_VARARGS, "..."},
    {"transaction_locktime",  kth_py_native_chain_transaction_locktime, METH_VARARGS, "..."},
    {"transaction_serialized_size",  kth_py_native_chain_transaction_serialized_size, METH_VARARGS, "..."},
    {"transaction_fees",  kth_py_native_chain_transaction_fees, METH_VARARGS, "..."},
    {"transaction_signature_operations",  kth_py_native_chain_transaction_signature_operations, METH_VARARGS, "..."},
    {"transaction_signature_operations_bip16_active",  kth_py_native_chain_transaction_signature_operations_bip16_active, METH_VARARGS, "..."},
    {"transaction_total_input_value",  kth_py_native_chain_transaction_total_input_value, METH_VARARGS, "..."},
    {"transaction_total_output_value",  kth_py_native_chain_transaction_total_output_value, METH_VARARGS, "..."},
    {"transaction_is_coinbase",  kth_py_native_chain_transaction_is_coinbase, METH_VARARGS, "..."},
    {"transaction_is_null_non_coinbase",  kth_py_native_chain_transaction_is_null_non_coinbase, METH_VARARGS, "..."},
    {"transaction_is_oversized_coinbase",  kth_py_native_chain_transaction_is_oversized_coinbase, METH_VARARGS, "..."},
    {"transaction_is_mature",  kth_py_native_chain_transaction_is_mature, METH_VARARGS, "..."},
    {"transaction_is_overspent",  kth_py_native_chain_transaction_is_overspent, METH_VARARGS, "..."},
    {"transaction_is_double_spend",  kth_py_native_chain_transaction_is_double_spend, METH_VARARGS, "..."},
    {"transaction_is_missing_previous_outputs",  kth_py_native_chain_transaction_is_missing_previous_outputs, METH_VARARGS, "..."},
    {"transaction_is_final",  kth_py_native_chain_transaction_is_final, METH_VARARGS, "..."},
    {"transaction_is_locktime_conflict",  kth_py_native_chain_transaction_is_locktime_conflict, METH_VARARGS, "..."},
    {"transaction_outputs",  kth_py_native_chain_transaction_outputs, METH_VARARGS, "..."},
    {"transaction_inputs",  kth_py_native_chain_transaction_inputs, METH_VARARGS, "..."},
    {"transaction_to_data",  kth_py_native_chain_transaction_to_data, METH_VARARGS, "..."},

    {"input_is_valid",  kth_py_native_kth_chain_input_is_valid, METH_VARARGS, "..."},
    {"input_is_final",  kth_py_native_kth_chain_input_is_final, METH_VARARGS, "..."},
    {"input_serialized_size",  kth_py_native_kth_chain_input_serialized_size, METH_VARARGS, "..."},
    {"input_sequence",  kth_py_native_kth_chain_input_sequence, METH_VARARGS, "..."},
    {"input_signature_operations",  kth_py_native_kth_chain_input_signature_operations, METH_VARARGS, "..."},
    {"input_script",  kth_py_native_kth_chain_input_script, METH_VARARGS, "..."},
    {"input_previous_output",  kth_py_native_kth_chain_input_previous_output, METH_VARARGS, "..."},
    //{"input_get_hash",  kth_py_native_kth_chain_input_get_hash, METH_VARARGS, "..."},
    //{"input_get_index",  kth_py_native_kth_chain_input_get_index, METH_VARARGS, "..."},
    {"input_to_data",  kth_py_native_kth_chain_input_to_data, METH_VARARGS, "..."},

    {"input_list_push_back",  kth_py_native_input_list_push_back, METH_VARARGS, "..."},
    {"input_list_count",  kth_py_native_input_list_count, METH_VARARGS, "..."},
    {"input_list_nth",  kth_py_native_input_list_nth, METH_VARARGS, "..."},

    {"output_is_valid",  kth_py_native_chain_output_is_valid, METH_VARARGS, "..."},
    {"output_serialized_size",  kth_py_native_chain_output_serialized_size, METH_VARARGS, "..."},
    {"output_value",  kth_py_native_chain_output_value, METH_VARARGS, "..."},
    {"output_signature_operations",  kth_py_native_chain_output_signature_operations, METH_VARARGS, "..."},
    {"output_script",  kth_py_native_chain_output_script, METH_VARARGS, "..."},
    //{"output_get_hash",  kth_py_native_chain_output_get_hash, METH_VARARGS, "..."},
    //{"output_get_index",  kth_py_native_chain_output_get_index, METH_VARARGS, "..."},
    {"output_to_data",  kth_py_native_chain_output_to_data, METH_VARARGS, "..."},

    {"output_list_push_back",  kth_py_native_output_list_push_back, METH_VARARGS, "..."},
    {"output_list_count",  kth_py_native_output_list_count, METH_VARARGS, "..."},
    {"output_list_nth",  kth_py_native_output_list_nth, METH_VARARGS, "..."},

    // {"binary_construct",  kth_py_native_binary_construct, METH_VARARGS, "..."},
    // {"binary_construct_string",  kth_py_native_binary_construct_string, METH_VARARGS, "..."},
    // {"binary_construct_blocks",  kth_py_native_binary_construct_blocks, METH_VARARGS, "..."},
    // {"binary_blocks",  kth_py_native_binary_blocks, METH_VARARGS, "..."},
    // {"binary_encoded",  kth_py_native_binary_encoded, METH_VARARGS, "..."},

    {"merkle_block_get_header",  kth_py_native_chain_merkle_block_get_header, METH_VARARGS, "..."},
    {"merkle_block_is_valid",  kth_py_native_chain_merkle_block_is_valid, METH_VARARGS, "..."},
    {"merkle_block_hash_count",  kth_py_native_chain_merkle_block_hash_count, METH_VARARGS, "..."},
    {"merkle_block_serialized_size",  kth_py_native_chain_merkle_block_serialized_size, METH_VARARGS, "..."},
    {"merkle_block_total_transaction_count",  kth_py_native_chain_merkle_block_total_transaction_count, METH_VARARGS, "..."},
    {"merkle_block_reset",  kth_py_native_chain_merkle_block_reset, METH_VARARGS, "..."},

    {"block_get_header",  kth_py_native_chain_block_get_header, METH_VARARGS, "..."},
    {"block_hash",  kth_py_native_chain_block_hash, METH_VARARGS, "..."},

    //TODO(KNUTH-NEW): implement
    // {"block_transaction_count",  kth_py_native_chain_block_transaction_count, METH_VARARGS, "..."},
    // {"block_transaction_nth",  kth_py_native_chain_block_transaction_nth, METH_VARARGS, "..."},

    {"block_serialized_size",  kth_py_native_chain_block_serialized_size, METH_VARARGS, "..."},
    {"block_fees",  kth_py_native_chain_block_fees, METH_VARARGS, "..."},
    {"block_claim",  kth_py_native_chain_block_claim, METH_VARARGS, "..."},
    {"block_reward",  kth_py_native_chain_block_reward, METH_VARARGS, "..."},
    {"block_generate_merkle_root",  kth_py_native_chain_block_generate_merkle_root, METH_VARARGS, "..."},

    {"block_is_valid",  kth_py_native_chain_block_is_valid, METH_VARARGS, "..."},
    {"block_signature_operations",  kth_py_native_chain_block_signature_operations, METH_VARARGS, "..."},
    {"block_signature_operations_bip16_active",  kth_py_native_chain_block_signature_operations_bip16_active, METH_VARARGS, "..."},
    {"block_total_inputs",  kth_py_native_chain_block_total_inputs, METH_VARARGS, "..."},
    {"block_is_extra_coinbases",  kth_py_native_chain_block_is_extra_coinbases, METH_VARARGS, "..."},
    {"block_is_final",  kth_py_native_chain_block_is_final, METH_VARARGS, "..."},
    {"block_is_distinct_transaction_set",  kth_py_native_chain_block_is_distinct_transaction_set, METH_VARARGS, "..."},
    {"block_is_valid_coinbase_claim",  kth_py_native_chain_block_is_valid_coinbase_claim, METH_VARARGS, "..."},
    {"block_is_valid_coinbase_script",  kth_py_native_chain_block_is_valid_coinbase_script, METH_VARARGS, "..."},
    {"block_is_internal_double_spend",  kth_py_native_chain_block_is_internal_double_spend, METH_VARARGS, "..."},
    {"block_is_valid_merkle_root",  kth_py_native_chain_block_is_valid_merkle_root, METH_VARARGS, "..."},

    {"header_get_version",  kth_py_native_chain_header_get_version, METH_VARARGS, "..."},
    {"header_set_version",  kth_py_native_chain_header_set_version, METH_VARARGS, "..."},
    {"header_get_previous_block_hash",  kth_py_native_chain_header_get_previous_block_hash, METH_VARARGS, "..."},
    //{"header_set_previous_block_hash",  kth_py_native_chain_header_set_previous_block_hash, METH_VARARGS, "..."},
    {"header_get_merkle",  kth_py_native_chain_header_get_merkle, METH_VARARGS, "..."},
    //{"header_set_merkle",  kth_py_native_chain_header_set_merkle, METH_VARARGS, "..."},
    {"header_get_hash",  kth_py_native_chain_header_get_hash, METH_VARARGS, "..."},
    {"header_get_timestamp",  kth_py_native_chain_header_get_timestamp, METH_VARARGS, "..."},
    {"header_set_timestamp",  kth_py_native_chain_header_set_timestamp, METH_VARARGS, "..."},
    {"header_get_bits",  kth_py_native_chain_header_get_bits, METH_VARARGS, "..."},
    {"header_set_bits",  kth_py_native_chain_header_set_bits, METH_VARARGS, "..."},
    {"header_get_nonce",  kth_py_native_chain_header_get_nonce, METH_VARARGS, "..."},
    {"header_set_nonce",  kth_py_native_chain_header_set_nonce, METH_VARARGS, "..."},

    {"history_compact_list_destruct",  kth_py_native_history_compact_list_destruct, METH_VARARGS, "..."},
    {"history_compact_list_count",  kth_py_native_history_compact_list_count, METH_VARARGS, "..."},
    {"history_compact_list_nth",  kth_py_native_history_compact_list_nth, METH_VARARGS, "..."},
    {"history_compact_get_point_kind",  kth_py_native_history_compact_get_point_kind, METH_VARARGS, "..."},
    {"history_compact_get_point",  kth_py_native_history_compact_get_point, METH_VARARGS, "..."},
    {"history_compact_get_height",  kth_py_native_history_compact_get_height, METH_VARARGS, "..."},
    {"history_compact_get_value_or_previous_checksum",  kth_py_native_history_compact_get_value_or_previous_checksum, METH_VARARGS, "..."},

    {"point_get_hash",  kth_py_native_point_get_hash, METH_VARARGS, "..."},
    {"point_is_valid",  kth_py_native_point_is_valid, METH_VARARGS, "..."},
    {"point_get_index",  kth_py_native_point_get_index, METH_VARARGS, "..."},
    {"point_get_checksum",  kth_py_native_point_get_checksum, METH_VARARGS, "..."},

    // {"word_list_construct",  kth_py_native_word_list_construct, METH_VARARGS, "..."},
    // {"word_list_destruct",  kth_py_native_word_list_destruct, METH_VARARGS, "..."},
    // {"word_list_add_word",  kth_py_native_word_list_add_word, METH_VARARGS, "..."},

    // {"wallet_mnemonics_to_seed",  kth_py_native_wallet_mnemonics_to_seed, METH_VARARGS, "..."},
    // {"wallet_ec_new",  kth_py_native_wallet_ec_new, METH_VARARGS, "..."},
    // {"wallet_ec_to_public",  kth_py_native_wallet_ec_to_public, METH_VARARGS, "..."},
    // {"wallet_ec_to_address",  kth_py_native_wallet_ec_to_address, METH_VARARGS, "..."},
    // {"wallet_hd_new",  kth_py_native_wallet_hd_new, METH_VARARGS, "..."},
    // {"wallet_hd_private_to_ec",  kth_py_native_wallet_hd_private_to_ec, METH_VARARGS, "..."},

    {"script_destruct",  kth_py_native_chain_script_destruct, METH_VARARGS, "..."},
    {"script_is_valid",  kth_py_native_chain_script_is_valid, METH_VARARGS, "..."},
    {"script_is_valid_operations",  kth_py_native_chain_script_is_valid_operations, METH_VARARGS, "..."},
    {"script_satoshi_content_size",  kth_py_native_chain_script_satoshi_content_size, METH_VARARGS, "..."},
    {"script_serialized_size",  kth_py_native_chain_script_serialized_size, METH_VARARGS, "..."},
    {"script_to_string",  kth_py_native_chain_script_to_string, METH_VARARGS, "..."},
    {"script_sigops",  kth_py_native_chain_script_sigops, METH_VARARGS, "..."},
    // {"script_sigops",  kth_py_native_chain_script_sigops, METH_VARARGS, "..."},

    {"payment_address_destruct",  kth_py_native_wallet_payment_address_destruct, METH_VARARGS, "..."},
    {"payment_address_encoded",  kth_py_native_wallet_payment_address_encoded, METH_VARARGS, "..."},
    {"payment_address_version",  kth_py_native_wallet_payment_address_version, METH_VARARGS, "..."},
    {"payment_address_construct_from_string",  kth_py_native_wallet_payment_address_construct_from_string, METH_VARARGS, "..."},

    {"output_point_get_hash",  kth_py_native_chain_output_point_get_hash, METH_VARARGS, "..."},
    //{"point_is_valid",  kth_py_native_point_is_valid, METH_VARARGS, "..."},
    {"output_point_get_index",  kth_py_native_chain_output_point_get_index, METH_VARARGS, "..."},
    {"output_point_construct",  kth_py_native_chain_output_point_construct, METH_VARARGS, "..."},
    {"output_point_construct_from_hash_index",  kth_py_native_chain_output_point_construct_from_hash_index, METH_VARARGS, "..."},
    {"output_point_destruct",  kth_py_native_chain_output_point_destruct, METH_VARARGS, "..."},
    //{"point_get_checksum",  kth_py_native_point_get_checksum, METH_VARARGS, "..."},

    {"compact_block_header",  kth_py_native_chain_compact_block_header, METH_VARARGS, "..."},
    {"compact_block_is_valid",  kth_py_native_chain_compact_block_is_valid, METH_VARARGS, "..."},
    {"compact_block_serialized_size",  kth_py_native_chain_compact_block_serialized_size, METH_VARARGS, "..."},
    {"compact_block_transaction_count",  kth_py_native_chain_compact_block_transaction_count, METH_VARARGS, "..."},
    {"compact_block_transaction_nth",  kth_py_native_chain_compact_block_transaction_nth, METH_VARARGS, "..."},
    {"compact_block_nonce",  kth_py_native_chain_compact_block_nonce, METH_VARARGS, "..."},
    {"compact_block_destruct",  kth_py_native_chain_compact_block_destruct, METH_VARARGS, "..."},
    {"compact_block_reset",  kth_py_native_chain_compact_block_reset, METH_VARARGS, "..."},

    {"header_destruct",  kth_py_native_chain_header_destruct, METH_VARARGS, "..."},
    {"block_destruct",  kth_py_native_chain_block_destruct, METH_VARARGS, "..."},
    {"merkle_block_destruct",  kth_py_native_chain_merkle_block_destruct, METH_VARARGS, "..."},
    {"transaction_destruct",  kth_py_native_chain_transaction_destruct, METH_VARARGS, "..."},
    {"output_destruct",  kth_py_native_chain_output_destruct, METH_VARARGS, "..."},
    {"input_destruct",  kth_py_native_kth_chain_input_destruct, METH_VARARGS, "..."},

    {"block_list_construct_default",  kth_py_native_chain_block_list_construct_default, METH_VARARGS, "..."},
    {"block_list_push_back",  kth_py_native_chain_block_list_push_back, METH_VARARGS, "..."},
    {"block_list_destruct",  kth_py_native_chain_block_list_destruct, METH_VARARGS, "..."},
    {"block_list_count",  kth_py_native_chain_block_list_count, METH_VARARGS, "..."},
    {"block_list_nth",  kth_py_native_chain_block_list_nth, METH_VARARGS, "..."},

    {"transaction_list_construct_default",  kth_py_native_chain_transaction_list_construct_default, METH_VARARGS, "..."},
    {"transaction_list_push_back",  kth_py_native_chain_transaction_list_push_back, METH_VARARGS, "..."},
    {"transaction_list_destruct",  kth_py_native_chain_transaction_list_destruct, METH_VARARGS, "..."},
    {"transaction_list_count",  kth_py_native_chain_transaction_list_count, METH_VARARGS, "..."},
    {"transaction_list_nth",  kth_py_native_chain_transaction_list_nth, METH_VARARGS, "..."},

    {"stealth_compact_ephemeral_public_key_hash",  kth_py_native_stealth_compact_get_ephemeral_public_key_hash, METH_VARARGS, "..."},
    {"stealth_compact_get_transaction_hash",  kth_py_native_stealth_compact_get_transaction_hash, METH_VARARGS, "..."},
    {"stealth_compact_get_public_key_hash",  kth_py_native_stealth_compact_get_public_key_hash, METH_VARARGS, "..."},

    {"stealth_compact_list_destruct",  kth_py_native_chain_stealth_compact_list_destruct, METH_VARARGS, "..."},
    {"stealth_compact_list_count",  kth_py_native_chain_stealth_compact_list_count, METH_VARARGS, "..."},
    {"stealth_compact_list_nth",  kth_py_native_chain_stealth_compact_list_nth, METH_VARARGS, "..."},

    //{"long_hash_t_to_str",  kth_py_native_long_hash_t_to_str, METH_VARARGS, "..."},
    //{"long_hash_t_free",  kth_py_native_long_hash_t_free, METH_VARARGS, "..."},

    {NULL, NULL, 0, NULL}        /* Sentinel */
};

struct module_state {
    PyObject *error;
};

#if PY_MAJOR_VERSION >= 3
#define GETSTATE(m) ((struct module_state*)PyModule_GetState(m))
#else //PY_MAJOR_VERSION >= 3
#define GETSTATE(m) (&_state)
static struct module_state _state;
#endif //PY_MAJOR_VERSION >= 3

#if PY_MAJOR_VERSION >= 3

static
int myextension_traverse(PyObject *m, visitproc visit, void *arg) {
    Py_VISIT(GETSTATE(m)->error);
    return 0;
}

static
int myextension_clear(PyObject *m) {
    Py_CLEAR(GETSTATE(m)->error);
    return 0;
}

static
struct PyModuleDef moduledef = {
        PyModuleDef_HEAD_INIT,
        "kth_native",
        NULL,
        sizeof(struct module_state),
        KnuthNativeMethods,
        NULL,
        myextension_traverse,
        myextension_clear,
        NULL
};

#define INITERROR return NULL

PyMODINIT_FUNC
PyInit_kth_native(void)


#else /* PY_MAJOR_VERSION >= 3 */

#define INITERROR return

void /*PyMODINIT_FUNC*/
initkth_native(void)

#endif /* PY_MAJOR_VERSION >= 3 */

{

    // Make sure the GIL has been created since we need to acquire it in our
    // callback to safely call into the python application.
    if (! PyEval_ThreadsInitialized()) {
        PyEval_InitThreads();
    }


#if PY_MAJOR_VERSION >= 3
    PyObject *module = PyModule_Create(&moduledef);
#else
    PyObject *module = Py_InitModule("kth_native", KnuthNativeMethods);
    // (void) Py_InitModule("kth_native", KnuthNativeMethods);
#endif

    if (module == NULL) {
        INITERROR;
    }

    struct module_state *st = GETSTATE(module);

    st->error = PyErr_NewException((char*)"myextension.Error", NULL, NULL);

    if (st->error == NULL) {
        Py_DECREF(module);
        INITERROR;
    }

#if PY_MAJOR_VERSION >= 3
    return module;
#endif
}

#ifdef __cplusplus
} // extern "C"
#endif
