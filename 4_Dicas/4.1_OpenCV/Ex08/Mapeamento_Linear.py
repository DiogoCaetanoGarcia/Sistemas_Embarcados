import cv2, numpy, sys

def Mapeamento_Linear(img1, alpha, beta):
	img2 = numpy.clip(img1*alpha+beta,0,255)
	return img2.astype(numpy.uint8)

if len(sys.argv)<2:
	print("Modo de uso: " + sys.argv[0] + " Nome_Imagem")
	sys.exit(-1)

img = cv2.imread(sys.argv[1])

for beta in numpy.arange(0,75,25):
	for alpha in numpy.arange(0.5,2.0,.5):
		cv2.imshow("%fx + %f" % (alpha, beta),
			Mapeamento_Linear(img,	alpha, beta))

cv2.waitKey(0)
cv2.destroyAllWindows()