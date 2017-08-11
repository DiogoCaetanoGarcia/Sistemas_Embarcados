# RT PREEMPT no Raspberry Pi

0 - O kernel Linux não oferece performance hard real-time, pois ele não garante a temporização tão precisa na execução de processos e threads. Isso acontece porque o kernel Linux executa multitasking cooperativo. Já o patch RT PREEMPT (Realtime Preemption) do kernel Linux garante a execução de multitasking preemptivo.
	
- No multitasking COOPERATIVO, os processos devem voluntariamente ceder sua vez para outros processos.
- No multitasking PREEMPTIVO, os processos podem ser interrompidos por outros processos de maior prioridade.

Fica claro que, no multitasking cooperativo, o kernel pode atrapalhar a execução de processos no userspace, afetando a temporização destes.

Referências:

	https://en.wikipedia.org/wiki/Cooperative_multitasking
	https://en.wikipedia.org/wiki/Preemption_(computing)

1 - Antes de instalar o patch RT PREEMPT, é recomendável fazer um backup do cartão SD do Raspberry Pi no seu computador. Se houver algum imprevisto na instalação ou na execução do RT PREEMPT, você poderá recuperar o estado do cartão pelo backup. Aqui estão algumas formas de fazer o backup:

	https://raspberrypi.stackexchange.com/a/313
	http://lifehacker.com/how-to-clone-your-raspberry-pi-sd-card-for-super-easy-r-1261113524
	https://www.raspberrypi.org/documentation/linux/filesystem/backup.md

2 - Faça login no Raspberry Pi, e execute os seguintes comandos:

	sudo rm -r /boot/overlays/
	sudo rm -r /lib/firmware/
	cd /tmp
	wget http://download.frank-durr.de/kernel-4.4.9-rt17.tgz
	tar xzf kernel-4.4.9-rt17.tgz
	cd boot
	sudo cp -rd * /boot/
	cd ../lib
	sudo cp -dr * /lib/

Estes comandos instalam um kernel já compilado com o patch RT PREEMPT (http://www.frank-durr.de/?p=203). É possível recompilar o kernel para a sua versão de sistema operacional, mas este processo é mais complicado.

3 - Execute

	sudo nano /boot/cmdline.txt

para acrescentar o seguinte texto a este arquivo:

	sdhci_bcm2708.enable_llm=0 dwc_otg.fiq_enable=0 dwc_otg.fiq_fsm_enable=0 dwc_otg.nak_holdoff=0

Não acrescente quebras de linhas ao inserir este texto.

4 - Execute 

	dmesg | grep "Machine model"

para descobrir o modelo do seu Raspberry Pi, e execute

	cat /proc/cpuinfo | grep Hardware

para descobrir o hardware específico dele.

OBSERVAÇÃO: outra forma de descobrir o modelo do seu Raspberry Pi, é executando

	cat /proc/cpuinfo | grep Revision

O campo 'Revision' indica qual é o modelo do seu Raspberry Pi:

	Raspberry Pi Model A: 0007, 0008, 0009
	Raspberry Pi Model B (Rev 1.0, 256Mb): 0002, 0003
	Raspberry Pi Model B (Rev 2.0, 256Mb): 0004, 0005, 0006
	Raspberry Pi Model B (Rev 2.0, 512Mb): 000d, 000e, 000f
	Raspberry Pi Model A+: 0012, 0015, 900021
	Raspberry Pi Model B+: 0010, 0013, 900032
	Raspberry Pi 2 Model B: a01040, a01041, a21041, a22042
	Raspberry Pi Zero: 900092, 900093, 920093
	Raspberry Pi Zero W: 9000c1
	Raspberry Pi 2 Model B: a02082, a22082, a32082

(Se o campo 'Revision' começar com os dígitos '10', ignore-os. Eles indicam que o seu Raspberry Pi sofreu over-clocking.)

4 - A partir do resultado anterior, execute

	sudo nano /boot/config.txt

para acrescentar o seguinte texto ao final deste arquivo:

	device_tree=bcm2708-rpi-b.dtb

De acordo com o modelo e o hardware do seu Raspberry Pi, troque o texto acima. Execute

	cd /boot
	ls *.dtb

para ver outras opções:

	bcm2708-rpi-0-w.dtb
	bcm2708-rpi-b.dtb
	bcm2708-rpi-b-plus.dtb
	bcm2708-rpi-cm.dtb
	bcm2709-rpi-2-b.dtb
	bcm2710-rpi-3-b.dtb
	bcm2710-rpi-cm3.dtb

5 - Execute

	sudo /sbin/reboot

para reiniciar o Raspberry Pi.

6 - Execute

	uname -a

para ver que o kernel foi alterado com o patch RT PREEMPT.

7 - Os códigos nesta pasta são baseados nos seguintes documentos:

	https://www.youtube.com/watch?v=uIXkvz1-weQ
	http://www.isy.liu.se/edu/kurs/TSEA81/lecture_linux_realtime.html
