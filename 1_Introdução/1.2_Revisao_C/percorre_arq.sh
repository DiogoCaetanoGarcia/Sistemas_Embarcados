#!/bin/bash

if [ $# -lt 1 ]
then
	echo Indique código-fonte a ser detalhado. Por exemplo:
	echo "   "\$ $0 $(ls *.c | head -1)
	exit
fi

function aviso()
{
	N_AVISO=${#1}
	N_AVISO=$((N_AVISO + 8))
	LINHA_AVISO=""
	for n in $(seq $N_AVISO)
	do
		LINHA_AVISO=${LINHA_AVISO}'='
	done
	echo ${LINHA_AVISO}
	echo "===" $1 "==="
	echo ${LINHA_AVISO}
	echo
}

function read_key()
{
	read -rsn1 ui
	case "$ui" in
		$'\x1b')    # Handle ESC sequence.
			# Flush read. We account for sequences for Fx keys as
			# well. 6 should suffice far more then enough.
			read -rsn1 -t 0.1 tmp
			if [[ "$tmp" == "[" ]]
			then
				read -rsn1 -t 0.1 tmp
				case "$tmp" in
					"A") printf "B";; #"Up";;
					"B") printf "F";; #"Down";;
					"C") printf "F";; #"Right";;
					"D") printf "B";; #"Left";;
				esac
			fi
			# Flush "stdin" with 0.1  sec timeout.
			read -rsn5 -t 0.1
			;;
			# Other one byte (char) cases. Here only quit.
		q)
			printf "F";
			break;;
	esac
}

# Black        0;30
# Red          0;31
# Green        0;32     
# Brown/Orange 0;33     
# Blue         0;34     
# Purple       0;35     
# Cyan         0;36     
# Light Gray   0;37     
# Dark Gray     1;30
# Light Red     1;31
# Light Green   1;32
# Yellow        1;33
# Light Blue    1;34
# Light Purple  1;35
# Light Cyan    1;36
# White         1;37

BLU='\033[0;34m'
RED='\033[0;31m'
YEL='\033[0;33m'
NC='\033[0m'

DELIM="SOE"
N=$(wc -l < $1)

LINHAS=($(grep ${DELIM} -n $1 | grep -oP "^.*?(?=\:)"))
XTRA=($(grep -oP "(?<=${DELIM}\().*?(?=\))" $1))
SED_SEARCH="s/${DELIM}\([0-9]*\)//"

i=1
while [ $i -le ${#LINHAS[@]} ]
do
	l=${LINHAS[$((i-1))]}
	k=${XTRA[$((i-1))]}
	clear
	printf "${BLU}"
	aviso $1
	printf "${NC}"
	if [ ${l} -gt 1 ]
	then
		head -$((l-1)) $1 | sed -r "${SED_SEARCH}"
	fi
	printf "${RED}"
	head -${l} $1 | tail -1 | sed -r "${SED_SEARCH}"
	printf "${YEL}"
	head -$((l+k)) $1 | tail -${k} | sed -r "${SED_SEARCH}"
	printf "${NC}"
	NLK=$((N-l-k))
	if [ ${NLK} -gt 0 ]
	then
		tail -${NLK} $1 | sed -r "${SED_SEARCH}"
	fi
	echo
	if [ $(read_key) == "B" ]
	then
		if [ ${i} -gt 1 ]
		then
			i=$((i-1))
		fi
	else
		i=$((i+1))
	fi
done
clear
printf "${BLU}"
aviso $1
printf "${NC}"
cat $1 | sed -r "${SED_SEARCH}"
