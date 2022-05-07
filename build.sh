#!/bin/bash
set -eoxu pipefail
cd "$(dirname "$0")"

python3.10 py/gen.py

cpp -undef -nostdinc wacc.wacc.in -o wacc.wacc

./tp ./wacc.wacc ./wacc.c