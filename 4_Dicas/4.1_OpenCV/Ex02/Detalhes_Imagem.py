import cv2, sys

if len(sys.argv)<2:
	print("Modo de uso: " + sys.argv[0] + " Nome_Imagem")
	sys.exit(-1)
image = cv2.imread(sys.argv[1])
rows,cols,channels = image.shape
print("\n_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n")
print(" ==> Imagem: " + sys.argv[1])
print(" ==> Dimensões: %dx%d pixels" %
	(rows, cols))
print(" ==> %d canais" % channels)
print("\n-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_\n")