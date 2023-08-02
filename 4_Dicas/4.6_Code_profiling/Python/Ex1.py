import math, sys

N = 1000000

x = []
y = []
for i in range(N):
	x.append(1000//((i+1)&(2**32-1)))
	y.append(1000//((3*i*i+5*i+1)&(2**32-1)))

media_x = 0
for i in range(N):
	media_x += x[i]/N

media_y = 0
for i in range(N):
	media_y += y[i]/N

dist_eucl = 0
for i in range(N):
	dist_eucl += (x[i]-y[i])**2
dist_eucl = math.sqrt(dist_eucl)

print("Resultado %s:" % sys.argv[0])
print("   Media(x) = %1.10f" % media_x)
print("   Media(y) = %1.10f" % media_y)
print("   Dist_euclidiana(x,y) = %3.10f" % dist_eucl)
