#!/bin/bash
echo
echo Compilando o módulo...
echo
make
echo
echo Carregando o módulo...
sudo insmod hello.ko
echo
echo Veja os módulos carregados:
lsmod
echo
echo Veja a mensagem de carregamento do módulo:
echo
dmesg | tail -1
echo
echo Veja se houve algum erro ou warning no carregamento do módulo:
cat /var/log/messages | grep hello
echo
echo Descarregando o módulo...
sudo rmmod hello
echo
echo Veja a mensagem de descarregamento do módulo:
echo
dmesg | tail -1
echo
echo Limpando a pasta...
echo
make clean
