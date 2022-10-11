import cProfile, numpy, sys

def preencher_vetores(N):
	i = numpy.arange(N)
	a = 1000//numpy.bitwise_and(i+1, 2**32-1)
	b = 1000//numpy.bitwise_and(3*i*i+5*i+1, 2**32-1)
	return a, b

def calc_media(a):
	return numpy.average(a)

def distancia_euclidiana(a, b):
	return numpy.sqrt(numpy.sum((a-b)**2))

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