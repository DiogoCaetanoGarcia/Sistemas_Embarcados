#!/bin/bash

mkdir build
cd build
cmake ../ > /dev/null
make > /dev/null
./Mapeamento_Linear ../../Imagens/Lena.png
cd ..
rm -rf build
