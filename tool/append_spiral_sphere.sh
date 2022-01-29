#!/bin/bash
ROOT=".."
OUTFILE="tmp.rt"
if [ $# != 1 ]; then
	echo "引数なしエラー"
	exit 1
else
	cp $1 ${OUTFILE}
fi
gcc spiral_sphere.c ${ROOT}/srcs/vector_utils*.c ${ROOT}/srcs/utils*.c -I${ROOT}/srcs ${ROOT}/libft/*.c ${ROOT}/srcs/print_debug.c -lm
./a.out >> ${OUTFILE}
${ROOT}/miniRT ${OUTFILE}
rm a.out ${OUTFILE}
