#!/bin/bash

function show_box()
{
	SHOW_BOX_MSG=$1
	SHOW_BOX_L=${#SHOW_BOX_MSG}
	SHOW_BOX_L=$((SHOW_BOX_L+4))
	SHOW_BOX_LINE=""
	for SHOW_BOX_i in $(seq $SHOW_BOX_L)
	do
		SHOW_BOX_LINE=${SHOW_BOX_LINE}"-"
	done
	echo
	echo ${SHOW_BOX_LINE}
	echo \| $SHOW_BOX_MSG \|
	echo ${SHOW_BOX_LINE}
	echo
}

show_box "Compilar e inserir módulo"
make
sudo insmod chardev.ko

show_box "Gerar lista de primos pelo Octave"
octave --eval "disp(primes(1000)')" > primos.txt
sed -i "s/ /g" primos.txt

show_box "Gerar lista de primos pelo LKM"
rm -f primos_lkm.txt
for i in {1..168}
do
	sudo cat /dev/chardev >> primos_lkm.txt
done
sed -i "s/ /g" primos_lkm.txt

show_box "Comparar listas de primos"
diff primos.txt primos_lkm.txt

show_box "Cleanup"
sudo rmmod chardev
make clean
rm primos.txt primos_lkm.txt