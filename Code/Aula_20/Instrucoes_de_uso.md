1 - Para compilar módulos do kernel, é preciso obter o código do kernel Linux para o Raspberry Pi.

Execute:

	sudo wget https://raw.githubusercontent.com/notro/rpi-source/master/rpi-source -O /usr/bin/rpi-source && sudo chmod +x /usr/bin/rpi-source && /usr/bin/rpi-source -q --tag-update

	rpi-source

Se este último não completar a instalação, siga as instruções na tela para instalar as dependências que faltam. Por exemplo, se surgir a mensagem:

	ERROR: bc is NOT installed. Needed by 'make modules_prepare'. On Raspbian, run 'sudo apt-get install bc' to install it.

Execute o que ele pede:

	sudo apt-get install bc

Completando a instalação, execute 

	sudo ln -s /usr/src/linux-headers-$(uname -r)/ /lib/modules/$(uname -r)/build

2 - As aulas a seguir são baseadas no livro "The Linux Kernel Module Programming Guide", de P. Salzman, M. Burian e O. Pomerantz:

	http://www.tldp.org/LDP/lkmpg/2.6/html/lkmpg.html

O livro está disponível na pasta "Refs" deste repositório.
