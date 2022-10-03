from spidev import SpiDev

spi = SpiDev()
spi.open(0,0)
spi.max_speed_hz = 500000

user_input = 1
while user_input!=0:
	print("Digite um numero entre 1 e 5 para mandar")
	print("o microcontrolador piscar seus LEDs,")
	print("ou digite 0 para terminar o programa. ")
	user_input = input()
	if((user_input<0) or (user_input>5)):
		print("Valor invalido")
	else if(user_input>0):
		spi.xfer([user_input])
		sleep(1+user_input/2)
	print("")

spi.close()