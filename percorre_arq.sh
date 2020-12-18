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

function change_color()
{
	case "$1" in
		"Black")
			printf '\033[0;30m';;
		"Red")
			printf '\033[0;31m';;
		"Green")
			printf '\033[0;32m';;
		"Brown/Orange")
			printf '\033[0;33m';;
		"Blue")
			printf '\033[0;34m';;
		"Purple")
			printf '\033[0;35m';;
		"Cyan")
			printf '\033[0;36m';;
		"Light Gray")
			printf '\033[0;37m';;
		"Dark Gray")
			printf '\033[1;30m';;
		"Light Red")
			printf '\033[1;31m';;
		"Light Green")
			printf '\033[1;32m';;
		"Yellow")
			printf '\033[1;33m';;
		"Light Blue")
			printf '\033[1;34m';;
		"Light Purple")
			printf '\033[1;35m';;
		"Light Cyan")
			printf '\033[1;36m';;
		"White")
			printf '\033[1;37m';;
		"No color")
			printf '\033[0m';;
	esac
}

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
	change_color "Blue"
	aviso $1
	change_color "No color"
	if [ ${l} -gt 1 ]
	then
		head -$((l-1)) $1 | sed -r "${SED_SEARCH}"
	fi
	change_color "Red"
	head -${l} $1 | tail -1 | sed -r "${SED_SEARCH}"
	change_color "Yellow"
	head -$((l+k)) $1 | tail -${k} | sed -r "${SED_SEARCH}"
	change_color "No color"
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
change_color "Blue"
aviso $1
change_color "No color"
cat $1 | sed -r "${SED_SEARCH}"
