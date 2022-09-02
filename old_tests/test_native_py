# Copyright (c) 2016-2022 Knuth Project developers.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http:#www.opensource.org/licenses/mit-license.php.


import kth_native
import signal
import sys
import time


def hash_to_str(hash):
    return bytes(reversed(hash)).hex()

def print_authority(authority):
    print(f'ip: {authority.ip}, port: {authority.port}')

def print_endpoint(endpoint):
    print(f'scheme: {endpoint.scheme}, host: {endpoint.host}, port: {endpoint.port}')

def print_node_settings(ns):
    print(ns.sync_peers)
    print(ns.sync_timeout_seconds)
    print(ns.block_latency_seconds)
    print(ns.refresh_transactions)
    print(ns.compact_blocks_high_bandwidth)
    print(ns.ds_proofs_enabled)

def print_database_settings(ds):
    print(ds.directory)
    print(ds.flush_writes)
    print(ds.file_growth_rate)
    print(ds.index_start_height)

    print(ds.reorg_pool_limit)
    print(ds.db_max_size)

    print(ds.safe_mode)
    print(ds.cache_capacity)

def print_blockchain_settings(bs):
    print(bs.cores)
    print(bs.priority)
    print(bs.byte_fee_satoshis)
    print(bs.sigop_fee_satoshis)
    print(bs.minimum_output_satoshis)
    print(bs.notify_limit_hours)
    print(bs.reorganization_limit)

    for c in bs.checkpoints:
        print( hash_to_str(c.hash) )
        print(c.height)

    print(bs.fix_checkpoints)
    print(bs.allow_collisions)
    print(bs.easy_blocks)
    print(bs.retarget)
    print(bs.bip16)
    print(bs.bip30)
    print(bs.bip34)
    print(bs.bip66)
    print(bs.bip65)
    print(bs.bip90)
    print(bs.bip68)
    print(bs.bip112)
    print(bs.bip113)
    print(bs.bch_uahf)
    print(bs.bch_daa_cw144)
    print(bs.bch_pythagoras)
    print(bs.bch_euclid)
    print(bs.bch_pisano)
    print(bs.bch_mersenne)
    print(bs.bch_fermat)
    print(bs.bch_euler)
    print(bs.gauss_activation_time)
    print(bs.descartes_activation_time)
    print(bs.asert_half_life)

def print_network_settings(ns):
    print(ns.threads)
    print(ns.protocol_maximum)
    print(ns.protocol_minimum)
    print(ns.services)
    print(ns.invalid_services)
    print(ns.relay_transactions)
    print(ns.validate_checksum)
    print(ns.identifier)
    print(ns.inbound_port)
    print(ns.inbound_connections)
    print(ns.outbound_connections)
    print(ns.manual_attempt_limit)
    print(ns.connect_batch_size)
    print(ns.connect_timeout_seconds)
    print(ns.channel_handshake_seconds)
    print(ns.channel_heartbeat_minutes)
    print(ns.channel_inactivity_minutes)
    print(ns.channel_expiration_minutes)
    print(ns.channel_germination_seconds)
    print(ns.host_pool_capacity)
    print(ns.hosts_file)

    print_authority(ns.self)

    print(ns.blacklist)

    for blacked in ns.blacklist:
        print_authority(blacked)

    for peer in ns.peers:
        print_endpoint(peer)

    for seed in ns.seeds:
        print_endpoint(seed)

    print(ns.debug_file)
    print(ns.error_file)
    print(ns.archive_directory)

    print(ns.rotation_size)
    print(ns.minimum_free_space)
    print(ns.maximum_archive_size)
    print(ns.maximum_archive_files)

    print_authority(ns.statistics_server)

    print(ns.verbose)
    print(ns.use_ipv6)

    print(ns.user_agent_blacklist)

stop_ = False
def signal_handler(signal, frame):
    print('You pressed Ctrl-C')
    global stop_
    stop_ = True

def handler(e):
    print(f'node run lambda: {e}')

def main():
    signal.signal(signal.SIGINT, signal_handler)
    signal.signal(signal.SIGTERM, signal_handler)

    setts = kth_native.config_settings_default(0)

    # print_node_settings(setts.node)
    # print_database_settings(setts.database)
    # print_blockchain_settings(setts.chain)
    # print_network_settings(setts.network)

    node = kth_native.node_construct(setts, True)
    # print(node)

    kth_native.node_init_run_and_wait_for_signal(node, 0, lambda e: handler(e) )

    # print("before sleep")
    global stop_
    while not stop_:
        # print("sleeping...")
        print(stop_)
        time.sleep(1)
    print("after sleep")

    kth_native.node_signal_stop(node);
    kth_native.node_destruct(node);



# ------------------------------------------------------------------------------------------------

# var toType = function(obj) {
#     return ({}).toString.call(obj).match(/\s([a-zA-Z]+)/)[1].toLowerCase()
# }

# ------------------------------------------------------------------------------------------------

# function timestampToDate(unix_timestamp) {
#     # Create a new JavaScript Date object based on the timestamp
#     # multiplied by 1000 so that the argument is in milliseconds, not seconds.
#     var date = new Date(unix_timestamp*1000);
#     # Hours part from the timestamp
#     var hours = date.getHours();
#     # Minutes part from the timestamp
#     var minutes = "0" + date.getMinutes();
#     # Seconds part from the timestamp
#     var seconds = "0" + date.getSeconds();

#     # Will display time in 10:30:23 format
#     var formattedTime = hours + ':' + minutes.substr(-2) + ':' + seconds.substr(-2);

#     return formattedTime
# }

# function byteToHexString(uint8arr) {
#     if (!uint8arr) {
#         return '';
#     }

#     var hexStr = '';
#     for (var i = 0; i < uint8arr.length; i++) {
#         var hex = (uint8arr[i] & 0xff).toString(16);
#         hex = (hex.length === 1) ? '0' + hex : hex;
#         hexStr += hex;
#     }

#     return hexStr.toUpperCase();
# }

# function hexStringToByte(str) {
#     if (!str) {
#         return new Uint8Array();
#     }

#     var a = [];
#     for (var i = 0, len = str.length; i < len; i+=2) {
#         a.push(parseInt(str.substr(i,2),16));
#     }

#     return new Uint8Array(a);
# }

# function reverse(s){
#     return s.split("").reverse().join("");
# }

# function toHash(s) {
#     return hexStringToByte(s).reverse();
# }

# function fromHash(arr) {
#     return byteToHexString(arr.reverse());
# }







# var hash_arr0 = toHash('0000000091a5fdf4b5f5fe07ed869bf82049b3d61a403f2771b5cbd1937dad09')
# var hash_arr1 = hexStringToByte('0000000091a5fdf4b5f5fe07ed869bf82049b3d61a403f2771b5cbd1937dad09')
# var hash_arr2 = new Uint8Array([21, 31, 21, 31, 21, 31, 21, 31, 21, 31, 21, 31, 21, 31, 21, 31, 21, 31, 21, 31, 21, 31, 21, 31, 21, 31, 21, 31, 21, 31, 21, 31])


# console.log(hash_arr0 instanceof Uint8Array)
# console.log(typeof hash_arr0)
# console.log(toType(hash_arr0))

# console.log(hash_arr1 instanceof Uint8Array)
# console.log(typeof hash_arr1)
# console.log(toType(hash_arr1))

# console.log(hash_arr2 instanceof Uint8Array)
# console.log(typeof hash_arr2)
# console.log(toType(hash_arr2))

# return


# ------------------------------------------------------------------------------------------------

# function sleep(ms) {
#     return new Promise(resolve => setTimeout(resolve, ms));
# }

# ------------------------------------------------------------------------------------------------


# function chain_fetch_last_height(chain) {
#     return new Promise((resolve, reject) => {
#         kth.chain_fetch_last_height(chain, function (e, h) {
#             resolve({error: e, height: h});
#             # if (e == 0) {
#             #     resolve(h);
#             # } else {
#             #     reject(e);
#             # }
#         })
#     });
# }

# function chain_fetch_block_header_by_hash(chain, hash) {
#     return new Promise((resolve, reject) => {
#         kth.chain_fetch_block_header_by_hash(chain, hash, function (e, header, height) {
#             resolve({error: e, header: header, height: height});
#             # if (e == 0) {
#             #     resolve([r, header, height]);
#             # } else {
#             #     resolve([header, height]);
#             #     # reject(e);
#             # }
#         })
#     });
# }

# async function wait_until_block(chain, desired_height) {

#     var res = await chain_fetch_last_height(chain);
#     console.log(`chain_fetch_last_height is OK, height: ${res.height}`)

#     while (res.height < desired_height) {
#         var res = await chain_fetch_last_height(chain);
#         console.log(`chain_fetch_last_height is OK, height: ${res.height}`)

#         if (res.height < desired_height) {
#             sleep(1000)
#         }
#     }
# }



# # async
# def main():

#     var node = kth.node_construct("/home/fernando/testnet4/testnet4.cfg", process.stdout, process.stderr);
#     # var node = kth.node_construct("/home/fernando/testnet4/testnet4.cfg", null, null);
#     # const node = kth.node_construct("", null, null)
#     # kth.node_initchain(node)
#     # kth.node_run_wait(node)

#     let justChain = 1;
#     kth.node_run(node, justChain, function (err) {
#         console.log(err);
#     });

#     var now = new Date().getTime();
#     console.log("-------------------------------------------", now);
#     await sleep(5000);
#     now = new Date().getTime();
#     console.log("-------------------------------------------", now);

#     # setTimeout(async function() {
#     #     console.log('program exit...');
#     #     kth.node_signal_stop(node);
#     #     # kth.node_destruct(node);
#     # }, 200000);

#     kth.node_signal_stop(node);
#     # kth.node_destruct(node);
# }


# async function main() {

#     # var node = kth.node_construct("/home/fernando/testnet4/testnet4.cfg", process.stdout, process.stderr);
#     var node = kth.node_construct("/home/fernando/testnet4/testnet4.cfg", null, null);
#     # const node = kth.node_construct("", null, null)
#     # kth.node_initchain(node)
#     # kth.node_run_wait(node)

#     kth.node_init_run_and_wait_for_signal(node, function (err) {
#         console.log(err);
#     });


#     const chain = kth.node_get_chain(node);

#     await wait_until_block(chain, 2300);


#     var hash_arr = toHash('0000000091a5fdf4b5f5fe07ed869bf82049b3d61a403f2771b5cbd1937dad09');

#     #-----------------------------------



#     # kth.chain_fetch_block_height(chain, [21,31], function (err, height) { #ERROR!
#     # kth.chain_fetch_block_height(chain, new Uint8Array([21, 31]), function (err, height) { #ERROR!
#     kth.chain_fetch_block_height(chain, hash_arr, function (err, height) {
#         if (err == 0) {
#             console.log(`chain_fetch_block_height is OK, err:  ${err}, height: ${height}`);
#         } else {
#             console.log(`chain_fetch_block_height failed, err: ${err}, height: ${height}`);
#         }
#     });


#     #-----------------------------------


#     # function arrayBufferToString(buffer){
#     #     var arr = new Uint8Array(buffer);
#     #     var str = String.fromCharCode.apply(String, arr);
#     #     if(/[\u0080-\uffff]/.test(str)){
#     #         throw new Error("this string seems to contain (still encoded) multibytes");
#     #     }
#     #     return str;
#     # }


#     kth.chain_fetch_block_header_by_height(chain, 2300, function (err, header, height) {
#         if (err == 0) {
#             console.log(`chain_fetch_block_header_by_height is OK, err:  ${err}, height: ${height}`);

#             # var version = kth.chain_header_version(header);
#             # console.log(`chain_fetch_block_header_by_height, version: ${version}`)

#             # var previous_block_hash = kth.chain_header_previous_block_hash(header);
#             # # console.log(`chain_fetch_block_header_by_height, previous_block_hash: ${previous_block_hash}`)
#             # var previous_block_hash_str = fromHash(previous_block_hash)
#             # console.log(`chain_fetch_block_header_by_height, previous_block_hash_str: ${previous_block_hash_str}`)

#             # var merkle = kth.chain_header_merkle(header);
#             # # console.log(`chain_fetch_block_header_by_height, merkle: ${merkle}`)
#             # var merkle_str = fromHash(merkle)
#             # console.log(`chain_fetch_block_header_by_height, merkle_str: ${merkle_str}`)

#             # var hash = kth.chain_header_hash(header);
#             # # console.log(`chain_fetch_block_header_by_height, hash: ${hash}`)
#             # var hash_str = fromHash(hash)
#             # console.log(`chain_fetch_block_header_by_height, hash_str: ${hash_str}`)

#             # var timestamp = kth.chain_header_timestamp(header);
#             # console.log(`chain_fetch_block_header_by_height, timestamp: ${timestamp}`)

#             # var timestamp_date = timestampToDate(timestamp)
#             # console.log(`chain_fetch_block_header_by_height, timestamp_date: ${timestamp_date}`)


#             # var bits = kth.chain_header_bits(header);
#             # console.log(`chain_fetch_block_header_by_height, bits: ${bits}`)

#             # var nonce = kth.chain_header_nonce(header);
#             # console.log(`chain_fetch_block_header_by_height, nonce: ${nonce}`)




#             kth.chain_header_destruct(header);
#         } else {
#             console.log(`chain_fetch_block_header_by_height failed, err: ${err}, height: ${height}`)
#         }
#     });

#     # Testnet4 Genesis block
#     res = await chain_fetch_block_header_by_hash(chain, toHash('000000001dd410c49a788668ce26751718cc797474d3152a5fc073dd44fd9f7b'));
#     console.log(res);

#     res = await chain_fetch_block_header_by_hash(chain, toHash('000000005845885b0f3e66a5a7377c408c7c42bad7528f44862f7b7e741bdb9e'));
#     console.log(res);

#     res = await chain_fetch_block_header_by_hash(chain, hash_arr);
#     console.log(res);

#     #-----------------------------------


#     # kth.chain_fetch_block_by_height(chain, 2300, function (err, block, height) {
#     #     if (err == 0) {
#     #         console.log(`chain_fetch_block_by_height is OK, err:  ${err}, height: ${height}`)
#     #     } else {
#     #         console.log(`chain_fetch_block_by_height failed, err: ${err}, height: ${height}`)
#     #     }
#     # })


#     kth.chain_fetch_block_by_height(chain, 2300, function (err, block, height) {
#         if (err == 0) {
#             console.log(`chain_fetch_block_by_height is OK, err:  ${err}, height: ${height}`)

#             var tx_count = kth.chain_block_transaction_count(block);
#             console.log(`chain_fetch_block_by_height, tx_count: ${tx_count}`)

#             var serialized_size = kth.chain_block_serialized_size(block, 0);
#             console.log(`chain_fetch_block_by_height, serialized_size: ${serialized_size}`)

#             var subsidy = kth.chain_block_subsidy(2300);
#             console.log(`chain_fetch_block_by_height, subsidy: ${subsidy}`)

#             var fees = kth.chain_block_fees(block);
#             console.log(`chain_fetch_block_by_height, fees: ${fees}`)

#             var claim = kth.chain_block_claim(block);
#             console.log(`chain_fetch_block_by_height, claim: ${claim}`)


#             var reward = kth.chain_block_reward(block, 2300);
#             console.log(`chain_fetch_block_by_height, reward: ${reward}`)


#             var merkle_root = fromHash(kth.chain_block_generate_merkle_root(block))
#             console.log(`chain_fetch_block_by_height, merkle_root: ${merkle_root}`)

#             var hash = fromHash(kth.chain_block_hash(block))
#             console.log(`chain_fetch_block_by_height, hash: ${hash}`)

#             var is_valid = kth.chain_block_is_valid(block);
#             console.log(`chain_fetch_block_by_height, is_valid: ${is_valid}`)

#             var tx_nth = kth.chain_block_transaction_nth(block, 0);
#             # console.log(`chain_fetch_block_by_height, tx_nth: ${tx_nth}`)

#             var sigops = kth.chain_block_signature_operations(block);
#             console.log(`chain_fetch_block_by_height, sigops: ${sigops}`)

#             var sigops2 = kth.chain_block_signature_operations_bip16_active(block, true);
#             console.log(`chain_fetch_block_by_height, sigops2: ${sigops2}`)

#             var total_inputs = kth.chain_block_total_inputs(block, true);
#             console.log(`chain_fetch_block_by_height, total_inputs: ${total_inputs}`)

#             var is_extra_coinbase = kth.chain_block_is_extra_coinbase(block);
#             console.log(`chain_fetch_block_by_height, is_extra_coinbase: ${is_extra_coinbase}`)

#             var is_final = kth.chain_block_is_final(block, 2300, 0);
#             console.log(`chain_fetch_block_by_height, is_final: ${is_final}`)

#             var is_distinct_transaction_set = kth.chain_block_is_distinct_transaction_set(block);
#             console.log(`chain_fetch_block_by_height, is_distinct_transaction_set: ${is_distinct_transaction_set}`)

#             var is_valid_coinbase_claim = kth.chain_block_is_valid_coinbase_claim(block, 2300);
#             console.log(`chain_fetch_block_by_height, is_valid_coinbase_claim: ${is_valid_coinbase_claim}`)

#             var is_valid_coinbase_script = kth.chain_block_is_valid_coinbase_script(block, 2300);
#             console.log(`chain_fetch_block_by_height, is_valid_coinbase_script: ${is_valid_coinbase_script}`)

#             var is_internal_double_spend = kth.chain_block_is_internal_double_spend(block);
#             console.log(`chain_fetch_block_by_height, is_internal_double_spend: ${is_internal_double_spend}`)

#             var is_valid_merkle_root = kth.chain_block_is_valid_merkle_root(block);
#             console.log(`chain_fetch_block_by_height, is_valid_merkle_root: ${is_valid_merkle_root}`)




#             var header = kth.chain_block_get_header(block);

#             var version = kth.chain_header_version(header);
#             console.log(`chain_fetch_block_by_height, version: ${version}`)

#             var previous_block_hash = kth.chain_header_previous_block_hash(header);
#             # console.log(`chain_fetch_block_by_height, previous_block_hash: ${previous_block_hash}`)
#             var previous_block_hash_str = fromHash(previous_block_hash)
#             console.log(`chain_fetch_block_by_height, previous_block_hash_str: ${previous_block_hash_str}`)

#             var merkle = kth.chain_header_merkle(header);
#             # console.log(`chain_fetch_block_by_height, merkle: ${merkle}`)
#             var merkle_str = fromHash(merkle)
#             console.log(`chain_fetch_block_by_height, merkle_str: ${merkle_str}`)

#             var hash = kth.chain_header_hash(header);
#             # console.log(`chain_fetch_block_by_height, hash: ${hash}`)
#             var hash_str = fromHash(hash)
#             console.log(`chain_fetch_block_by_height, hash_str: ${hash_str}`)

#             var timestamp = kth.chain_header_timestamp(header);
#             console.log(`chain_fetch_block_by_height, timestamp: ${timestamp}`)

#             var timestamp_date = timestampToDate(timestamp)
#             console.log(`chain_fetch_block_by_height, timestamp_date: ${timestamp_date}`)


#             var bits = kth.chain_header_bits(header);
#             console.log(`chain_fetch_block_by_height, bits: ${bits}`)

#             var nonce = kth.chain_header_nonce(header);
#             console.log(`chain_fetch_block_by_height, nonce: ${nonce}`)


#         } else {
#             console.log(`chain_fetch_block_by_height failed, err: ${err}, height: ${height}`)
#         }
#     })



#     kth.chain_fetch_block_by_hash(chain, hash_arr, function (err, block, height) {
#         if (err == 0) {
#             console.log(`chain_fetch_block_by_hash is OK, err:  ${err}, height: ${height}`)
#         } else {
#             console.log(`chain_fetch_block_by_hash failed, err: ${err}, height: ${height}`)
#         }
#     })

#     #-----------------------------------


#     kth.chain_fetch_merkle_block_by_height(chain, 2300, function (err, merkle_block, height) {
#         if (err == 0) {
#             console.log(`chain_fetch_merkle_block_by_height is OK, err:  ${err}, height: ${height}`)
#         } else {
#             console.log(`chain_fetch_merkle_block_by_height failed, err: ${err}, height: ${height}`)
#         }
#     })

#     kth.chain_fetch_merkle_block_by_hash(chain, hash_arr, function (err, merkle_block, height) {
#         if (err == 0) {
#             console.log(`chain_fetch_merkle_block_by_hash is OK, err:  ${err}, height: ${height}`)
#         } else {
#             console.log(`chain_fetch_merkle_block_by_hash failed, err: ${err}, height: ${height}`)
#         }
#     })


#     #-----------------------------------
#     # TODO(kth): implement compact blocks.
#     # kth.chain_fetch_compact_block_by_height(chain, 2300, function (err, compact_block, height) {
#     #     if (err == 0) {
#     #         console.log(`chain_fetch_compact_block_by_height is OK, err:  ${err}, height: ${height}`)
#     #     } else {
#     #         console.log(`chain_fetch_compact_block_by_height failed, err: ${err}, height: ${height}`)
#     #     }
#     # })

#     # kth.chain_fetch_compact_block_by_hash(chain, hash_arr, function (err, compact_block, height) {
#     #     if (err == 0) {
#     #         console.log(`chain_fetch_compact_block_by_hash is OK, err:  ${err}, height: ${height}`)
#     #     } else {
#     #         console.log(`chain_fetch_compact_block_by_hash failed, err: ${err}, height: ${height}`)
#     #     }
#     # })

#     #-----------------------------------
#     var tx_hash_arr = toHash('2c8e87226737f9a782e568bf744cf6757cd0f593184df80a61ab0e08c6d86733')

#     # kth.chain_fetch_transaction(chain, tx_hash_arr, false, function (err, tx, index, height) {
#     kth.chain_fetch_transaction(chain, tx_hash_arr, true, function (err, tx, index, height) {
#         if (err == 0) {
#             console.log(`chain_fetch_transaction is OK, err:  ${err}, index: ${index}, height: ${height}`)


#             var version = kth.chain_transaction_version(tx)
#             console.log(`chain_fetch_transaction, version: ${version}`)

#             # kth.chain_transaction_set_version(tx)
#             var hash = kth.chain_transaction_hash(tx)
#             console.log(`chain_fetch_transaction, hash: ${hash}`)

#             var hash_sighash_type = kth.chain_transaction_hash_sighash_type(tx, 0)
#             console.log(`chain_fetch_transaction, hash_sighash_type: ${hash_sighash_type}`)

#             var locktime = kth.chain_transaction_locktime(tx)
#             console.log(`chain_fetch_transaction, locktime: ${locktime}`)

#             var serialized_size = kth.chain_transaction_serialized_size(tx, true)
#             console.log(`chain_fetch_transaction, serialized_size: ${serialized_size}`)

#             var fees = kth.chain_transaction_fees(tx)
#             console.log(`chain_fetch_transaction, fees: ${fees}`)

#             var signature_operations = kth.chain_transaction_signature_operations(tx)
#             console.log(`chain_fetch_transaction, signature_operations: ${signature_operations}`)

#             var signature_operations_bip16_active = kth.chain_transaction_signature_operations_bip16_active(tx, true)
#             console.log(`chain_fetch_transaction, signature_operations_bip16_active: ${signature_operations_bip16_active}`)

#             var total_input_value = kth.chain_transaction_total_input_value(tx)
#             console.log(`chain_fetch_transaction, total_input_value: ${total_input_value}`)

#             var total_output_value = kth.chain_transaction_total_output_value(tx)
#             console.log(`chain_fetch_transaction, total_output_value: ${total_output_value}`)

#             var is_coinbase = kth.chain_transaction_is_coinbase(tx)
#             console.log(`chain_fetch_transaction, is_coinbase: ${is_coinbase}`)

#             var is_null_non_coinbase = kth.chain_transaction_is_null_non_coinbase(tx)
#             console.log(`chain_fetch_transaction, is_null_non_coinbase: ${is_null_non_coinbase}`)

#             var is_oversized_coinbase = kth.chain_transaction_is_oversized_coinbase(tx)
#             console.log(`chain_fetch_transaction, is_oversized_coinbase: ${is_oversized_coinbase}`)

#             var is_mature = kth.chain_transaction_is_mature(tx, 0)
#             console.log(`chain_fetch_transaction, is_mature: ${is_mature}`)

#             var is_overspent = kth.chain_transaction_is_overspent(tx)
#             console.log(`chain_fetch_transaction, is_overspent: ${is_overspent}`)

#             var is_double_spend = kth.chain_transaction_is_double_spend(tx, true)
#             console.log(`chain_fetch_transaction, is_double_spend: ${is_double_spend}`)

#             var is_missing_previous_outputs = kth.chain_transaction_is_missing_previous_outputs(tx)
#             console.log(`chain_fetch_transaction, is_missing_previous_outputs: ${is_missing_previous_outputs}`)

#             var is_final = kth.chain_transaction_is_final(tx)
#             console.log(`chain_fetch_transaction, is_final: ${is_final}`)

#             var is_locktime_conflict = kth.chain_transaction_is_locktime_conflict(tx)
#             console.log(`chain_fetch_transaction, is_locktime_conflict: ${is_locktime_conflict}`)

#             var outputs = kth.chain_transaction_outputs(tx)
#             # console.log(`chain_fetch_transaction, outputs: ${outputs}`)

#             var inputs = kth.chain_transaction_inputs(tx)
#             # console.log(`chain_fetch_transaction, inputs: ${inputs}`)


#             kth.chain_transaction_destruct(tx)


#         } else {
#             console.log(`chain_fetch_transaction failed, err: ${err}, index: ${index}, height: ${height}`)
#         }
#     })

#     # kth.chain_fetch_transaction_position(chain, tx_hash_arr, false, function (err, index, height) {
#     kth.chain_fetch_transaction_position(chain, tx_hash_arr, true, function (err, index, height) {
#         if (err == 0) {
#             console.log(`chain_fetch_transaction_position is OK, err:  ${err}, index: ${index}, height: ${height}`)
#         } else {
#             console.log(`chain_fetch_transaction_position failed, err: ${err}, index: ${index}, height: ${height}`)
#         }
#     })

#     #-----------------------------------

#     #-----------------------------------


#     console.log('... BEFORE EXIT ...')

#     kth.node_destruct(node)
# }


if __name__ == "__main__":
    main()