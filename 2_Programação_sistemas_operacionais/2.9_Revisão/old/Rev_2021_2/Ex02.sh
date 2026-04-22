#!/bin/bash

EH_MES=1
for args in $@
do
	if [ $EH_MES -eq 1 ]
	then
		NUM_MES=$args
		EH_MES=0
	else
		NUM_ANO=$args
		cal $NUM_MES $NUM_ANO
		EH_MES=1
	fi
done