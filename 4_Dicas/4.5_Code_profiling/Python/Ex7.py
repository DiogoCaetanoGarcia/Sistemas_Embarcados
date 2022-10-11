import math, sys, time

N = 1000000

t = [None]*6
t[0] = time.time()
x = [1000//((i+1)&(2**32-1)) for i in range(N)]
t[1] = time.time()
y = [1000//((3*i*i+5*i+1)&(2**32-1)) for i in range(N)]
t[2] = time.time()
media_x = sum(x)/N
t[3] = time.time()
media_y = sum(y)/N
t[4] = time.time()
dist_eucl = math.sqrt(sum([(x[i]-y[i])**2 for i in range(N)]))
t[5] = time.time()

print("Resultado %s:" % sys.argv[0])
print("   Media(x) = %1.10f" % media_x)
print("   Media(y) = %1.10f" % media_y)
print("   Dist_euclidiana(x,y) = %3.10f\n" % dist_eucl)
print("Diferenças de tempos:\n   %f %f %f %f %f" %
	(t[1]-t[0],t[2]-t[1],t[3]-t[2],t[4]-t[3],t[5]-t[4]))