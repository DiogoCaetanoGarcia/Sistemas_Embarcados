# Questões

1. Considere o caso em que a Raspberry Pi deve receber leituras analógico/digitais de um MSP430, que a comunicação entre os dois seja SPI, e que o MSP430 seja o escravo. É tecnicamente possível que o MSP430 mande os resultados da conversão A/D a qualquer hora, ou ele deve aguardar a Raspberry Pi fazer um pedido ao MSP430? Por quê?
2. Se o Raspberry Pi tiver de se comunicar com dois dispositivos via SPI, como executar a comunicação com o segundo dispositivo?
3. Considere um MSP430 sendo usado para leituras analógicas. O Raspberry Pi está conectado a ele via SPI, e é o mestre. O MSP430 foi programado para funcionar da seguinte forma:

- O MSP430 recebe o byte 0x55  e envia o byte 0xAA, o que indica o começo de conversão.
- 100us depois, o MSP430 recebe os bytes 0x01 e 0x02 , e envia o byte menos significativo e o mais significativo da conversão de 10 bits, nesta ordem.

Escreva o código para o Raspberry Pi executar este protocolo, de forma a obter conversões a cada 10 ms. A cada 1 segundo ele deve apresentar no terminal a média das últimas 100 amostras.

Utilize o [seguinte código](https://github.com/DiogoCaetanoGarcia/Sistemas_Embarcados/blob/master/3_Programa%C3%A7%C3%A3o_RPi/3.7_Revis%C3%A3o/MSP430_AD/MSP430_AD_SPI.c) para o MSP430 seguir este protocolo, ou [este código](https://github.com/DiogoCaetanoGarcia/Sistemas_Embarcados/blob/master/3_Programa%C3%A7%C3%A3o_RPi/3.7_Revis%C3%A3o/Arduino_AD_SPI/Arduino_AD_SPI.ino) para o Arduino seguir este protocolo. Se for usar o Arduino, utilize um [divisor de tensão](https://github.com/DiogoCaetanoGarcia/Sistemas_Embarcados/blob/master/3_Programa%C3%A7%C3%A3o_RPi/3.7_Revis%C3%A3o/Arduino_AD_SPI/Conexoes_RPi_Arduino_Nano.png) no pino MISO do mesmo, que trabalha com 5 V.
