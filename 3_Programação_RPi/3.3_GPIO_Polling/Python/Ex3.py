import RPi.GPIO as gpio
import os, select

pin = 4
os.system("echo %d      > /sys/class/gpio/export" % pin)
os.system("echo falling > /sys/class/gpio/gpio%d/edge" % pin)
os.system("echo in      > /sys/class/gpio/gpio%d/direction" % pin)

fd = os.open("/sys/class/gpio/gpio%d/value" % pin, os.O_RDONLY)
pfd = select.poll()
pfd.register(fd, select.POLLPRI | select.POLLERR)

print("Pressione o botao...")
for btn_press in range(5):
	os.lseek(fd, 0, os.SEEK_SET)
	os.read(fd, 1)
	pfd.poll()
	print("Borda de descida!")

os.close(fd)
os.system("echo %d > /sys/class/gpio/unexport" % pin)
