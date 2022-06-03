#!/bin/bash
set -eoxu pipefail
git clone git@gitlab.doc.ic.ac.uk:lab2122_spring/wacc_examples.git
rm -rf example-valid
mv wacc_examples/valid example-valid
rm -rf wacc_examples
