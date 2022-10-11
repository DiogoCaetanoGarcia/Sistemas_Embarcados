#!/bin/bash

make > /dev/null
for img in ../Imagens/*.png
do
	echo "Código em C:"
	./Detalhes_Imagem $img
	echo "Código em Python:"
	python Detalhes_Imagem.py $img
done
make clean > /dev/null