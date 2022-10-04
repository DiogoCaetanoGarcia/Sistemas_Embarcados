import smbus2
from time import sleep

canal = 1
endereco = 15
i2c = smbus2.SMBus(canal)

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
			i2c.write_byte(endereco, user_input)
			sleep(int(1+user_input/2))
			microcontroller_ret = i2c.read_byte(endereco, 1)
			print("Retorno do microcontrolador = %d" % microcontroller_ret)
	print("")

i2c.close()
