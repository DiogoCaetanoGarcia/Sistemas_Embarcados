import cv2, numpy, sys

if len(sys.argv)<2:
	print("Modo de uso: " + sys.argv[0] + " Nome_Imagem")
	sys.exit(-1)
image = cv2.imread(sys.argv[1])
rows,cols,channels = image.shape

media_linhas  = numpy.round(numpy.mean(image, 0))
media_colunas = numpy.round(numpy.mean(image, 1))

print(" ==> Imagem: " + sys.argv[1])
print(" Linhas: ")
print(media_linhas)
print(" Colunas: ")
print(media_colunas)
