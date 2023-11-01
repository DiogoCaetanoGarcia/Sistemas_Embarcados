#!/bin/bash

for img in ../Imagens_placas/*
do
	echo --- $img ---
	./call_tesseract.out $img
done