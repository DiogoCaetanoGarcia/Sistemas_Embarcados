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
clear
echo Veja o resultado da leitura do dispositivo
for k in {0..110}
do
	sudo cat /dev/chardev
	echo
done
echo
read -p "Pressione ENTER para continuar"
clear
echo Descarregando o módulo...
sudo rmmod chardev
echo Limpando a pasta...
echo
make clean
