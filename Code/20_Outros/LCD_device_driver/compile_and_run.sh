#!/bin/bash

MOD=lcd_device_driver
TEXTO="Oi LCD"
echo Compilando o modulo...
make
echo
echo Carregando o módulo...
sudo insmod $MOD.ko
echo
echo Alterando permissões no device para permitir sua escrita...
sudo chmod 777 /dev/$MOD
clear
echo Lendo o texto atual do LCD...
sudo cat /dev/$MOD
read
clear
echo Escrevendo $TEXTO no LCD
sudo echo $TEXTO > /dev/$MOD
echo Lendo o texto atual do LCD...
sudo cat /dev/$MOD
read
clear
echo Descarregando o módulo...
sudo rmmod $MOD
echo
echo Limpando a pasta...
make clean
