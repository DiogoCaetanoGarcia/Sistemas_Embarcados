#!/bin/bash
echo
echo Compilando o módulo...
echo
make
echo
read -p "Pressione ENTER para continuar"
clear
echo Carregando o módulo...
sudo insmod chardev.ko
echo
echo Veja os módulos carregados:
lsmod
echo
read -p "Pressione ENTER para continuar"
clear
echo Veja a mensagem de carregamento do módulo:
echo
dmesg | tail -3
echo
read -p "Pressione ENTER para continuar"
clear
echo Veja o dispositivo criado
ls /dev/chardev -l
echo
read -p "Pressione ENTER para continuar"
clear
echo Veja o resultado da leitura do dispositivo
sudo cat /dev/chardev
echo
echo
read -p "Pressione ENTER para continuar"
clear
echo Descarregando o módulo...
sudo rmmod chardev
echo
echo Veja que o dispositivo foi removido
ls /dev/chardev -l
echo
read -p "Pressione ENTER para continuar"
clear
echo Limpando a pasta...
echo
make clean
