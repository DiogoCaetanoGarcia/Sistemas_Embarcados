#!/bin/bash

for arq in *.c
do
	gcc $arq -o $arq.out -lpthread
done
