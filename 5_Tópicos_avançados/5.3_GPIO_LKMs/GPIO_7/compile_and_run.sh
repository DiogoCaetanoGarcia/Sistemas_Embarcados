#!/bin/bash

echo Módulo que liga um LED no GPIO4 usando DTS.
echo
echo Compilando o overlay...
dtc -@ -I dts -O dtb -o gpiomod_output.dtbo gpiomod_output-overlay.dts
echo Instalando o overlay...
sudo cp gpiomod_output.dtbo /boot/firmware/overlays/
sudo dtoverlay gpiomod_output
echo
echo Verificando o overlay instalado...
echo
sudo dtoverlay -l
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
echo
echo Removendo o overlay...
sudo dtoverlay -r 0
echo Verificando o overlay desinstalado...
echo
sudo dtoverlay -l
