1. Crie dois processos, e faça com que o processo-filho gere uma onda quadrada, enquanto o processo-pai lê um botão no GPIO, aumentando a frequência da onda sempre que o botão for pressionado. A frequência da onda quadrada deve começar em 1 Hz, e dobrar cada vez que o botão for pressionado. A frequência máxima é de 64 Hz, devendo retornar a 1 Hz se o botão for pressionado novamente.

2. Crie dois processos, e faça com que o processo-filho gere uma onda quadrada, enquanto o processo-pai faz polling de um botão no GPIO, aumentando a frequência da onda sempre que o botão for pressionado. A frequência da onda quadrada deve começar em 1 Hz, e dobrar cada vez que o botão for pressionado. A frequência máxima é de 64 Hz, devendo retornar a 1 Hz se o botão for pressionado novamente.

3. Considere um MSP430 sendo usado para leituras analógicas. O Raspberry Pi está conectado a ele via UART. O MSP430 foi programado para converter e enviar dados de 10 bits a cada 10 ms. Escreva o código para o Raspberry Pi receber estes dados, e a cada 1 segundo apresentar no terminal a média das últimas 100 amostras.

Utilize o [seguinte código](https://github.com/DiogoCaetanoGarcia/Sistemas_Embarcados/blob/master/3_Programa%C3%A7%C3%A3o_RPi/3.7_Revis%C3%A3o/MSP430_AD/MSP430_AD_UART.c) para o MSP430 seguir este protocolo, ou [este código](https://github.com/DiogoCaetanoGarcia/Sistemas_Embarcados/blob/master/3_Programa%C3%A7%C3%A3o_RPi/3.7_Revis%C3%A3o/Arduino_AD_UART/Arduino_AD_UART.ino) para o Arduino seguir este protocolo. Se for usar o Arduino, utilize um [divisor de tensão](https://github.com/DiogoCaetanoGarcia/Sistemas_Embarcados/blob/master/3_Programa%C3%A7%C3%A3o_RPi/3.7_Revis%C3%A3o/Arduino_AD_UART/Conexoes_RPi_Arduino_Nano.png) no pino de transmissão UART do mesmo, que trabalha com 5 V.

4. Considere um MSP430 sendo usado para leituras analógicas. O Raspberry Pi está conectado a ele via SPI, e é o mestre. O MSP430 foi programado para funcionar da seguinte forma:

- O MSP430 recebe o byte 0x55  e envia o byte 0xAA, o que indica o começo de conversão.
- 100us depois, o MSP430 recebe os bytes 0x01 e 0x02 , e envia o byte menos significativo e o mais significativo da conversão de 10 bits, nesta ordem.

Escreva o código para o Raspberry Pi executar este protocolo, de forma a obter conversões a cada 10 ms. A cada 1 segundo ele deve apresentar no terminal a média das últimas 100 amostras.

Utilize o [seguinte código](https://github.com/DiogoCaetanoGarcia/Sistemas_Embarcados/blob/master/3_Programa%C3%A7%C3%A3o_RPi/3.7_Revis%C3%A3o/MSP430_AD/MSP430_AD_SPI.c) para o MSP430 seguir este protocolo, ou [este código](https://github.com/DiogoCaetanoGarcia/Sistemas_Embarcados/blob/master/3_Programa%C3%A7%C3%A3o_RPi/3.7_Revis%C3%A3o/Arduino_AD_SPI/Arduino_AD_SPI.ino) para o Arduino seguir este protocolo. Se for usar o Arduino, utilize um [divisor de tensão](https://github.com/DiogoCaetanoGarcia/Sistemas_Embarcados/blob/master/3_Programa%C3%A7%C3%A3o_RPi/3.7_Revis%C3%A3o/Arduino_AD_SPI/Conexoes_RPi_Arduino_Nano.png) no pino MISO do mesmo, que trabalha com 5 V.

5. Considere um MSP430 sendo usado para leituras analógicas. O Raspberry Pi está conectado a ele via I2C, e é o mestre. O MSP430 foi programado para funcionar da seguinte forma:

- O MSP430 recebe o byte 0x55, o que indica o começo de conversão.
- 100us depois, o MSP430 envia o byte menos significativo e o mais significativo da conversão de 10 bits, nesta ordem.

Escreva o código para o Raspberry Pi executar este protocolo, de forma a obter conversões a cada 10 ms. A cada 1 segundo ele deve apresentar no terminal a média das últimas 100 amostras.

Utilize o [seguinte código](https://github.com/DiogoCaetanoGarcia/Sistemas_Embarcados/blob/master/3_Programa%C3%A7%C3%A3o_RPi/3.7_Revis%C3%A3o/MSP430_AD/MSP430_AD_I2C.c) para o MSP430 seguir este protocolo, ou [este código](https://github.com/DiogoCaetanoGarcia/Sistemas_Embarcados/blob/master/3_Programa%C3%A7%C3%A3o_RPi/3.7_Revis%C3%A3o/Arduino_AD_I2C/Arduino_AD_I2C.ino) para o Arduino seguir este protocolo. Se for usar o Arduino, utilize o [circuito a seguir](https://github.com/DiogoCaetanoGarcia/Sistemas_Embarcados/blob/master/3_Programa%C3%A7%C3%A3o_RPi/3.7_Revis%C3%A3o/Arduino_AD_I2C/Conexoes_RPi_Arduino_Nano.png), pois o Arduino trabalha com 5 V. O MSP430 e o Arduino utilizam o endereço 0x0F.