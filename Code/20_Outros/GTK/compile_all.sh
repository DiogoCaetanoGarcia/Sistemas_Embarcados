#!/bin/bash

for arq in *.c
do
	gcc $arq `pkg-config --cflags --libs gtk+-3.0` -o $arq\_exe
done
