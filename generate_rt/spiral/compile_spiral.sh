#!/bin/bash
ROOT="../.."
gcc spiral_sphere.c ${ROOT}/srcs/vector_utils*.c ${ROOT}/srcs/utils*.c -I${ROOT}/srcs ${ROOT}/libft/*.c ${ROOT}/srcs/print_debug.c -lm
