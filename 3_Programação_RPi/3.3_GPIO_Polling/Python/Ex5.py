import RPi.GPIO as gpio
import os, select, time

def poll_btn(pfd, fd):
	N = 50
	Nlim = N/2
	os.lseek(fd, 0, os.SEEK_SET)
	buf = int(os.read(fd, 1))
	vals = [buf]*N
	pfd.poll()
	test=True
	pos = 0
	while test:
		os.lseek(fd, 0, os.SEEK_SET)
		vals[pos] = int(os.read(fd, 1))
		pos = (pos+1) % N
		s = sum(vals)
		if buf==0:
			test = s<Nlim
		else:
			test = s>Nlim


pin = 4
os.system("echo %d      > /sys/class/gpio/export" % pin)
os.system("echo falling > /sys/class/gpio/gpio%d/edge" % pin)
os.system("echo in      > /sys/class/gpio/gpio%d/direction" % pin)

fd = os.open("/sys/class/gpio/gpio%d/value" % pin, os.O_RDONLY)
pfd = select.poll()
pfd.register(fd, select.POLLPRI | select.POLLERR)

print("Pressione o botao...")
for btn_press in range(5):
	poll_btn(pfd, fd)
	print("Borda de descida!")
	poll_btn(pfd, fd)
	print("Borda de subida!")

os.close(fd)
os.system("echo %d > /sys/class/gpio/unexport" % pin)
