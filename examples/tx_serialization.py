 # 
 # Copyright (c) 2017 Bitprim developers (see AUTHORS)
 # 
 # This file is part of Bitprim.
 # 
 # This program is free software: you can redistribute it and/or modify
 # it under the terms of the GNU Affero General Public License as published by
 # the Free Software Foundation, either version 3 of the License, or
 # (at your option) any later version.
 # 
 # This program is distributed in the hope that it will be useful,
 # but WITHOUT ANY WARRANTY; without even the implied warranty of
 # MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 # GNU Affero General Public License for more details.
 # 
 # You should have received a copy of the GNU Affero General Public License
 # along with this program.  If not, see <http://www.gnu.org/licenses/>.
 # 

# pip install --upgrade --index-url https://test.pypi.org/pypi/ --install-option="--currency=BCH" bitprim-native
# pip install --upgrade --index-url https://test.pypi.org/pypi/ bitprim-native

import os
import signal
import sys
import time
import bitprim_native as bn


def tx_inputs_outputs_size(tx_hex_str):
    tx_bytes = bytearray.fromhex(tx_hex_str)
    tx_buffer = buffer(tx_bytes)
    tx = bn.transaction_factory_from_data(0, tx_buffer)

    inputs = bn.transaction_inputs(tx)
    inputs_count = bn.input_list_count(inputs)
    # print(inputs_count)

    outputs = bn.transaction_outputs(tx)
    outputs_count = bn.output_list_count(outputs)
    # print(outputs_count)

        # {"input_list_push_back",  bitprim_native_input_list_push_back, METH_VARARGS, "..."},
        # {"input_list_count",  bitprim_native_input_list_count, METH_VARARGS, "..."},
        # {"input_list_nth",  bitprim_native_input_list_nth, METH_VARARGS, "..."},


    inputs_bytes_size = 0
    for i in range(inputs_count):
        # print(i)
        input = bn.input_list_nth(inputs, i)
        input_data = bn.input_to_data(input, 1)
        input_data_hex = input_data.encode('hex')
        # print(input)
        # print(input_data)
        # print(input_data_hex)

        # 0bd212940492b2423f32868ff30088c4bc80b715cb47b550f1fc47822ec0d9bf010000006b483045022100af1ffb38b0c292f91b72bdc1520c1398c6a45b4ff5e8f361458cae39ff14d273022000b977757a08ef6c418680db11de5df5594869a3760a9f0b46508548ad1719bb412103d7878213d5c96abcf7b4c03a61240c6567b5302c07b40c165a9b724dd34b2e81feffffff
        # 0db688bd0c2a64e4084b57ff216259545dbec30746479bd401bff558ad936712000000006b483045022100c702d0fcb63286ef877928dbd9d7cc0dc8e0a7b6e4225149ff27b125524761950220140b42ce045e43567dc01174802404a87efd671da5d1b49fec1b242cf663fcd8412103ffd233a7b258ef93b321f7f89b7064f8a6fb8617408af7d0ef4db32758c43509feffffff
        # print(len(input_data))

        inputs_bytes_size = inputs_bytes_size + len(input_data)


    outputs_bytes_size = 0
    for i in range(outputs_count):
        # print(i)
        output = bn.output_list_nth(outputs, i)
        output_data = bn.output_to_data(output, 1)
        output_data_hex = output_data.encode('hex')
        # print(output)
        # print(output_data)
        # print(output_data_hex)

        # 707c7b01000000001976a914f745229eefae10932c19109033a2411caa41eb5d88ac
        # 744f2200000000001976a914457dde18f9d246533a7176f14bdf5b13faf79da888ac
        # print(len(output_data))

        outputs_bytes_size = outputs_bytes_size + len(output_data)


    bn.transaction_destruct(tx)    

    return (inputs_bytes_size, outputs_bytes_size)


# ------------------------------------------------------------------------------------------------------------------------------------------------------------------
# Usage
# ------------------------------------------------------------------------------------------------------------------------------------------------------------------

# https://blockdozer.com/insight-api/tx/92a2daf3876d4567d09776db2e15534dea7404fa072ccda75952d2d8d9ce3cbf
# https://blockdozer.com/insight-api/rawtx/92a2daf3876d4567d09776db2e15534dea7404fa072ccda75952d2d8d9ce3cbf

# {"rawtx":"02000000020bd212940492b2423f32868ff30088c4bc80b715cb47b550f1fc47822ec0d9bf010000006b483045022100af1ffb38b0c292f91b72bdc1520c1398c6a45b4ff5e8f361458cae39ff14d273022000b977757a08ef6c418680db11de5df5594869a3760a9f0b46508548ad1719bb412103d7878213d5c96abcf7b4c03a61240c6567b5302c07b40c165a9b724dd34b2e81feffffff0db688bd0c2a64e4084b57ff216259545dbec30746479bd401bff558ad936712000000006b483045022100c702d0fcb63286ef877928dbd9d7cc0dc8e0a7b6e4225149ff27b125524761950220140b42ce045e43567dc01174802404a87efd671da5d1b49fec1b242cf663fcd8412103ffd233a7b258ef93b321f7f89b7064f8a6fb8617408af7d0ef4db32758c43509feffffff02707c7b01000000001976a914f745229eefae10932c19109033a2411caa41eb5d88ac744f2200000000001976a914457dde18f9d246533a7176f14bdf5b13faf79da888acd0f50700"}

tx_hex_str = "02000000020bd212940492b2423f32868ff30088c4bc80b715cb47b550f1fc47822ec0d9bf010000006b483045022100af1ffb38b0c292f91b72bdc1520c1398c6a45b4ff5e8f361458cae39ff14d273022000b977757a08ef6c418680db11de5df5594869a3760a9f0b46508548ad1719bb412103d7878213d5c96abcf7b4c03a61240c6567b5302c07b40c165a9b724dd34b2e81feffffff0db688bd0c2a64e4084b57ff216259545dbec30746479bd401bff558ad936712000000006b483045022100c702d0fcb63286ef877928dbd9d7cc0dc8e0a7b6e4225149ff27b125524761950220140b42ce045e43567dc01174802404a87efd671da5d1b49fec1b242cf663fcd8412103ffd233a7b258ef93b321f7f89b7064f8a6fb8617408af7d0ef4db32758c43509feffffff02707c7b01000000001976a914f745229eefae10932c19109033a2411caa41eb5d88ac744f2200000000001976a914457dde18f9d246533a7176f14bdf5b13faf79da888acd0f50700"
res = tx_inputs_outputs_size(tx_hex_str)
print(res)