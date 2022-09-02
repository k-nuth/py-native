#!/bin/bash

/root/opt/bin/python3 --version

echo $PATH
export PATH="$HOME/.local/bin/:$PATH"
export PATH="$HOME/opt/bin/:$PATH"
echo $PATH

# python3 -m pip install --upgrade pip

pip3 install --upgrade setuptools --user
pip3 install --upgrade kthbuild --user
pip3 install --upgrade conan_package_tools --user
pip3 install --upgrade twine --user
pip3 install --upgrade wheel --user
# pip3 install auditwheel

conan --version
conan user

conan profile list
conan profile new default --detect
conan profile list

# conan remote add kth_temp https://knuth.jfrog.io/artifactory/api/conan/knuth
conan config install https://github.com/k-nuth/ci-utils/raw/master/conan/config.zip
conan profile list
conan profile update settings.compiler.libcxx=libstdc++11 default


cd /home/conan/project
# PROJECT_VERSION="$(/root/opt/bin/python3 -c 'from version import __version__; print(__version__)')"
# echo $PROJECT_VERSION

conan install .
pip3 install  -e .
python3 setup.py sdist
python3 setup.py bdist_wheel


auditwheel show dist/kth_py_native-*.whl
auditwheel repair dist/kth_py_native-*.whl
