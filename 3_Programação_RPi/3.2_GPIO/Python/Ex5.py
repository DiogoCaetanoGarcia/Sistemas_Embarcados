import RPi.GPIO as gpio

i = 0
pin = 4
gpio.setmode(gpio.BCM)
gpio.setup(pin, gpio.IN)
while i<15:
	print("i = %d" % i)
	print("Pressione o botão")
	while gpio.input(pin) > 0:
		pass
	print("Botão pressionado")
	while gpio.input(pin) == 0:
		pass
	print("Botão solto")
	i += 1
gpio.cleanup()
