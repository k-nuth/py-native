# Copyright (c) 2016-2022 Knuth Project developers.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

import kth_native
import os
import signal
import sys
import time

def main():
    # config = kth.settings.getDefault(kth.network.mainnet);
    config = kth_native.config_settings_default(0)     #mainnet
    print(config)

if __name__ == "__main__":
    main()


