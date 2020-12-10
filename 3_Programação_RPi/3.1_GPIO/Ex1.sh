#!/bin/bash

echo "Conecte um LED+resistor a GPIO4"
echo "Pinos GPIO disponíveis:"
ls -l /sys/class/gpio
echo "Criando conexao ao GPIO4 via sysfs"
sudo echo "4" >> /sys/class/gpio/export
echo "Confira a criacao da pasta 'gpio4'"
ls -l /sys/class/gpio
echo "Acendendo o LED"
sudo echo "out" > /sys/class/gpio/gpio4/direction
sudo echo "1" > /sys/class/gpio/gpio4/value
echo "Aguardando 5 segundos"
sleep 5
echo "Apagando o LED"
echo "0" > /sys/class/gpio/gpio4/value
echo "Liberando o pino GPIO4"
echo "4" >> /sys/class/gpio/unexport
echo "Fim"
