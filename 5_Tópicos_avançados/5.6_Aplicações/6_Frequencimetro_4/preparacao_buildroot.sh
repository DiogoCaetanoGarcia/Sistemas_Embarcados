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

PASTA_REPO_1="https://raw.githubusercontent.com/DiogoCaetanoGarcia/Sistemas_Embarcados/master/5_T%C3%B3picos_avan%C3%A7ados/5.6_Aplica%C3%A7%C3%B5es/"
PASTA_REPO_2="5_Frequencimetro_3/"
PASTA_REPO_3="6_Frequencimetro_4/"
for arq in Makefile freq.c freq.h lcd.c lcd.h main.c
do
	wget ${PASTA_REPO_1}${PASTA_REPO_2}${arq}
done
wget ${PASTA_REPO_1}${PASTA_REPO_3}frequencimetro-init
cd ../buildroot/package
mkdir frequencimetro
cd frequencimetro
for arq in Config.in frequencimetro.mk
do
	wget ${PASTA_REPO_1}${PASTA_REPO_3}$arq
done
cd ..
sed -i '/menu "Miscellaneous"/a\\tsource "package/frequencimetro/Config.in"' Config.in
cd ..
make $arquitetura
echo 'Para terminar a criação do exemplo, execute'
echo '   $ cd ~/exemplos_buildroot/buildroot'
echo '   $ make xconfig'
echo 'selecione "Target packages ==> Miscellaneous ==> frequencimetro",'
echo 'salve a configuração do Buildroot, e execute'
echo '   $ time make'
echo 'para criar a imagem a ser instalada no cartão SD.'
