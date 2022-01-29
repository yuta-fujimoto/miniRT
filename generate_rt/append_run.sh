#!/bin/bash
ROOT=".."
OUT="tmp.rt"
if [ $# != 2 ]; then
	echo "引数エラー"
	exit 1
else
	EXECUTE=$1
	BASE=$2
	cp $2 ${OUT}
fi
./${EXECUTE} >> ${OUT}
${ROOT}/miniRT ${OUT}
rm ${OUT}
