from spidev import SpiDev
from time import sleep

spi = SpiDev()
spi.open(0,0)
spi.max_speed_hz = 500000

user_input = 1
while user_input!=0:
	print("Digite um numero entre 1 e 5 para mandar")
	print("o microcontrolador piscar seus LEDs,")
	print("ou digite 0 para terminar o programa. ")
	user_input = int(input())
	if((user_input<0) or (user_input>5)):
		print("Valor invalido")
	else:
		if(user_input>0):
			send_microcontroller = [user_input]
			spi.xfer(send_microcontroller)
			sleep(int(1+user_input/2))
			print("Retorno do microcontrolador = %d" % send_microcontroller[0])
	print("")

spi.close()
