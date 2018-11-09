#!/bin/bash

echo
echo Você leu README.md?
echo A SPI deverá estar habilitada para o código funcionar.
echo Vamos escrever na interface de comunicação SPI
echo através do arquivo /dev/spidev0.0.
echo
echo O comando
echo echo -ne \"\\x01\"
echo escreve o valor hexadecimal 0x01 na tela,
echo sem pular a linha \(\\n\).
echo O comando
echo echo -ne "\x01" \> /dev/spidev0.0
echo escreve o valor hexadecimal 0x01 em /dev/spidev0.0.
echo Se você tiver compilado e executado o código MSP430_code.c
echo no MSP430G2553, ele deverá piscar o LED uma vez.
echo
echo Pressione a tecla ENTER.
read
echo -ne "\x01" > /dev/spidev0.0
echo
echo Vamos piscar o LED 5 vezes.
echo Pressione a tecla ENTER.
read
echo -ne "\x05" > /dev/spidev0.0

