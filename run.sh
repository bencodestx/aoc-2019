#!/bin/bash
set -euo pipefail

cat $1.txt | build/$1_$2
