#!/bin/bash
set -eoxu pipefail

git clone https://github.com/katef/kgt --depth=1 --recursive
cd kgt
bmake -r -j$(nproc)
cd ..
cp ./kgt/build/bin/kgt ./_build/tool
rm -rf kgt