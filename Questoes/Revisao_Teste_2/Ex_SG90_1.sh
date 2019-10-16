#!/bin/bash

P=4

function sqwv()
{
	echo "HI = $1 s, LO = $2 s"
	t1=$(date +%s%3N)
	for i in $(seq 1 $3)
	do
		echo 1 > /sys/class/gpio/gpio$P/value
		sleep $1
		echo 0 > /sys/class/gpio/gpio$P/value
		sleep $2
	done
	t2=$(date +%s%3N)
	t2=$((t2-t1))
	echo Tempo = $t2 ms
}

echo "Execute este programa como super-usuario (sudo $0)!!!"
echo
echo "Este script deveria gerar quatro ondas de 50Hz"
echo "com ciclos de trabalho diferentes para controle"
echo "do servo SG90, cada uma durando 0,5 segundos."
echo "Repare na medida de duração das ondas."
echo

if [ ! -d /sys/class/gpio/gpio$P ]
then
	echo $P > /sys/class/gpio/export
fi
echo out > /sys/class/gpio/gpio$P/direction
sqwv 0.01  0.019  25
sqwv 0.012 0.0188 25
sqwv 0.018 0.0182 25
sqwv 0.02  0.018  25

echo $P > /sys/class/gpio/unexport
