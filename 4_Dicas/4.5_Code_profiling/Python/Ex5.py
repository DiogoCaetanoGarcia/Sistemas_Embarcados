import math, sys

N = 1000000

x = [1000//((i+1)&(2**32-1)) for i in range(N)]
y = [1000//((3*i*i+5*i+1)&(2**32-1)) for i in range(N)]

media_x = sum(x)/N
media_y = sum(y)/N
dist_eucl = math.sqrt(sum([(x[i]-y[i])**2 for i in range(N)]))

print("Resultado %s:" % sys.argv[0])
print("   Media(x) = %1.10f" % media_x)
print("   Media(y) = %1.10f" % media_y)
print("   Dist_euclidiana(x,y) = %3.10f\n" % dist_eucl)
