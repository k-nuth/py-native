rm -rf kth
mkdir kth
cd kth

cp -R /Users/fernando/.conan/data/c-api/0.25.0/kth/staging/package/0505ec8a1cdbf5817fd85795a1d3a35559132d45/* .

cp -R /Users/fernando/.conan/data/node/0.24.0/kth/staging/package/b887919b1649986289da3ea0c142b1d70e412c02/lib/* lib/.
cp -R /Users/fernando/.conan/data/secp256k1/0.9.0/kth/staging/package/58873fd7c926413a5ca08676fe10ea1540f75463/lib/* lib/.
cp -R /Users/fernando/.conan/data/blockchain/0.19.0/kth/staging/package/159f417adc9ca3aa82d4cce47e6ea03b6218c59c/lib/* lib/.
cp -R /Users/fernando/.conan/data/network/0.22.0/kth/staging/package/d0ad659e46aa1b6d80b227b153b2b0b5402d9d4c/lib/* lib/.
cp -R /Users/fernando/.conan/data/consensus/0.16.0/kth/staging/package/9394a5f0835090caea9a6c11e72f6dc2b5d51847/lib/* lib/.
cp -R /Users/fernando/.conan/data/database/0.19.0/kth/staging/package/1bad93d7483e19c67549849e92be4067e7d5c47e/lib/* lib/.
cp -R /Users/fernando/.conan/data/domain/0.21.0/kth/staging/package/9a07e722225844a8da6f7a3ceb1b27e495dcae78/lib/* lib/.
cp -R /Users/fernando/.conan/data/infrastructure/0.18.0/kth/staging/package/7dad4c5e20ba0b3426042fc0722526e17778fdcb/lib/* lib/.
cp -R /Users/fernando/.conan/data/boost/1.78.0/_/_/package/504548c61f240a2dc13f252499115b36e75c5b49/lib/* lib/.
cp -R /Users/fernando/.conan/data/gmp/6.2.1/_/_/package/df6a0d5cf591703ff65dc0f9b8e62a6f9e6eb9de/lib/* lib/.
cp -R /Users/fernando/.conan/data/lmdb/0.9.24/kth/stable/package/44091a5b30c40829c7188499afa38ea5e6413695/lib/* lib/.


    # clang-13: error: no such file or directory: 'kth/lib/libboost_atomic.a'
    # clang-13: error: no such file or directory: 'kth/lib/libboost_chrono.a'
    # clang-13: error: no such file or directory: 'kth/lib/libboost_date_time.a'
    # clang-13: error: no such file or directory: 'kth/lib/libboost_filesystem.a'
    # clang-13: error: no such file or directory: 'kth/lib/libboost_iostreams.a'
    # clang-13: error: no such file or directory: 'kth/lib/libboost_locale.a'
    # clang-13: error: no such file or directory: 'kth/lib/libboost_log.a'
    # clang-13: error: no such file or directory: 'kth/lib/libboost_log_setup.a'
    # clang-13: error: no such file or directory: 'kth/lib/libboost_program_options.a'
    # clang-13: error: no such file or directory: 'kth/lib/libboost_random.a'
    # clang-13: error: no such file or directory: 'kth/lib/libboost_regex.a'
    # clang-13: error: no such file or directory: 'kth/lib/libboost_system.a'
    # clang-13: error: no such file or directory: 'kth/lib/libboost_unit_test_framework.a'
    # clang-13: error: no such file or directory: 'kth/lib/libboost_prg_exec_monitor.a'
    # clang-13: error: no such file or directory: 'kth/lib/libboost_test_exec_monitor.a'
    # clang-13: error: no such file or directory: 'kth/lib/libboost_thread.a'
    # clang-13: error: no such file or directory: 'kth/lib/libboost_timer.a'

    # clang-13: error: no such file or directory: 'kth/lib/libgmp.a'

    # clang-13: error: no such file or directory: 'kth/lib/liblmdb.a'