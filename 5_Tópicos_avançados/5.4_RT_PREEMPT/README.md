Primeiros passos em computador:

```
	sudo apt install bc bison flex libssl-dev make
	mkdir ~/rpi-kernel
	cd ~/rpi-kernel
	mkdir rt-kernel
	git clone https://github.com/raspberrypi/linux.git -b rpi-4.19.y-rt
	git clone https://github.com/raspberrypi/tools.git
	cd linux
	git checkout rpi-4.19.y-rt
	export ARCH=arm
	export CROSS_COMPILE=~/rpi-kernel/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-
	export INSTALL_MOD_PATH=~/rpi-kernel/rt-kernel
	export INSTALL_DTBS_PATH=~/rpi-kernel/rt-kernel
	export KERNEL=kernel7
	make bcm2709_defconfig
	sed -i -e 's/YYLTYPE yylloc/extern YYLTYPE yylloc/' scripts/dtc/dtc-lexer.lex.c
	make -j4 zImage modules dtbs
	make -j4 modules_install dtbs_install
	mkdir $INSTALL_MOD_PATH/boot
	./scripts/mkknlimg ./arch/arm/boot/zImage $INSTALL_MOD_PATH/boot/$KERNEL.img
	cd $INSTALL_MOD_PATH
	tar czf ../rt-kernel.tgz *
	cd ..
```

Copie o arquivo ```rt-kernel.tgz``` para o Raspberry Pi, e faça login nele:

```
	scp rt-kernel.tgz pi@<ipaddress>:/tmp
	ssh pi@<ipaddress>
```

Agora execute estes comandos no terminal do Raspberry Pi:

```
	cd /tmp
	tar xzf rt-kernel.tgz
	cd boot
	sudo cp -rd * /boot/
	cd ../lib
	sudo cp -dr * /lib/
	cd ../overlays
	sudo cp -d * /boot/overlays
	cd ..
	sudo cp -d bcm* /boot/
	sudo echo "kernel=vmlinuz-<VERSÃO_DO_KERNEL>" >> /boot/config.txt
```

Execute ```sudo reboot```, entre novamente no Raspberry Pi via ssh e execute ```uname -r``` para
conferir a nova versão do kernel.








<!--Siga [https://www.raspberrypi.com/documentation/computers/linux_kernel.html](https://www.raspberrypi.com/documentation/computers/linux_kernel.html) para instalar uma branch do kernel com RT PREEMPT (por exemplo, [https://github.com/raspberrypi/linux/tree/rpi-4.19.y-rt](https://github.com/raspberrypi/linux/tree/rpi-4.19.y-rt).

Pode ser necessário fazer [isso](https://github.com/BPI-SINOVOIP/BPI-M4-bsp/issues/4#issue-663584220).-->
