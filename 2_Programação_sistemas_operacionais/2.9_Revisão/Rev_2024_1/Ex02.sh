#!/bin/bash

par_ou_impar=0
for arg in $@
do
	if [ $par_ou_impar -eq 0 ]
	then
		mes=$arg
		par_ou_impar=1
	else
		cal $mes $arg
		par_ou_impar=0
	fi
done