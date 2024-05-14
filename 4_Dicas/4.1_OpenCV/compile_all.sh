#!/bin/bash

for folder in ./Ex*
do
	cd $folder
	make && echo make $folder OK! &
	cd ..
done
