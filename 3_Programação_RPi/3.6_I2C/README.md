# Questões

1. Considere o caso em que a Raspberry Pi deve receber leituras analógico/digitais de um MSP430, que a comunicação entre os dois é I2C, e que o MSP430 é o escravo. É tecnicamente possível que o MSP430 mande os resultados da conversão A/D a qualquer hora, ou ele deve aguardar a Raspberry Pi fazer um pedido ao MSP430? Por quê?
2. Se o Raspberry Pi tiver de se comunicar com dois dispositivos via I2C, como executar a comunicação com o segundo dispositivo?
3. Considere um MSP430 sendo usado para leituras analógicas. O Raspberry Pi está conectado a ele via I2C, e é o mestre. O MSP430 foi programado para funcionar da seguinte forma:

- O MSP430 recebe o byte 0x55, o que indica o começo de conversão.
- 100us depois, o MSP430 envia o byte menos significativo e o mais significativo da conversão de 10 bits, nesta ordem.

Escreva o código para o Raspberry Pi executar este protocolo, de forma a obter conversões a cada 10 ms. A cada 1 segundo ele deve apresentar no terminal a média das últimas 100 amostras.

Utilize o [seguinte código](https://github.com/DiogoCaetanoGarcia/Sistemas_Embarcados/blob/master/3_Programa%C3%A7%C3%A3o_RPi/3.7_Revis%C3%A3o/MSP430_AD/MSP430_AD_I2C.c) para o MSP430 seguir este protocolo, ou [este código](https://github.com/DiogoCaetanoGarcia/Sistemas_Embarcados/blob/master/3_Programa%C3%A7%C3%A3o_RPi/3.7_Revis%C3%A3o/Arduino_AD_I2C/Arduino_AD_I2C.ino) para o Arduino seguir este protocolo. Se for usar o Arduino, utilize o [circuito a seguir](https://github.com/DiogoCaetanoGarcia/Sistemas_Embarcados/blob/master/3_Programa%C3%A7%C3%A3o_RPi/3.7_Revis%C3%A3o/Arduino_AD_I2C/Conexoes_RPi_Arduino_Nano.png). pois o Arduino trabalha com 5 V. O MSP430 e o Arduino utilizam o endereço 0x0F.
