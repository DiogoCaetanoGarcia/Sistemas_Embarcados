#!/bin/bash

mkdir build
cd build
cmake ../ > /dev/null
make > /dev/null
for img in ../../Imagens/*.png
do
	./Detalhes_Imagem $img
done
cd ..
rm -rf build
