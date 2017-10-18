O Raspbian não tem a comunicação I2C habilitada inicialmente. Para utiliza-la, você deve habilita-la da seguinte maneira:

1 - Execute

	$ sudo raspi-config

vá em Advanced options -> I2C, e habilite o acesso:

	Would you like the ARM I2C interface to be enabled? Yes.

2 - Reinicie (reboot) o sistema para tornar esta mudança efetiva.

3 - Execute

	$ cat /boot/config.txt | grep i2c

Deverá aparecer o texto

	dtparam=i2c_arm=on

indicando que a I2C está habilitada.

4 - Execute

	sudo apt-get install -y i2c-tools

para obter ferramentas de teste e configuração da comunicação I2C pelo terminal. Depois de instaladas, execute

	i2cdetect -y 1

para enxergar o endereço de todos os dispositivos I2C conectados. (O código nesta pasta para o MSP430 o configura com endereço 0xF.)

5 - Para mudar a taxa de transmissão I2C para 50000 Hz, por exemplo, deve-se acrescentar a seguinte linha ao arquivo /boot/config.txt:

	dtparam=i2c_baudrate=50000

A mudança só será efetivada depois do reboot.

6 - É necessário conectar resistores de pullup nas duas linhas, SCL (clock) e SDA (dados). A comunicação I2C requer estes resistores porque as linhas são conectadas na configuração coletor aberto (https://learn.sparkfun.com/tutorials/i2c/i2c-at-the-hardware-level):


```
                        Vcc
                        ---
                         |
                         /
                         \  Resistor de pullup
                         /
                         |
                         *-------  Linha I2C (SDA, por exemplo)
                         |
                         /
                       |/
Driver interno ao  o---|
dispositivo I2C        |\
                         \|
                          T
                          |
                        -----
                         ---
                          -
```

Nesta configuração, qualquer dispositivo, mestre ou escravo, consegue levar a linha para 0 (GND) a qualquer momento, e qualquer dispositivo só consegue levar a linha para 1 (Vcc) se nenhum outro dispositivo "segurar" a linha em 0.

7 - As linhas SCL e SDA possuem uma capacitância intrínseca, o que afeta a escolha dos resistores de pullup. Quanto maior o resistor de pullup, maior o tempo para levar as linhas de 0 para 1, afetando a performance do sistema. Quanto mais comprida a conexão física da linha, maior a capacitância. Geralmente, escolhem-se resistores menores do que 10000 ohms.

Se os valores escolhidos para os resistores não estiverem adequados, utilize as seguintes referências para calcula-los:

	http://www.ti.com/lit/an/slva689/slva689.pdf
	http://dsscircuits.com/articles/effects-of-varying-i2c-pull-up-resistors
