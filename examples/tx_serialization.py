# Copyright (c) 2016-present Knuth Project developers.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

"""Example: deserialize a raw BCH tx and report input/output byte sizes."""

from __future__ import annotations

import kth_native as bn


def tx_inputs_outputs_size(tx_hex_str):
    tx_bytes = bytes(bytearray.fromhex(tx_hex_str))
    tx = bn.transaction_factory_from_data(tx_bytes)

    inputs = bn.transaction_inputs(tx)
    inputs_count = bn.input_list_count(inputs)
    # print(inputs_count)

    outputs = bn.transaction_outputs(tx)
    outputs_count = bn.output_list_count(outputs)
    # print(outputs_count)

        # {"input_list_push_back",  kth_py_native_input_list_push_back, METH_VARARGS, "..."},
        # {"input_list_count",  kth_py_native_input_list_count, METH_VARARGS, "..."},
        # {"input_list_nth",  kth_py_native_input_list_nth, METH_VARARGS, "..."},


    inputs_bytes_size = 0
    for i in range(inputs_count):
        input = bn.input_list_nth(inputs, i)
        input_data = bn.input_to_data(input, 1)
        inputs_bytes_size += len(input_data)

    outputs_bytes_size = 0
    for i in range(outputs_count):
        output = bn.output_list_nth(outputs, i)
        output_data = bn.output_to_data(output, 1)
        outputs_bytes_size += len(output_data)


    bn.transaction_destruct(tx)

    return (inputs_bytes_size, outputs_bytes_size)


if __name__ == "__main__":
    # Sample BCH tx 92a2daf3876d4567d09776db2e15534dea7404fa072ccda75952d2d8d9ce3cbf
    SAMPLE_TX_HEX = (
        "02000000020bd212940492b2423f32868ff30088c4bc80b715cb47b550f1fc4782"
        "2ec0d9bf010000006b483045022100af1ffb38b0c292f91b72bdc1520c1398c6a4"
        "5b4ff5e8f361458cae39ff14d273022000b977757a08ef6c418680db11de5df559"
        "4869a3760a9f0b46508548ad1719bb412103d7878213d5c96abcf7b4c03a61240c"
        "6567b5302c07b40c165a9b724dd34b2e81feffffff0db688bd0c2a64e4084b57ff"
        "216259545dbec30746479bd401bff558ad936712000000006b483045022100c702"
        "d0fcb63286ef877928dbd9d7cc0dc8e0a7b6e4225149ff27b1255247619502201"
        "40b42ce045e43567dc01174802404a87efd671da5d1b49fec1b242cf663fcd8412"
        "103ffd233a7b258ef93b321f7f89b7064f8a6fb8617408af7d0ef4db32758c4350"
        "9feffffff02707c7b01000000001976a914f745229eefae10932c19109033a2411"
        "caa41eb5d88ac744f2200000000001976a914457dde18f9d246533a7176f14bdf5"
        "b13faf79da888acd0f50700"
    )
    inputs, outputs = tx_inputs_outputs_size(SAMPLE_TX_HEX)
    print(f"inputs bytes:  {inputs}")
    print(f"outputs bytes: {outputs}")