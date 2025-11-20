#!/bin/bash

function send_signal_by_name()
{
	if [ "$#" -ne 2 ];
	then
		s=SIGKILL
	else
		s=$2
	fi
	p=$(pidof $1)
	if [ -z $p ];
	then
		echo $1 terminated
	else
		sudo kill -s $s $p > /dev/null
	fi
}

if [ $# -lt 1 ]
then
	make
	echo "Digite o número correspondente ao código compilado:"
	for f in Ex*.out
	do
		echo $(echo ${f} | grep -oP "(?<=Ex).*?(?=\.out)")": ${f}"
	done
	exit -1
fi


E=./Ex${1}.out
if [ ! -f $E ]; then
	echo Programa $E não existe!
	exit -2
fi

echo "Executando '$E'..."
sudo $E

# echo "Aperte ENTER"
# read

echo "Executando '$E' com nice 19..."
nice -n 19 sudo $E

# echo "Aperte ENTER"
# read

echo "Executando '$E' por $T segundos, com"
echo "'cat /dev/urandom > /dev/null &' em paralelo..."
cat /dev/urandom > /dev/null &
sudo $E

# echo "Aperte ENTER"
# read

echo "Executando '$E' por $T segundos, com"
echo "'cat /dev/urandom > /dev/null &' e './eatmem.out' em paralelo..."
./eatmem.out &
sudo $E
# sleep 1
send_signal_by_name cat
send_signal_by_name "./eatmem.out"
