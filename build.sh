#!/bin/bash

CFLAGS="-Wall -Wextra -pedantic -std=c11 -pedantic -pthread"
OUTDIR="dist/main"
files_to_compile=$(find . -name "*.c" -not -name "main.c")

gcc src/main.c ${files_to_compile} ${CFLAGS} -o ${OUTDIR}
