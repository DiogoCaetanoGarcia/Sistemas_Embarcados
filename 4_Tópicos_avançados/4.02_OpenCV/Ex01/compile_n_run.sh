#!/bin/bash

echo ">>> Criando pasta para guardar executável..."
mkdir build
cd build
echo ">>> Preparando arquivos para compilação..."
cmake ../
echo ">>> Compilando"
make
echo ">>> Executando código..."
echo ">>> Aperte qualquer botão para fechar o programa."
./DisplayImage ../../Imagens/Lena.png
echo ">>> Limpando pasta com executável e arquivos para compilação..."
cd ..
rm -rf build
echo ">>> FIM."
