1 - Compile o módulo:

	make

2 - Carregue o módulo:

	sudo insmod chardev.ko

3 - Leia as mensagens fornecidas pelo módulo:

	dmesg | tail -5

4 - Crie o arquivo de dispositivo para o módulo. Por exemplo, se o módulo forneceu a seguinte mensagem:

	[18166.021222] Major number assinalado: 243.
	[18166.021255] Para comunicar como driver, crie um arquivo dev:
	[18166.021272]    mknod /dev/chardev c 243 0
	[18166.021283] Tente varios minors. Tente usar cat e echo com o arquivo dev.
	[18166.021294] Remova o arquivo dev e o modulo quando terminar.

execute

	sudo mknod /dev/chardev c 243 0

5 - Leia o arquivo de dispositivo:

	cat /dev/chardev

O dispositivo sempre retorna um caracter '1'.

6 - Desfaça o módulo e o seu arquivo:

	sudo rm /dev/chardev
	sudo rmmod chardev
	make clean
