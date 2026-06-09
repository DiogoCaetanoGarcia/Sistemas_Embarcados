#!/bin/bash

MOD=gpiomod_output
echo Módulo que permite acender e apagar um LED no GPIO4 pelo terminal.
echo
echo Compilando o modulo...
make
echo
echo Carregando o módulo...
sudo insmod $MOD.ko
echo
echo Alterando permissões no device para permitir sua escrita...
sudo chmod 777 /dev/$MOD
echo Lendo o valor atual do pino...
sudo cat /dev/$MOD
echo
echo
for k in {1..5}
do
	echo Acendendo o LED...
	sudo echo 1 > /dev/$MOD
	echo Lendo o valor atual do pino...
	sudo cat /dev/$MOD
	echo
	sleep 0.5
	echo Apagando o LED...
	sudo echo 0 > /dev/$MOD
	echo Lendo o valor atual do pino...
	sudo cat /dev/$MOD
	echo
	sleep 0.5
done
echo
echo Descarregando o módulo e apagando o LED...
sudo rmmod $MOD
echo
echo Limpando a pasta...
make clean
