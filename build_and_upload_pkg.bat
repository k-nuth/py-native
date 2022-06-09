@echo off

REM Requirements --------------------------------------
REM pip install wheel
REM pip install twine
REM ---------------------------------------------------

REM pip install --global-option=build_ext --global-option="-IC:/dev/kth/kth-c-api/include" --global-option="-LC:/dev/kth/build/kth-c-apt/" -e .
pip install -e .
python setup.py bdist_wheel
twine upload dist/*
