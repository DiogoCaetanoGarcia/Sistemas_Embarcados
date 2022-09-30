import threading, time

cancel = False

def thread_function():
	global cancel
	print("Nova thread")
	for i in range(10,0,-1):
		if cancel:
			return
		print("Faltam %2d segundos para acabar a thread ..." % i)
		time.sleep(1)

print("Criando a thread")
t = threading.Thread(target=thread_function)
t.start()
time.sleep(5)
print("Cancelando a thread")
cancel = True
print("Thread cancelada!")