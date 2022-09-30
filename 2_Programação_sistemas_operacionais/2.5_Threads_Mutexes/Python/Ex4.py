import threading, time

varCompartilhada = 0

def incrementa_contador():
	global varCompartilhada
	for i in range(1000000):
		varCompartilhada += 1

def decrementa_contador():
	global varCompartilhada
	for i in range(1000000):
		varCompartilhada -= 1

print("Valor inicial: %d" % varCompartilhada)

t1 = threading.Thread(target=incrementa_contador)
t2 = threading.Thread(target=decrementa_contador)
t1.start()
t2.start()
t1.join()
t2.join()

print("Valor final:   %d" % varCompartilhada)