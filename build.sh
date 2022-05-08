#!/bin/bash
set -eoxu pipefail
cd "$(dirname "$0")"

python3.10 py/gen.py

cpp -undef -nostdinc wacc.wacc.in -o wacc.wacc

if [[ ! -f ./tp ]]
then
    ./regen-tp.sh
fi

./tp ./wacc.wacc ./wacc.c
gcc wacc.c -g -o wacc