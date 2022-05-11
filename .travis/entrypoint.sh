#!/bin/bash

echo "-----------------------------------------------------------------"
echo "-----------------------------------------------------------------"
echo "-----------------------------------------------------------------"
echo "-----------------------------------------------------------------"

python --version
python3 --version


echo "-----------------------------------------------------------------"
echo "-----------------------------------------------------------------"
echo "-----------------------------------------------------------------"
echo "-----------------------------------------------------------------"
echo "-----------------------------------------------------------------"

sudo pip install --upgrade kthbuild
sudo pip install --upgrade conan_package_tools
sudo pip install --upgrade wheel
sudo pip install --upgrade twine

conan user

conan remote add kth_temp https://knuth.jfrog.io/artifactory/api/conan/knuth

cd /home/conan/project
sudo conan install .
sudo pip install  -e .
sudo python setup.py sdist

# twine upload -u ${PYPI_USER_NAME} -p ${PYPI_PASSWORD} dist/*

# /bin/bash
