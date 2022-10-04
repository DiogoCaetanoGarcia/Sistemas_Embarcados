from serial import Serial
from time import sleep
import struct

# Para RPi 0, 1 e 2
# TTY = "/dev/ttyAMA0"
# Para RPi 0W, 3 e 4
TTY = "/dev/ttyS0"

ser = Serial(TTY, 9600)
ser.flush()
microcontroller_input = 1
while microcontroller_input != 5:
	microcontroller_input = ser.read(1)[0]
	serial_status = ser.in_waiting
	print("Retorno do microcontrolador = %d" % microcontroller_input)
	print("%d bytes disponíveis" % serial_status)

ser.close()
