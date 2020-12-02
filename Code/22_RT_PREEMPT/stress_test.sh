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

T=5.1
echo "Executando '$1' por $T segundos..."
sudo $1 &
sleep $T
send_signal_by_name $1 SIGINT

echo "Executando '$1' por $T segundos com nice 19..."
nice -n 19 sudo $1 &
sleep $T
send_signal_by_name $1 SIGINT

echo "Executando '$1' por $T segundos, com"
echo "'cat /dev/urandom > /dev/null &' em paralelo..."
cat /dev/urandom > /dev/null &
sudo $1 &
sleep $T
send_signal_by_name $1 SIGINT

echo "Executando '$1' por $T segundos, com"
echo "'cat /dev/urandom > /dev/null &' e './eatmem.out' em paralelo..."
./eatmem.out &
sudo $1 &
sleep $T
send_signal_by_name $1 SIGINT
sleep 1
send_signal_by_name cat
send_signal_by_name "./eatmem.out"
