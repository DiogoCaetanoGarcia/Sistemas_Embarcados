#!/bin/sh

echo "Conecte um LED+resistor a GPIO4"
echo "Execute \"gpioinfo\" para ver os pinos GPIO disponíveis:"

echo "Acendendo o LED"
gpioset -t 0s -c 0 4=1
echo "Aguardando 5 segundos"
sleep 5
echo "Apagando o LED"
gpioset -t 0s -c 0 4=0

echo "Fim"
