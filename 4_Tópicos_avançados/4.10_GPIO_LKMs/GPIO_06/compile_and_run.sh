#!/bin/bash

echo Módulo que liga/desliga um LED no GPIO24 de acordo com um botão no GPIO4.
echo
echo Compilando o modulo...
make
echo
echo Carregando o módulo...
sudo insmod gpiomod_output.ko
echo
echo Pressione o botão para ligar e desligar o LED.
sleep 30
echo
echo Descarregando o módulo...
sudo rmmod gpiomod_output
echo
echo Limpando a pasta...
make clean
