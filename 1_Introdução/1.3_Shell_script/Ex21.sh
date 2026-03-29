#!/bin/bash

# Referência: https://www.vivaolinux.com.br/dica/Utilizando-arrays-em-shell-script

vals=( "ABC" "DEF" "GHI" "JKL" )

echo ${vals[0]}
echo ${vals[1]}
echo ${vals[2]}
echo ${vals[3]}

echo ----------------

echo O vetor vals tem ${#vals[@]} elementos
for i in ${vals[@]}
do
	echo i = $i
done
