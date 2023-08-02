import cProfile, math, sys

def preencher_vetores(N):
	a = [1000//((i+1)&(2**32-1)) for i in range(N)]
	b = [1000//((3*i*i+5*i+1)&(2**32-1)) for i in range(N)]
	return a, b

def calc_media(a):
	return sum(a)/len(a)

def distancia_euclidiana(a, b):
	dif_quad = [(ai-bi)**2 for ai,bi in zip(a,b)]
	return math.sqrt(sum(dif_quad))

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