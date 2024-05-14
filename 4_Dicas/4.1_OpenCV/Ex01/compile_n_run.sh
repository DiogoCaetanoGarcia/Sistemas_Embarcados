#!/bin/bash

make
for img in ../Imagens/*.png
do
	./DisplayImage $img
done

make clean
