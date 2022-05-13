#!/bin/bash
set -eoxu pipefail
cd "$(dirname "$0")"

python3.10 py/gen.py

mkdir -p _build
cpp -undef -nostdinc src/wacc.wacc.in -o _build/wacc.wacc

if [[ ! -f ./_build/tp ]]
then
    ./regen-tp.sh
fi

./_build/tp ./_build/wacc.wacc ./_build/wacc.c
gcc ./_build/wacc.c -g -o ./_build/wacc
