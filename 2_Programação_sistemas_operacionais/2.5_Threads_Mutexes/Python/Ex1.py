import threading, time

def print_xs(c):
	for i in range(10):
		print(c, end="")

t1 = threading.Thread(target=print_xs, args = ("A"))
t2 = threading.Thread(target=print_xs, args = ("B"))
t1.start()
t2.start()

for i in range(10):
	print('-', end="")

print()