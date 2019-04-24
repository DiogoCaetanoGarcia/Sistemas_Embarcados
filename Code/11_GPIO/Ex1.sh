#!/bin/bash

clear
echo Hello RPi LED blink!
echo
echo Torne este script executavel usando chmod
echo Execute este script como super-usuario! \(sudo ./Ex1.sh\)
echo
echo Conecte o anodo do LED ao pino GPIO4.
echo Conecte o catodo do LED a um resistor.
echo Conecte o resistor ao GND.
echo
echo Veja os arquivos disponiveis para conexao I/O
ls -l /sys/class/gpio
read
clear
echo Criando conexao ao GPIO4 via sysfs...
echo 4 >> /sys/class/gpio/export
echo Confira a criacao da pasta \'gpio4\'
ls -l /sys/class/gpio
read
clear
echo Tornando o pino GPIO4 saida em nivel alto para ligar o LED...
sudo echo out > /sys/class/gpio/gpio4/direction
sudo echo 1 > /sys/class/gpio/gpio4/value
echo
echo Aguardando 5 segundos...
sleep 5
echo
echo Apagando o LED...
echo 0 > /sys/class/gpio/gpio4/value
echo
echo Liberando o pino GPIO4...
echo 4 >> /sys/class/gpio/unexport
echo Confira o fim da pasta \'gpio4\'
ls -l /sys/class/gpio
echo Fim.
echo
