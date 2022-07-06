#!/bin/bash

### 1a opção
EH_MES=1
for arg in $@
do
	if [ $EH_MES == 1 ]
	then
		MES=$arg
		EH_MES=0
	else
		cal $MES $arg
		EH_MES=1
	fi
done

### 2a opção
for arg in $(seq 1 2 $#)
do
	cal ${@:arg:2}
done