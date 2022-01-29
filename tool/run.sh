#!/bin/bash
ROOT=".."
gcc generate_rt.c ${ROOT}/srcs/vector_utils*.c ${ROOT}/srcs/utils*.c -I${ROOT}/srcs ${ROOT}/libft/*.c ${ROOT}/srcs/print_debug.c -lm
./a.out >> $1
rm a.out
${ROOT}/miniRT $1
