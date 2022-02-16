#!/bin/bash

EH_MES=1
for ARG in $@
do
	# echo ARG = ${ARG}, EH_MES = ${EH_MES}
	if [ $EH_MES -eq 1 ]
	then
		MES=${ARG}
		EH_MES=0
	else
		cal ${MES} ${ARG}
		EH_MES=1
	fi
done