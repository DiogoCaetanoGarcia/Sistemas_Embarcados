import os, time

def func(x, y, z):
	print("PID = %d, x=%d, y=%d e z=%d" %
		(os.getpid(), x, y, z))

a = 1
b = 2
c = 3
func(a, b, c)

pid_filho = os.fork()
if(pid_filho == 0):
	a=7
	b=8
	c=9
	func(a, b, c)
else:
	time.sleep(1)
	func(a, b, c)