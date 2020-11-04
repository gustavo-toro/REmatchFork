#!/bin/bash

python setup.py bdist_wheel
pip uninstall -y rematchpy
pip install dist/*.whl

python tests/swig/simple-test.py