#!/bin/bash
set -euo pipefail

export PATH=/opt/gcc-9.1.0/bin:${PATH}
export LD_LIBRARY_PATH=/opt/gcc-9.1.0/lib:${LD_LIBRARY_PATH:-}
export CC=gcc-9.1
export CXX=g++-9.1
mkdir -p .build
pushd .build
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j4 unittest && ./unittest --use-colour yes && make -j4 all
popd
