#!/bin/bash

mkdir build
cd build
cmake ../ > /dev/null
make > /dev/null
p="../../Cascades/"
c1="haarcascade_frontalface_alt.xml"
c2="haarcascade_eye_tree_eyeglasses.xml"
for img in ../../Imagens/*.png
do
	./Faces $img $p$c1 $p$c2
done
cd ..
rm -rf build
