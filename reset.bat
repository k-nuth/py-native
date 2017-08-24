
@echo off

rd /s /q dist
rd /s /q build
rd /s /q bitprim_native.egg-info
rd /s /q bitprim_native.so


rd /s /q bitprim
rd /s /q conanbuildinfo.cmake
rd /s /q conaninfo.txt
rd /s /q conan_imports_manifest.txt

del bitprim_native.cp36-win_amd64.pyd

