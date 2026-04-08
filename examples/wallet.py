# Copyright (c) 2016-present Knuth Project developers.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

"""Wallet example: parse a payment address and reformat it.

Demonstrates the new triple split of the address encoding API:

    wallet_payment_address_encoded_legacy(addr)        # base58 P2PKH/P2SH
    wallet_payment_address_encoded_cashaddr(addr, t)   # cashaddr (BCH only)
    wallet_payment_address_encoded_token(addr)         # CashTokens prefix

The HD/EC derivation entry points (`wallet_hd_new`, `wallet_ec_new`,
`wallet_mnemonics_to_seed`, `word_list_*`) are still commented out in
`src/module.c` and not exported by the build, so this example sticks
to the parts of the wallet API that are actually live.
"""

from __future__ import annotations

import kth_native as bn

# A canonical mainnet BCH address (legacy form).
LEGACY_ADDR = "1BvBMSEYstWetqTFn5Au4m4GFg7xJaNVN2"


def main() -> None:
    addr = bn.wallet_payment_address_construct_from_string(LEGACY_ADDR)
    try:
        version = bn.wallet_payment_address_version(addr)
        legacy = bn.wallet_payment_address_encoded_legacy(addr)
        cashaddr = bn.wallet_payment_address_encoded_cashaddr(addr, False)
        token = bn.wallet_payment_address_encoded_token(addr)

        print(f"version:    {version}")
        print(f"legacy:     {legacy}")
        print(f"cashaddr:   {cashaddr}")
        print(f"token-aware:{token}")
    finally:
        bn.wallet_payment_address_destruct(addr)


if __name__ == "__main__":
    main()
