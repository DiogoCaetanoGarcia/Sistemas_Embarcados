import time

N = 150000000
time_1 = time.time()
for i in range(N):
	pass
time_2 = time.time()
print("Tempo de execução do laço 'for': %4.1f s" % (time_2-time_1))