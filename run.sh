#!/bin/bash
set -euo pipefail

./build.sh

cat $1.txt | .build/$1_$2
