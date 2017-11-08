#!/bin/bash

echo Módulo que liga um LED no GPIO4.
echo
echo Compilando o modulo...
make
echo
echo Carregando o módulo...
sudo insmod gpiomod_output.ko
echo
echo Confira o LED ligado.
sleep 5
echo
echo Descarregando o módulo...
sudo rmmod gpiomod_output
echo
echo Confira o LED desligado.
echo
echo Limpando a pasta...
make clean
