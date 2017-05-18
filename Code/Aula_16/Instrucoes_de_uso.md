O Raspbian utiliza a porta serial assíncrona (UART) para acesso remoto ao terminal (bash):

	http://elinux.org/RPi_Serial_Connection#Connection_to_a_microcontroller_or_other_peripheral

Para utilizar a UART para outros propósitos, você deve desabilitar este acesso remoto, da seguinte maneira:

1 - Execute

	$ sudo raspi-config

vá em Advanced options -> Serial, e desabilite o acesso:

	Would you like a login shell to be accessible over serial? No.

Quando sair deste programa, não o deixe dar reiniciar (reboot) o sistema.

2 - Execute

	$ sudo cat /boot/config.txt

e verifique se este arquivo contém a seguinte linha:

	enable_uart=1

Se o arquivo conter a linha

	enable_uart=0

abra o arquivo:

	$ sudo nano /boot/config.txt

e troque "enable_uart=0" por "enable_uart=1".

3 - Reinicie o Raspberry Pi:

	$ sudo reboot

4 - Se você estiver usando o Raspberry Pi 3, o arquivo de acesso à porta serial não é "/dev/ttyAMA0", e sim "/dev/ttyS0", pois "/dev/ttyAMA0" é a porta serial usada para comunicar com o módulo Bluetooth da placa. Assim, em todos os exemplos desta aula, troque as definições

	#define TTY /dev/ttyAMA0

por

	#define TTY /dev/ttyS0
