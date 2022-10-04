from serial import Serial
from time import sleep
import struct

# Para RPi 0, 1 e 2
# TTY = "/dev/ttyAMA0"
# Para RPi 0W, 3 e 4
TTY = "/dev/ttyS0"

ser = Serial(TTY, 9600)
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
			if(ser.write(struct.pack('b',user_input))==1):
				sleep(int(1+user_input/2))
			else:
				print("Nao conseguiu mandar os dados.")
	print("")

ser.close()
