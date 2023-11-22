#!/bin/bash

echo Módulo que liga LEDs nos GPIOs 4, 24 e 25.
echo
echo Compilando o modulo...
make
echo
echo Carregando o módulo...
sudo insmod gpiomod_output.ko
echo
echo Confira os LEDs ligados.
sleep 5
echo
echo Descarregando o módulo...
sudo rmmod gpiomod_output
echo
echo Confira os LEDs desligados.
echo
echo Limpando a pasta...
make clean
