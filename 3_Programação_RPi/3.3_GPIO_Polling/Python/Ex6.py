import RPi.GPIO as gpio
import os, select, time

pins = [4, 17]
os.system("echo %d      > /sys/class/gpio/export" % pins[0])
os.system("echo falling > /sys/class/gpio/gpio%d/edge" % pins[0])
os.system("echo in      > /sys/class/gpio/gpio%d/direction" % pins[0])
os.system("echo %d      > /sys/class/gpio/export" % pins[1])
os.system("echo falling > /sys/class/gpio/gpio%d/edge" % pins[1])
os.system("echo in      > /sys/class/gpio/gpio%d/direction" % pins[1])

fds = [0,0]
fds[0] = os.open("/sys/class/gpio/gpio%d/value" % pins[0], os.O_RDONLY)
fds[1] = os.open("/sys/class/gpio/gpio%d/value" % pins[1], os.O_RDONLY)

pfd = select.poll()
pfd.register(fds[0], select.POLLPRI | select.POLLERR)
pfd.register(fds[1], select.POLLPRI | select.POLLERR)

print("Pressione o botao...")
for btn_press in range(5):
	os.lseek(fds[0], 0, os.SEEK_SET)
	os.read(fds[0], 1)
	os.lseek(fds[1], 0, os.SEEK_SET)
	os.read(fds[1], 1)
	ret = pfd.poll()
	for r in ret:
		if (r[0] == fds[0]) and (r[1] & (select.POLLPRI | select.POLLERR)):
			print("Borda de descida em GPIO%d!" % pins[0])
		if (r[0] == fds[1]) and (r[1] & (select.POLLPRI | select.POLLERR)):
			print("Borda de descida em GPIO%d!" % pins[1])
	time.sleep(0.3)

os.close(fds[0])
os.system("echo %d > /sys/class/gpio/unexport" % pins[0])
os.close(fds[1])
os.system("echo %d > /sys/class/gpio/unexport" % pins[1])
