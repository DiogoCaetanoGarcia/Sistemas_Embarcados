import cv2, numpy, sys

if len(sys.argv)<2:
	print("Modo de uso: " + sys.argv[0] + " Nome_Imagem")
	sys.exit(-1)
image = cv2.imread(sys.argv[1])
print(" ==> Imagem: " + sys.argv[1])
print(" Linhas: ")
print(cv2.reduce(image, 0, cv2.REDUCE_AVG))
print(" Colunas: ")
print(cv2.reduce(image, 1, cv2.REDUCE_AVG))