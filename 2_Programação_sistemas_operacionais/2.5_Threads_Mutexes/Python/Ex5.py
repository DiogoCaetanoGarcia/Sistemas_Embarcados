import threading, time

varCompartilhada = 0
l = threading.Lock()

def incrementa_contador():
	global varCompartilhada
	for i in range(1000000):
		l.acquire()
		varCompartilhada += 1
		l.release()

def decrementa_contador():
	global varCompartilhada
	for i in range(1000000):
		l.acquire()
		varCompartilhada -= 1
		l.release()

print("Valor inicial: %d" % varCompartilhada)

t1 = threading.Thread(target=incrementa_contador)
t2 = threading.Thread(target=decrementa_contador)
t1.start()
t2.start()
t1.join()
t2.join()

print("Valor final:   %d" % varCompartilhada)