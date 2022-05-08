#!/bin/bash
set -eoxu pipefail

git clone https://github.com/RiscInside/WACC-to-C bootstrap
cd bootstrap
make
cd ..
cp bootstrap/transpiler-opt ./_build/tp
rm -rf bootstrap
