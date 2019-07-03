#!/bin/bash

PS3='Escolha o modelo do Raspberry Pi: '
options=("RPi 0" "RPi 0W" "RPi 2" "RPi 3_64" "RPi 3" "RPi 3_qt5we" "RPi 1" "Exit")
select opt in "${options[@]}"
do
	case $opt in
		"RPi 0")
			arquitetura=raspberrypi0_defconfig
			break
			;;
		"RPi 0W")
			arquitetura=raspberrypi0w_defconfig
			break
			;;
		"RPi 2")
			arquitetura=raspberrypi2_defconfig
			break
			;;
		"RPi 3_64")
			arquitetura=raspberrypi3_64_defconfig
			break
			;;
		"RPi 3")
			arquitetura=raspberrypi3_defconfig
			break
			;;
		"RPi 3_qt5we")
			arquitetura=raspberrypi3_qt5we_defconfig
			break
			;;
		"RPi 1")
			arquitetura=raspberrypi_defconfig
			break
			;;
		"Exit")
			echo Script cancelado.
			exit
			break
			;;
		*) echo "Opção inválida $REPLY";;
	esac
done

echo Arquitetura escolhida: $arquitetura

mkdir ~/exemplos_buildroot
cd ~/exemplos_buildroot
git clone https://github.com/buildroot/buildroot.git buildroot
mkdir frequencimetro
cd frequencimetro
for arq in Makefile freq.c freq.h lcd.c lcd.h main.c
do
	wget https://raw.githubusercontent.com/DiogoCaetanoGarcia/Sistemas_Embarcados/master/Code/27_Aplica%C3%A7%C3%B5es/Frequencimetro_2/$arq
done
cd ../buildroot/package
mkdir frequencimetro
cd frequencimetro
for arq in frequencimetro-init Config.in frequencimetro.mk
do
	wget https://raw.githubusercontent.com/DiogoCaetanoGarcia/Sistemas_Embarcados/master/Code/27_Aplica%C3%A7%C3%B5es/Frequencimetro_3/$arq
done
cd ..
sed -i '/menu "Miscellaneous"/a\\tsource "package/frequencimetro/Config.in"' Config.in
cd ..
make $arquitetura
