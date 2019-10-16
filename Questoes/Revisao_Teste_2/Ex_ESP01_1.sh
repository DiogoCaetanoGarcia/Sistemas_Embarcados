#!/bin/bash

F=/dev/ttyS0

if [ $# -lt 2 ]
then
	echo "Teste de comunicação com o ESP-01, por envio"
	echo "de pedidos AT. Por exemplo, tente:"
	echo "   $0 AT+CWLAP OK"
	echo "   $0 AT+GMR OK"
	echo "   $0 AT+CIFSR OK"
	exit -1
fi

stty -F $F 9600
resp="NOT"
echo Fazendo pedido $1...
printf "$1\r\n" > $F
while [ "$resp" != "$2" ]
do
	resp=$(head -1 $F);
	printf "==> $resp\n"
done
