#!/bin/bash

MOD=lcd_device_driver
TEXTO="Oi LCD"
echo Compilando o overlay...
dtc -@ -I dts -O dtb -o lcd_device_driver.dtbo lcd_device_driver-overlay.dts
echo Instalando o overlay...
sudo cp lcd_device_driver.dtbo /boot/firmware/overlays/
sudo dtoverlay lcd_device_driver
echo
echo Verificando o overlay instalado...
echo
sudo dtoverlay -l
echo
echo Compilando o modulo...
make
echo
echo Carregando o módulo...
sudo insmod $MOD.ko
echo
echo Conferindo mensagens de inserção do módulo...
dmesg | grep lcd
echo
echo Alterando permissões no device para permitir sua escrita...
sudo chmod 777 /dev/$MOD
# clear
echo Lendo o texto atual do LCD...
sudo cat /dev/$MOD
read
# clear
echo Escrevendo $TEXTO no LCD
sudo echo -n $TEXTO > /dev/$MOD
echo Lendo o texto atual do LCD...
sudo cat /dev/$MOD
read
#vclear
echo Descarregando o módulo...
sudo rmmod $MOD
echo
echo Limpando a pasta...
make clean
echo
echo Removendo o overlay...
sudo dtoverlay -r 0
echo Verificando o overlay desinstalado...
echo
sudo dtoverlay -l
