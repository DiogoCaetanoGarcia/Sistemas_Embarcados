import cv2, sys

if len(sys.argv)<2:
	print("Modo de uso: " + sys.argv[0] + " Nome_Imagem")
	sys.exit(-1)
image = cv2.imread(sys.argv[1])
cv2.imshow(sys.argv[1], image)
cv2.waitKey(0)
cv2.destroyAllWindows()