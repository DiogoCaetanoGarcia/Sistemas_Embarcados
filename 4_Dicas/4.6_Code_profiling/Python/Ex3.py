import cProfile, math, sys

def preencher_vetores(N):
	a = [None]*N
	b = [None]*N
	for i in range(N):
		a[i] = 1000//((i+1)&(2**32-1))
		b[i] = 1000//((3*i*i+5*i+1)&(2**32-1))
	return a, b

def calc_media(a):
	media_a = 0
	N = len(a)
	for i in range(N):
		media_a += a[i]/N
	return media_a

def distancia_euclidiana(a, b):
	dist_eucl = 0
	for i in range(len(a)):
		dist_eucl += (a[i]-b[i])**2
	return math.sqrt(dist_eucl)

def main():
	N = 1000000
	x,y = preencher_vetores(N)
	media_x = calc_media(x)
	media_y = calc_media(y)
	dist_eucl = distancia_euclidiana(x,y)

	print("Resultado %s:" % sys.argv[0])
	print("   Media(x) = %1.10f" % media_x)
	print("   Media(y) = %1.10f" % media_y)
	print("   Dist_euclidiana(x,y) = %3.10f" % dist_eucl)

if len(sys.argv)>1:
	cProfile.run('main()')
else:
	main()