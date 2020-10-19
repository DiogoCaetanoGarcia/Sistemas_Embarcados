#!/bin/bash

# Para RPi 0, 1 e 2
# UART=/dev/ttyAMA0
# Para RPi 0W, 3 e 4
UART=/dev/ttyS0

echo Leia o arquivo README.txt antes de rodar este exemplo!
echo
echo
echo

# Compile e rode o codigo do MSP430 antes de rodar os exemplos desta pasta. É necessario instalar as ferramentas de desenvolvimento para o MSP430:
# $ sudo apt-get install msp430-libc mspdebug msp430mcu binutils-msp430 gcc-msp430 gdb-msp430
./compile_run_MSP430.sh MSP430_code.c

echo
echo
echo

# Configure a porta serial
stty -F $UART ispeed 9600 ospeed 9600 cs8 -cstopb -parenb
# Confira o resultado da configuracao
stty -F $UART -a

echo
echo
echo

echo Pressione ENTER para ver o LED do MSP430 piscar 1 vez
read
echo -n -e \\x01 >> $UART
echo Pressione ENTER para ver o LED do MSP430 piscar 3 vezes
read
echo -n -e \\x03 >> $UART
