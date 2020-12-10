#!/bin/bash
echo
echo Compilando o módulo...
echo
make
read -p "Pressione ENTER para continuar"
echo Carregando o módulo...
sudo insmod hello.ko
echo
echo Veja os módulos carregados:
lsmod
read -p "Pressione ENTER para continuar"
echo Veja a mensagem de carregamento do módulo:
echo
dmesg | tail -1
echo
echo Veja se houve algum erro ou warning no carregamento do módulo:
cat /var/log/messages | grep hello
read -p "Pressione ENTER para continuar"
echo Descarregando o módulo...
sudo rmmod hello
echo
echo Veja a mensagem de descarregamento do módulo:
echo
dmesg | tail -1
read -p "Pressione ENTER para continuar"
echo Limpando a pasta...
echo
make clean
