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
echo Mudando permissões do arquivo
sudo chmod 777 /dev/chardev
echo Veja o resultado da leitura do dispositivo
echo sudo cat /dev/chardev
sudo cat /dev/chardev
echo
echo
read -p "Pressione ENTER para continuar"
clear
echo Veja o resultado da escrita no dispositivo
echo "sudo echo -n 12345 > /dev/chardev"
sudo echo -n 12345 > /dev/chardev
echo "sudo cat /dev/chardev"
sudo cat /dev/chardev
echo
echo
echo "sudo echo -n ABCDE > /dev/chardev"
sudo echo -n ABCDE > /dev/chardev
echo "sudo cat /dev/chardev"
sudo cat /dev/chardev
echo
echo
read -p "Pressione ENTER para continuar"
clear
echo Descarregando o módulo...
sudo rmmod chardev
echo Limpando a pasta...
echo
make clean
