#!/bin/bash
set -eoxu pipefail

mkdir -p _build/html

if [[ ! -f ./_build/tool/kgt ]]
then
    ./regen-kgt.sh
fi

./_build/tool/kgt -e html5     -l iso-ebnf < gram/parse.ebnf > _build/html/parse-rr.html
./_build/tool/kgt -e ebnfhtml5 -l iso-ebnf < gram/parse.ebnf > _build/html/parse-ebnf.html
./_build/tool/kgt -e html5     -l iso-ebnf < gram/lex.ebnf  > _build/html/lex-rr.html
./_build/tool/kgt -e ebnfhtml5 -l iso-ebnf < gram/lex.ebnf   > _build/html/lex-ebnf.html
