#!/bin/bash
echo
echo Compilando o módulo...
echo
make
echo
echo Carregando o módulo...
sudo insmod hello.ko
echo
echo Veja as informações que inserimos no kernel:
modinfo hello.ko
echo
echo Descarregando o módulo...
sudo rmmod hello
echo
echo Limpando a pasta...
echo
make clean
