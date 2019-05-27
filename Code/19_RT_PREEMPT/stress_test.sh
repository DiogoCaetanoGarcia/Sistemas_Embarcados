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
	if [ -z "{$p}" ];
	then
		echo $1 terminated
	else
		sudo kill -s $s $p > /dev/null
	fi
}

echo "Executando '$1' por 6 segundos..."
sudo $1 &
sleep 6
send_signal_by_name $1 SIGINT

echo "Executando '$1' por 6 segundos, com"
echo "'cat /dev/urandom > /dev/null &' em paralelo..."
cat /dev/urandom > /dev/null &
sudo $1 &
sleep 6
send_signal_by_name $1 SIGINT
send_signal_by_name cat

echo "Executando '$1' por 6 segundos, com"
echo "'cat /dev/urandom > /dev/null &' e './eatmem.out' em paralelo..."
cat /dev/urandom > /dev/null &
./eatmem.out &
sudo $1 &
sleep 6
send_signal_by_name $1 SIGINT
send_signal_by_name "./eatmem.out" SIGKILL
send_signal_by_name cat
