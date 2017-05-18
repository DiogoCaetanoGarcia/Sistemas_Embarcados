O Raspbian não tem a comunicação SPI habilitada inicialmente. Para utiliza-la, você deve habilita-la da seguinte maneira:

1 - Execute

	$ sudo raspi-config

vá em Advanced options -> SPI, e habilite o acesso:

	Would you like the SPI interface to be enabled? Yes.

2 - Reinicie (reboot) o sistema para tornar esta mudança efetiva.

3 - Execute

	$ cat /boot/config.txt | grep spi

Deverá aparecer o texto

	dtparam=spi=on

indicando que a SPI está habilitada.
