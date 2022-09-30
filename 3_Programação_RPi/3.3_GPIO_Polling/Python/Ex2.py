import RPi.GPIO as gpio
import os, select

pin = 4
os.system("echo %d      > /sys/class/gpio/export" % pin)
os.system("echo falling > /sys/class/gpio/gpio%d/edge" % pin)
os.system("echo in      > /sys/class/gpio/gpio%d/direction" % pin)

fd = os.open("/sys/class/gpio/gpio%d/value" % pin, os.O_RDONLY)
os.read(fd, 1)
pfd = select.poll()
pfd.register(fd, select.POLLPRI | select.POLLERR)

print("Pressione o botao...")
ret = pfd.poll()
if ret[0][1] & select.POLLPRI:
	print("POLLPRI detectado")
if ret[0][1] & select.POLLERR:
	print("POLLERR detectado")
print("Borda de descida!")
os.close(fd)
os.system("echo %d > /sys/class/gpio/unexport" % pin)
