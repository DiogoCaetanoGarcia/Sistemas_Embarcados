#!/bin/bash

if [ ${1: -2} == ".c" ]
then
	echo "Não forneça o arquivo .c!!!"
	exit 1
fi

make $1 CFLAGS="-O3 -fno-inline"
time ./$1
gprof ./$1 -p -b -c
rm gmon.out
rm ./$1