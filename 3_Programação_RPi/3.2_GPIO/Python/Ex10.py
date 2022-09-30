import RPi.GPIO as gpio
import time
import signal

def fim(signum, frame):
	gpio.cleanup()

pin = 4
signal.signal(signal.SIGINT, fim)

print("Digite a frequência desejada: ", end="")
freq = float(input())
print("freq=%f" % freq)

if freq<=0.0:
	print("Frequência de %f Hz inválida!" % freq)
	exit(-1)
print("Digite o ciclo de trabalho desejado (0-100): ", end="")
duty_cyc = float(input())
if (duty_cyc<0.0) or (duty_cyc>100.0):
	print("Ciclo de trabalho de %f %% inválido!" % duty_cyc)
	exit(-1)

periodo = 1/freq
periodo_alto = periodo*duty_cyc/100
periodo_baixo = periodo - periodo_alto

gpio.setmode(gpio.BCM)
gpio.setup(pin, gpio.OUT)
while True:
	gpio.output(pin, gpio.HIGH)
	time.sleep(periodo_alto)
	gpio.output(pin, gpio.LOW)
	time.sleep(periodo_baixo)
