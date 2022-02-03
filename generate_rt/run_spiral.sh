#!/bin/bash
ROOT="../.."
gcc spiral_sphere.c ${ROOT}/srcs/*utils*.c -I${ROOT}/srcs ${ROOT}/libft/*.c -lm
./a.out
