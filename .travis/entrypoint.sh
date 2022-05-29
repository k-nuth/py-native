#!/bin/bash

pip3 uninstall -y kthbuild
pip3 uninstall -y conan
pip3 uninstall -y conan_package_tools
pip3 uninstall -y twine

echo "-----------------------------------------------------------------"
echo "-----------------------------------------------------------------"
echo "-----------------------------------------------------------------"
echo "-----------------------------------------------------------------"
echo "-----------------------------------------------------------------"

apt-get install -y make build-essential libssl-dev zlib1g-dev libbz2-dev libreadline-dev libsqlite3-dev wget curl llvm libncurses5-dev libncursesw5-dev xz-utils tk-dev libffi-dev liblzma-dev

echo "-----------------------------------------------------------------"
echo "-----------------------------------------------------------------"
echo "-----------------------------------------------------------------"
echo "-----------------------------------------------------------------"
echo "-----------------------------------------------------------------"

cd
wget https://github.com/openssl/openssl/archive/refs/heads/OpenSSL_1_1_1-stable.zip
unzip OpenSSL_1_1_1-stable.zip
cd openssl-OpenSSL_1_1_1-stable/
./config --prefix=$HOME/opt/ssl --openssldir=$HOME/opt/ssl && make && make install

echo "-----------------------------------------------------------------"
echo "-----------------------------------------------------------------"
echo "-----------------------------------------------------------------"
echo "-----------------------------------------------------------------"
echo "-----------------------------------------------------------------"

wget https://www.python.org/ftp/python/3.10.4/Python-3.10.4.tgz
tar -xf Python-3.10.4.tgz
cd Python-3.10.4
./configure --prefix=$HOME/opt --with-openssl=$HOME/opt/ssl --with-openssl-rpath=auto && make && make install


echo "-----------------------------------------------------------------"
echo "-----------------------------------------------------------------"
echo "-----------------------------------------------------------------"
echo "-----------------------------------------------------------------"
echo "-----------------------------------------------------------------"

/root/opt/bin/python3 --version

echo "-----------------------------------------------------------------"
echo "-----------------------------------------------------------------"
echo "-----------------------------------------------------------------"
echo "-----------------------------------------------------------------"
echo "-----------------------------------------------------------------"


echo $PATH
export PATH="$HOME/.local/bin/:$PATH"
echo $PATH

echo "-----------------------------------------------------------------"
echo "-----------------------------------------------------------------"
echo "-----------------------------------------------------------------"
echo "-----------------------------------------------------------------"
echo "-----------------------------------------------------------------"

/root/opt/bin/python3.10 -m pip install --upgrade pip

echo "-----------------------------------------------------------------"
echo "-----------------------------------------------------------------"
echo "-----------------------------------------------------------------"
echo "-----------------------------------------------------------------"
echo "-----------------------------------------------------------------"


/root/opt/bin/pip3 install --upgrade kthbuild --user
/root/opt/bin/pip3 install --upgrade conan_package_tools --user
/root/opt/bin/pip3 install --upgrade twine --user
/root/opt/bin/pip3 install --upgrade wheel --user
# pip3 install auditwheel


echo "-----------------------------------------------------------------"
echo "-----------------------------------------------------------------"
echo "-----------------------------------------------------------------"
echo "-----------------------------------------------------------------"
echo "-----------------------------------------------------------------"

conan --version
conan user

echo "-----------------------------------------------------------------"
echo "-----------------------------------------------------------------"
echo "-----------------------------------------------------------------"
echo "-----------------------------------------------------------------"
echo "-----------------------------------------------------------------"

conan profile list
conan profile new default --detect
conan profile list

# conan remote add kth_temp https://knuth.jfrog.io/artifactory/api/conan/knuth
conan config install https://github.com/k-nuth/ci-utils/raw/master/conan/config.zip

conan profile list

conan profile update settings.compiler.libcxx=libstdc++11 default

echo "-----------------------------------------------------------------"
echo "-----------------------------------------------------------------"
echo "-----------------------------------------------------------------"
echo "-----------------------------------------------------------------"
echo "-----------------------------------------------------------------"

cd /home/conan/project

# sudo conan install .
# sudo pip install  -e .
# sudo python setup.py sdist
conan install .
/root/opt/bin/pip3 install  -e .
/root/opt/bin/python3 setup.py sdist
/root/opt/bin/python3 setup.py bdist_wheel


echo "*************************************************"
ls
echo "*************************************************"
auditwheel show dist/kth_py_native-0.1.0-cp310-cp310-linux_x86_64.whl
echo "*************************************************"
auditwheel repair dist/kth_py_native-0.1.0-cp310-cp310-linux_x86_64.whl
# rm dist/kth_py_native-0.1.0-cp310-cp310-linux_x86_64.whl
# echo "*************************************************"
# ls
# echo "*************************************************"

# echo "*************************************************"
# ls wheelhouse
# echo "*************************************************"
# auditwheel show dist/kth_py_native-0.1.0-cp310-cp310-linux_x86_64.whl
# auditwheel show wheelhouse/kth_py_native-0.1.0-cp35-cp35m-manylinux_2_24_x86_64.whl
# echo "*************************************************"



# twine upload -u ${PYPI_USER_NAME} -p ${PYPI_PASSWORD} dist/*
# /bin/bash
