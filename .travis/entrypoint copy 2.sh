#!/bin/bash

pip3 uninstall -y kthbuild
pip3 uninstall -y conan
pip3 uninstall -y conan_package_tools
pip3 uninstall -y twine

# apt-get install -y make build-essential libssl-dev zlib1g-dev libbz2-dev libreadline-dev libsqlite3-dev wget curl llvm libncurses5-dev libncursesw5-dev xz-utils tk-dev libffi-dev liblzma-dev

#new
dnf -y install wget

# TODO: do this in the docker image
cd
wget https://github.com/openssl/openssl/archive/refs/heads/OpenSSL_1_1_1-stable.zip
unzip OpenSSL_1_1_1-stable.zip
cd openssl-OpenSSL_1_1_1-stable/
./config --prefix=$HOME/opt/ssl --openssldir=$HOME/opt/ssl && make && make install


cd
wget https://www.python.org/ftp/python/$PYTHON_VERSION/Python-$PYTHON_VERSION.tgz
tar -xf Python-$PYTHON_VERSION.tgz
cd Python-$PYTHON_VERSION

if [[ "${CP_PYTHON_VERSION}" == "cp310" ]]; then
    ./configure --prefix=$HOME/opt --with-openssl=$HOME/opt/ssl --with-openssl-rpath=auto
else
    export LD_LIBRARY_PATH=$HOME/opt/ssl/lib
    ./configure --prefix=$HOME/opt --with-openssl=$HOME/opt/ssl
fi
make && make install


/root/opt/bin/python3 --version

echo $PATH
export PATH="$HOME/.local/bin/:$PATH"
echo $PATH

/root/opt/bin/python3 -m pip install --upgrade pip
/root/opt/bin/pip3 install --upgrade kthbuild --user
/root/opt/bin/pip3 install --upgrade conan_package_tools --user
/root/opt/bin/pip3 install --upgrade twine --user
/root/opt/bin/pip3 install --upgrade wheel --user
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
/root/opt/bin/pip3 install  -e .
/root/opt/bin/python3 setup.py sdist
/root/opt/bin/python3 setup.py bdist_wheel


auditwheel show dist/kth_py_native-*.whl
auditwheel repair dist/kth_py_native-*.whl
