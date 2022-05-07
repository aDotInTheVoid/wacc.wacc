#!/bin/bash
set -eoxu pipefail
cd "$(dirname "$0")"

python3.10 py/gen_struct.py

cpp -undef -nostdinc wacc.wacc.in -o wacc.wacc