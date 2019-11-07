#!/bin/bash

mkdir build
cd build
cmake ../ > /dev/null
make > /dev/null
./Contraste_brilho ../../Imagens/Lena.png
cd ..
rm -rf build
