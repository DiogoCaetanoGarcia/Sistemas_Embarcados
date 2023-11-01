#!/bin/bash

for img in ../Imagens/*
do
	echo --- $img ---
	./call_GoogLeNet.out \
		--class=files/synset_words.txt \
		--image=$img \
		--model=files/bvlc_googlenet.caffemodel \
		--proto=files/bvlc_googlenet.prototxt
done