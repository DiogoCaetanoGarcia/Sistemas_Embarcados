Data: 18/05/2017

1. Controle 6 LEDs de uma árvore de natal utilizando charlieplexing, de forma que um ser humano veja todos acesos ao mesmo tempo. Pisque os LEDs numa frequência de 100 Hz.

2. Controle 6 LEDs de uma árvore de natal utilizando charlieplexing. Pisque os LEDs numa frequência de 100 Hz. Acenda os LEDs de forma que um ser humano veja dois LEDs acesos juntos por um tempo, depois outros dois LEDs, e depois os últimos 2 LEDs juntos. Permaneça em cada estado durante 0,5 segundos.

3. Multiplexe 2 displays de 7 segmentos para apresentar a seguinte sequência em loop:

	01 - 12 - 23 - 34 - 45 - 56 - 67 - 78 - 89 - 9A - AB - BC - CD - DE - EF - F0

Pisque os LEDs numa frequência de 100 Hz.

4. Implemente a comunicação UART em um pino GPIO, usando um bit de START (padrão), oito bits de dados na ordem MSB->LSB e um bit de STOP.

	(a) Escreva a seguinte função em C para configurar pinos GPIO para transmissão e recepção:

		void Config_UART(unsigned char TX_pin, unsigned char RX_pin);

	onde 'TX_pin' e 'RX_pin' são os valores dos pinos GPIO na Raspberry Pi.

	(b) Escreva a seguinte função em C para imitar a transmissão UART em um pino GPIO da Raspberry Pi:

		void Transmit_UART(unsigned char data_out, unsigned char TX_pin, unsigned char baud_rate);

	onde 'data_out' é o byte a ser enviado, 'TX_pin' é o valor do pino GPIO de transmissão, e 'baud_rate' é a taxa de transmissão UART, em amostras por segundo.

	(c) Escreva a seguinte função em C para imitar a recepção UART em um pino GPIO da Raspberry Pi:

		unsigned char Receive_UART(unsigned char RX_pin, unsigned char baud_rate);

	onde 'RX_pin' é o valor do pino GPIO de recepção, e 'baud_rate' é a taxa de recepção UART, em amostras por segundo. A função retorna o byte lido.

	(d) Escreva a seguinte função em C para liberar os pinos GPIO de transmissão e recepção:

		void Release_UART(unsigned char TX_pin, unsigned char RX_pin);

5. Considere dois MSP430, onde um deles faz leituras AD em 8 canais, e o outro escreve em 4 displays de 7 segmentos. Ambos estão conectados ao Raspberry Pi pelas portas I2C, e seus respectivos endereços são 0x20 e 0x51, respectivamente.

	(a) Escreva a função em C para configurar a comunicação I2C no Raspberry Pi.

		void Config_I2C(void);

	(b) Escreva a função em C para ler uma conversão AD de 10 bits do MSP430 de um dos oito canais. O Raspberry Pi manda o número do canal para o MSP430, aguarda 100us, e lê os bytes menos e mais significativos da conversão, nessa ordem.

		unsigned int AD_read_I2C(char channel);

	(c) Escreva a função em C para escrever nos displays a leitura atual de tensão. Considere que o MSP430 mede tensões entre 0 e 3 V, e que o conversor AD é de 10 bits.

		void Write_4_7seg_I2C(unsigned int value);

	O MSP430 deverá receber a casas decimais do valor, da casa mais significativa para a menos significativa. Por exemplo, se value=1023, a Raspberry Pi deverá transmitir o vetor {3,0,0,0}.

6. Considere dois MSP430, onde um deles faz leituras AD em 8 canais, e o outro escreve em 4 displays de 7 segmentos. Ambos estão conectados ao Raspberry Pi pelas portas SPI.

	(a) Escreva a função em C para configurar a comunicação SPI no Raspberry Pi:

		void Config_SPI(void);

	(b) Escreva a função em C para ler uma conversão AD de 10 bits do MSP430 de um dos oito canais. O Raspberry Pi manda o número do canal para o MSP430, aguarda 100us, e lê os bytes menos e mais significativos da conversão, nessa ordem.

		unsigned int AD_read_SPI(char channel);

	(c) Escreva a função em C para escrever nos displays a leitura atual de tensão. Considere que o MSP430 mede tensões entre 0 e 3 V, e que o conversor AD é de 10 bits.

		void Write_4_7seg_SPI(unsigned int value);

	O MSP430 deverá receber a casas decimais do valor, da casa mais significativa para a menos significativa. Por exemplo, se value=1023, a Raspberry Pi deverá transmitir o vetor {3,0,0,0}.












