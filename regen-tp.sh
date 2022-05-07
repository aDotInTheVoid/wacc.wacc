#!/bin/bash

git clone https://github.com/RiscInside/WACC-to-C bootstrap
cd bootstrap
make
cd ..
cp bootstrap/transpiler-opt ./tp
rm -rf bootstrap
