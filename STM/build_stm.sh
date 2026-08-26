#!/bin/bash
# Compile the ZIPC generated-C STM into a shared library (run in WSL)
set -e
cd "$(dirname "$0")"
gcc -shared -fPIC -o libstm.so harness.c Main_m0.c actions.c Param_ram.c
echo "[OK] libstm.so built"
