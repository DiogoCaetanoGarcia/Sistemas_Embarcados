import time

def fatorial(n):
	if(n<2):
		return 1
	else:
		return n*fatorial(n-1)

N   = 10000
FAT = 20

t = [0,0]
t[0] = time.clock_gettime(time.CLOCK_MONOTONIC)
t[1] = t[0]
for i in range(N):
	f = fatorial(FAT)
t[1] = time.clock_gettime(time.CLOCK_MONOTONIC)
media = (t[1]-t[0])/N

print("Media de tempo de fatorial(%d) = %d\n"
	"   %2.2f ns" % (FAT,f,media*1.0e9))