#!/bin/bash

for folder in ./Ex*
do
	cd $folder
	make clean
	cd ..
done
