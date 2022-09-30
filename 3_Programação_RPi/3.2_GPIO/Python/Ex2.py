import RPi.GPIO as gpio
import time

pin = 4
gpio.setmode(gpio.BCM)
gpio.setup(pin, gpio.OUT)
gpio.output(pin, gpio.HIGH)
time.sleep(5)
gpio.output(pin, gpio.LOW)
gpio.cleanup()
