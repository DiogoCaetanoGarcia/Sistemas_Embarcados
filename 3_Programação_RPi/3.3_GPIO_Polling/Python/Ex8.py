import RPi.GPIO as gpio
import time

i_global = 0

def interrupcao(c):
	global i_global
	print("Botao pressionado, i_global = %d" % i_global)
	i_global += 1


pin = 4
gpio.setmode(gpio.BCM)
gpio.setup(pin, gpio.IN)
gpio.add_event_detect(pin, gpio.FALLING, callback=interrupcao, bouncetime=300)
print("Pressione o botao")
while i_global<15:
	time.sleep(1);
	print("Loop principal, i_global = %d" % i_global)
gpio.cleanup()
