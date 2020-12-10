#!/bin/bash

mkdir build
cd build
cmake ../ > /dev/null
make > /dev/null
./Criar_Imagem
cd ..
rm -rf build
