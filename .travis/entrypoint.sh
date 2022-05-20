#!/bin/bash

echo "-----------------------------------------------------------------"
echo "-----------------------------------------------------------------"
echo "-----------------------------------------------------------------"
echo "-----------------------------------------------------------------"

python --version
python3 --version
pyenv --version
# pyenv install --list

echo "-----------------------------------------------------------------"
echo "-----------------------------------------------------------------"
echo "-----------------------------------------------------------------"
echo "-----------------------------------------------------------------"
echo "-----------------------------------------------------------------"

# sudo pip install --upgrade kthbuild
# sudo pip install --upgrade conan_package_tools
# sudo pip install --upgrade wheel
# sudo pip install --upgrade twine

pip install --upgrade kthbuild --user
pip install --upgrade conan_package_tools --user
pip install --upgrade wheel --user
pip install --upgrade twine --user

echo "-----------------------------------------------------------------"
echo "-----------------------------------------------------------------"
echo "-----------------------------------------------------------------"
echo "-----------------------------------------------------------------"
echo "-----------------------------------------------------------------"

conan --version
conan user

# echo "-----------------------------------------------------------------"
# echo "-----------------------------------------------------------------"
# echo "-----------------------------------------------------------------"
# echo "-----------------------------------------------------------------"
# echo "-----------------------------------------------------------------"

# cd
# cd .conan/profiles
# ls

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
pip install  -e .
python setup.py sdist
python setup.py bdist_wheel

# twine upload -u ${PYPI_USER_NAME} -p ${PYPI_PASSWORD} dist/*

# /bin/bash
