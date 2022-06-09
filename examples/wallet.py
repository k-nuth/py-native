# Copyright (c) 2016-2022 Knuth Project developers.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

import os
import signal
import sys
import time
import bitprim_native as bn





wl = bn.word_list_construct()

# ------------------------------------------------------------------------------------------------------
# Copay Fernando
# genre salon chuckle oval finish loan crystal delay mixed erupt clown horn
# c8e30a6df5fb13257d5044e0c2a9546681f20c7318c676e5cb616c98df20f4d83f119fd03ef2061511008e022c8c28450ff1fa2d3a83df04818313a7b9996023
# 15LdCdQoXio4tYAtPd8v2cvdrzrtoHYyaW

bn.word_list_add_word(wl, "genre")
bn.word_list_add_word(wl, "salon")
bn.word_list_add_word(wl, "chuckle")
bn.word_list_add_word(wl, "oval")
bn.word_list_add_word(wl, "finish")
bn.word_list_add_word(wl, "loan")
bn.word_list_add_word(wl, "crystal")
bn.word_list_add_word(wl, "delay")
bn.word_list_add_word(wl, "mixed")
bn.word_list_add_word(wl, "erupt")
bn.word_list_add_word(wl, "clown")
bn.word_list_add_word(wl, "horn")


# ------------------------------------------------------------------------------------------------------
# car slab tail dirt wife custom front shield diet pear skull vapor gorilla token yard
# https://iancoleman.io/bip39/
# e0b6ebf43ebcaa428f59a1f9241019ba4c083a1c05d988677c8bf28ec6505ae07286515a9bb0bf98d836f582a94f29fc92bbe9a0a5805ce6dc4756a439ebd1d9

# bn.word_list_add_word(wl, "car")
# bn.word_list_add_word(wl, "slab")
# bn.word_list_add_word(wl, "tail")
# bn.word_list_add_word(wl, "dirt")
# bn.word_list_add_word(wl, "wife")
# bn.word_list_add_word(wl, "custom")
# bn.word_list_add_word(wl, "front")
# bn.word_list_add_word(wl, "shield")
# bn.word_list_add_word(wl, "diet")
# bn.word_list_add_word(wl, "pear")
# bn.word_list_add_word(wl, "skull")
# bn.word_list_add_word(wl, "vapor")
# bn.word_list_add_word(wl, "gorilla")
# bn.word_list_add_word(wl, "token")
# bn.word_list_add_word(wl, "yard")
# ------------------------------------------------------------------------------------------------------


seed = bn.wallet_mnemonics_to_seed(wl)
print(seed.encode('hex'))


# ec_priv = bn.wallet_ec_new(seed)
# print(ec_priv.encode('hex'))


hd_priv = bn.wallet_hd_new(seed, 76066276)
ec_priv = bn.wallet_hd_private_to_ec(hd_priv)

print(ec_priv.encode('hex'))

pubk = bn.wallet_ec_to_public(ec_priv, 1)
addr = bn.wallet_ec_to_address(pubk, 0)
addr_str = bn.payment_address_encoded(addr)

# # seed_hex = seed[::-1].encode('hex')
# seed_hex = seed.encode('hex')

# print(seed_hex)

print(addr_str)
# 15LdCdQoXio4tYAtPd8v2cvdrzrtoHYyaW
# 18BVJyoFgv2D1uSrJxbubZarEKRPwKfc8D


bn.word_list_destruct(wl)
