#!/bin/bash
echo
echo Compilando o módulo...
echo
make
echo
read -p "Pressione ENTER para continuar"
echo Carregando o módulo...
sudo insmod hello.ko
echo
echo Veja as informações que inserimos no kernel:
modinfo hello.ko
read -p "Pressione ENTER para continuar"
echo Descarregando o módulo...
sudo rmmod hello
read -p "Pressione ENTER para continuar"
echo Limpando a pasta...
echo
make clean
