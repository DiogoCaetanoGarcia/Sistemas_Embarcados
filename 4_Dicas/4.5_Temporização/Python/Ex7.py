import time

N = 150
DELAY_US = 10000
DELAY_S  = DELAY_US*1e-6

t = [0,0]
t[0] = time.clock_gettime(time.CLOCK_MONOTONIC)
t[1] = t[0]
for i in range(N):
	t[1] += DELAY_S
	while t[1]>time.clock_gettime(time.CLOCK_MONOTONIC):
		pass
t[1] = time.clock_gettime(time.CLOCK_MONOTONIC)
media = (t[1]-t[0])/N

print("Media de tempo de usando time.clock_gettime()\n"
	"   N =  %d, %2.2f us" % (N, media*1.0e6))