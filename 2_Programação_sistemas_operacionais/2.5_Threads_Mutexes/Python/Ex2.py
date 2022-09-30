import threading, time

def char_print(c, n):
	for i in range(n):
		print(c, end="")
		time.sleep(0.003)

t1 = threading.Thread(target=char_print, args = ("x",100))
t2 = threading.Thread(target=char_print, args = ("o",80))
t1.start()
t2.start()

print("\nTerminando a execucao da thread principal.")
