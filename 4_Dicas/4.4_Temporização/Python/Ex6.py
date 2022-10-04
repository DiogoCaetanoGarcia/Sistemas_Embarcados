import time

N = 150
DELAY_US = 10000
DELAY_S  = DELAY_US*1e-6

CPU_time = [0,0]
CPU_time[0] = time.clock_gettime(time.CLOCK_MONOTONIC)
for i in range(N):
	time.sleep(DELAY_S)
CPU_time[1] = time.clock_gettime(time.CLOCK_MONOTONIC)
media = (CPU_time[1]-CPU_time[0])/N

print("Media de tempo de time.sleep(%f)\n"
	"   N =  %d, %2.1f us" % (DELAY_S, N, media*1.0e6))