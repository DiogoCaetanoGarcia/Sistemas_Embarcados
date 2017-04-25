#!/bin/bash

GPIO_PATH=/sys/class/gpio
echo Este script usa uma variavel para facilitar o trabalho: \$GPIO_PATH=$GPIO_PATH
echo Torne este script executavel usando chmod
echo Execute este script como super-usuario! \(sudo ./Ex2.sh\)
echo Conecte o anodo do LED ao pino GPIO4.
echo Conecte o catodo do LED a um resistor.
echo Conecte o resistor ao GND.
echo Criando conexao ao GPIO4 via sysfs...
echo 4 >> $GPIO_PATH/export
echo Tornando o pino GPIO4 saida em nivel alto para ligar o LED...
sudo echo out > $GPIO_PATH/gpio4/direction
sudo echo 1 > $GPIO_PATH/gpio4/value
echo Aguardando 5 segundos...
sleep 5
echo Apagando o LED...
echo 0 > $GPIO_PATH/gpio4/value
echo Liberando o pino GPIO4...
echo 4 >> $GPIO_PATH/unexport
echo Fim.
