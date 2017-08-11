#!/bin/bash

msp430-gcc -Os -Wall -g -mmcu=msp430g2553 -o $1.elf $1
sudo mspdebug rf2500 "prog $1.elf"
rm $1.elf
