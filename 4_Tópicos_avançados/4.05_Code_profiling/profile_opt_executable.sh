#!/bin/bash

if [ ${1: -2} == ".c" ]
then
	echo "Não forneça o arquivo .c!!!"
	exit 1
fi

make $1 CFLAGS="-O3 -fno-inline"
echo
echo "--- TIME ---"
time ./$1
echo
echo "--- GPROF ---"
gprof ./$1 -p -b
rm gmon.out
rm ./$1
