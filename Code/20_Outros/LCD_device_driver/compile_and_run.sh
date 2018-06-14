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
echo
echo Lendo o texto atual do LCD...
sudo cat /dev/$MOD
echo
echo Escrevendo $TEXTO no LCD
sudo echo $TEXTO > /dev/$MOD
echo Lendo o texto atual do LCD...
sudo cat /dev/$MOD
echo
echo Descarregando o módulo e apagando o LED...
sudo rmmod $MOD
echo
echo Limpando a pasta...
make clean
