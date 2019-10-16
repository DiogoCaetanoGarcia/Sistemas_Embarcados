#!/bin/bash

F=/dev/ttyS0
stty -F $F 115200
fim=$(printf "SAIR")
pedido=OK
while [ $pedido != $fim ]
do
	echo Aguardando dado via Bluetooth...
	pedido=$(head -1 $F)
	echo Recebido: $pedido
	sudo printf "RPi: $pedido\r\n" > $F
done

