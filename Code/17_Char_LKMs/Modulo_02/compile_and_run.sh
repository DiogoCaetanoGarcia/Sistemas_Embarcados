#!/bin/bash
echo
echo Compilando o módulo...
echo
make
echo
echo Carregando o módulo...
sudo insmod chardev.ko
echo
echo Veja os módulos carregados:
lsmod
echo
echo Veja a mensagem de carregamento do módulo:
echo
dmesg | tail -3
echo
echo Veja o dispositivo criado
ls /dev/chardev -l
echo
echo Veja o resultado da leitura do dispositivo
sudo cat /dev/chardev
echo
echo
echo Descarregando o módulo...
sudo rmmod chardev
echo
echo Veja que o dispositivo foi removido
ls /dev/chardev -l
echo
echo Limpando a pasta...
echo
make clean
