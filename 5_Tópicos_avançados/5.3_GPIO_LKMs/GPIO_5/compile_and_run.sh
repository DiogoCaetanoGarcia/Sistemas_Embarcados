#!/bin/bash

MOD=gpiomod_output
echo Módulo que permite piscar um LED no GPIO4 pelo terminal, a diferentes frequencias.
echo
echo Compilando o modulo...
make
echo
echo Carregando o módulo...
sudo insmod $MOD.ko
echo
echo Alterando permissões no device para permitir sua escrita...
sudo chmod 777 /dev/$MOD
echo
echo Lendo a frequencia atual do pino...
sudo cat /dev/$MOD
echo
echo
sleep 5
echo
echo Trocando a frequencia do pino
sudo echo 5 > /dev/$MOD
echo
echo Lendo a frequencia atual do pino...
sudo cat /dev/$MOD
echo
echo
sleep 5
echo
echo Descarregando o módulo e apagando o LED...
sudo rmmod $MOD
echo
echo Limpando a pasta...
make clean
