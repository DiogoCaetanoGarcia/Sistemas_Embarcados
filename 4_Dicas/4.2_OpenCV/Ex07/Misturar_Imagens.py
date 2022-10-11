import cv2, numpy, sys

if len(sys.argv)<4:
	print("Modo de uso: " + sys.argv[0] + " Nome_Imagem1 Nome_Imagem2 Peso")
	print("Peso deve estar entre 0 e 1")
	sys.exit(-1)

img1 = cv2.imread(sys.argv[1])
img2 = cv2.imread(sys.argv[2])

rows1,cols1,channels1 = img1.shape
rows2,cols2,channels2 = img2.shape
if (rows1!=rows2) or (cols1!=cols2) or (channels1!=channels2):
	print("%s e %s devem ter as mesmas dimensões!" %
		(sys.argv[1], sys.argv[2]))
	sys.exit(-2)

p1 = float(sys.argv[3])
if (p1<0.0) or (p1>1.0):
	print("Peso deve estar entre 0 e 1.")
	sys.exit(-3)
p2 = 1.0-p1

img3 = cv2.addWeighted(img1,p1,img2,p2,0)
cv2.imshow("", img3)
cv2.waitKey(0)
cv2.destroyAllWindows()