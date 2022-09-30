import threading, time

retorno = 0
def thread_function():
	global retorno
	print("Nova thread")
	for i in range(10,0,-1):
		print("Faltam %2d segundos para acabar a thread ..." % i)
		time.sleep(1)
	retorno = 0

print("Criando a thread")
t = threading.Thread(target=thread_function)
t.start()
t.join()
j = retorno
print("j = %d" % j)