import RPi.GPIO as gpio

pin = 4
gpio.setmode(gpio.BCM)
gpio.setup(pin, gpio.IN)
print("Pressione o botão")
while gpio.input(pin) > 0:
	pass
GPIO.cleanup()
