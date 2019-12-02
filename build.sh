#!/bin/bash
set -euo pipefail

mkdir -p .build
pushd .build
cmake -D_CMAKE_TOOLCHAIN_PREFIX=llvm- -DCMAKE_BUILD_TYPE=Release ..
make -j4 unittest && ./unittest --use-colour yes && make -j4 all
popd
