import time

N = 150
DELAY_US = 10000
DELAY_S  = DELAY_US*1e-6

CPU_time = [0,0]
CPU_time[0] = time.process_time()
for i in range(N):
	time.sleep(DELAY_S)
CPU_time[1] = time.process_time()
media = (CPU_time[1]-CPU_time[0])/N

print("Cálculo de tempo usando time.process_time():")
print("N = %d" % N)
print("Media de tempo de sleep(%f)\n"
	"   %2.1f us\n" % (DELAY_S, media*1.0e6))
print("time.process_time() retorna a quantidade")
print("   de ciclos de clock consumidos")
print("   PELO PROCESSO ATUAL.")
print("A chamada time.sleep(%f) não é contabilizada.\n" % DELAY_S)

CPU_time[0] = time.thread_time()
for i in range(N):
	time.sleep(DELAY_S)
CPU_time[1] = time.thread_time()
media = (CPU_time[1]-CPU_time[0])/N

print("Cálculo de tempo usando time.thread_time():")
print("N = %d" % N)
print("Media de tempo de sleep(%f)\n"
	"   %2.1f us\n" % (DELAY_S, media*1.0e6))
print("time.thread_time() retorna a quantidade")
print("   de ciclos de clock consumidos")
print("   PELA THREAD ATUAL.")
print("A chamada time.sleep(%f) não é contabilizada." % DELAY_S)