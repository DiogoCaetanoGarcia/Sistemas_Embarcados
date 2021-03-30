#!/bin/bash

mkdir build
cd build
cmake ../ > /dev/null
make > /dev/null
./Misturar_Imagens ../../Imagens/Lena.png ../../Imagens/Baboon.png 0.25
./Misturar_Imagens ../../Imagens/Lena.png ../../Imagens/Baboon.png 0.5
./Misturar_Imagens ../../Imagens/Lena.png ../../Imagens/Baboon.png 0.75
./Misturar_Imagens ../../Imagens/Lena_grey.png ../../Imagens/Baboon_grey.png 0.25
./Misturar_Imagens ../../Imagens/Lena_grey.png ../../Imagens/Baboon_grey.png 0.5
./Misturar_Imagens ../../Imagens/Lena_grey.png ../../Imagens/Baboon_grey.png 0.75
cd ..
rm -rf build
