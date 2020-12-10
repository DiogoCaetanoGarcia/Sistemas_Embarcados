#!/bin/bash
echo
echo Compilando o módulo...
echo
make
echo
echo Carregando o módulo...
sudo insmod hello.ko
dmesg | tail -1
echo
read -p "Pressione ENTER para continuar"
clear
echo Veja as variaveis hello_int e hello_str no arquivo /proc/kallsyms
cat /proc/kallsyms | grep hello
read -p "Pressione ENTER para continuar"
clear
echo Descarregando o módulo...
sudo rmmod hello
echo
read -p "Pressione ENTER para continuar"
clear
echo Carregando o módulo com hello_int=3...
sudo insmod hello.ko hello_int=3
dmesg | tail -1
read -p "Pressione ENTER para continuar"
clear
echo Descarregando o módulo...
sudo rmmod hello
echo
read -p "Pressione ENTER para continuar"
clear
echo Carregando o módulo com hello_int=4, hello_str=Olaaa...
sudo insmod hello.ko hello_int=4 hello_str="Olaaa"
dmesg | tail -1
read -p "Pressione ENTER para continuar"
clear
echo Descarregando o módulo...
sudo rmmod hello
echo
echo Limpando a pasta...
make clean
