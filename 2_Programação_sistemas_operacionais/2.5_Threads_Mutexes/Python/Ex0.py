import threading, time

def print_1():
	for i in range(10):
		print('1', end="")
		time.sleep(0.05)

def print_2():
	for i in range(10):
		print('2', end="")
		time.sleep(0.05)

t1 = threading.Thread(target=print_1)
t2 = threading.Thread(target=print_2)
t1.start()
t2.start()

for i in range(10):
	print('-', end="")
	time.sleep(0.05)

print()