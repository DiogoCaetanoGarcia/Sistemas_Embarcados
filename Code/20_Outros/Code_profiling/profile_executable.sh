#!/bin/bash

if [ ${1: -2} == ".c" ]
then
	echo "Não forneça o arquivo .c!!!"
	exit 1
fi

make $1
echo
echo "--- TIME ---"
echo "Saída do comando 'time'"
echo "real: Tempo usado pelo processo, em segundos."
echo "user: Número de segundos-CPU usados pelo processo em user space, em segundos."
echo "sys: Número de segundos-CPU usados pelo processo em kernel space, em segundos."
echo
time ./$1
echo
echo "--- GPROF ---"
gprof ./$1 -p -b
rm gmon.out
rm ./$1
