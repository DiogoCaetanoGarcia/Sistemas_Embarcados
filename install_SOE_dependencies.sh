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

show_box "apt update"
sudo apt update
show_box "Install GCC, G++ etc"
sudo apt install build-essential
show_box "Install git"
sudo apt install git-all
show_box "Install cal"
sudo apt install ncal
show_box "Install WiringPi"
CUR_FOLDER=$(pwd)
cd ~
git clone https://github.com/WiringPi/WiringPi
cd ~/WiringPi
./build
cd ${CUR_FOLDER}
show_box "Install Python RPi.GPIO (GPIO)"
python -m pip install RPi.GPIO
show_box "Install Python pyserial (UART)"
python -m pip install pyserial
show_box "Install Python spidev (SPI)"
python -m pip install spidev
show_box "Install Python smbus2 (I2C)"
python -m pip install smbus2
show_box "Install i2c-tools"
sudo apt install -y i2c-tools
show_box "Install curl"
sudo apt install curl
show_box "Install Apache"
sudo apt install apache2
show_box "Install cmake"
sudo apt -y install cmake
show_box "Install OpenCV (C++)"
sudo apt install libopencv-dev
show_box "Install OpenCV (Python)"
sudo apt install python3-opencv
show_box "Install GTK"
sudo apt install libgtk2.0-dev
show_box "Install rt-tests"
sudo apt-get install libnuma-dev
show_box "Install buildroot dependencies and get buildroot repository"
sudo apt-get install build-essential libncurses5-dev bzr cvs git mercurial rsync subversion
CUR_FOLDER=$(pwd)
mkdir ~/exemplos_buildroot
cd ~/exemplos_buildroot
git clone https://github.com/buildroot/buildroot.git buildroot
cd ${CUR_FOLDER}
CUR_FOLDER=$(pwd)
cd ~
git clone git://git.kernel.org/pub/scm/utils/rt-tests/rt-tests.git
cd ~/rt-tests
git checkout stable/v1.0
make all
sudo make install
cd ${CUR_FOLDER}
show_box "Instalação demorada para os códigos das aulas finais (LKMs)"
curl https://raw.githubusercontent.com/DiogoCaetanoGarcia/Sistemas_Embarcados/master/5_T%C3%B3picos_avan%C3%A7ados/5.2_LKMs/README.md
