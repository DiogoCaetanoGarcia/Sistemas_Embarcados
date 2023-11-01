#!/bin/bash

echo Após cada execução do programa,
echo confira a imagem \'yolo_output.png\'
echo gerada nesta pasta, e aperte ENTER
echo para processar a próxima imagem.
echo

for img in ../Imagens/*
do
	./call_yolo.out $img
	echo
	echo "Pressione ENTER"
	read
done