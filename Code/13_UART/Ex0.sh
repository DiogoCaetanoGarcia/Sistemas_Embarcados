#!/bin/bash

# Para RPi 0, 1 e 2
# UART=/dev/ttyAMA0
# Para RPi 0W, 3 e 4
UART=/dev/ttyS0

# Configure a porta serial
stty -F $UART ispeed 9600 ospeed 9600 cs8 -cstopb -parenb
# Confira o resultado da configuracao
stty -F $UART -a

echo Pressione ENTER para ver o LED do MSP430 piscar 1 vez
read
echo -n -e \\x01 >> $UART
echo Pressione ENTER para ver o LED do MSP430 piscar 3 vezes
read
echo -n -e \\x03 >> $UART
