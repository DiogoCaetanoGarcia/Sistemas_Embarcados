import time

N = 1500000
time_1 = time.time()
for i in range(N):
	pass
time_2 = time.time()
print("Tempo de execução do laço 'for': %f s" % (time_2-time_1))