#!/bin/bash

mkdir build
cd build
cmake ../ > /dev/null
make > /dev/null
./Media_linhas_colunas ../../Imagens/Olho.png
cd ..
rm -rf build
