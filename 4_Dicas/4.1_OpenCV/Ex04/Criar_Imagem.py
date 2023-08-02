import numpy, cv2

A = numpy.zeros((256,256), dtype=numpy.uint8)
for k in range(256):
	A[k] = numpy.arange(256)
cv2.imshow("Matriz 256x256", A)
cv2.waitKey(0);
cv2.destroyWindow("Matriz 256x256");

A = numpy.zeros((256,256,3), dtype=numpy.uint8)
for k in range(256):
	A[k,:,0] = numpy.arange(256)
cv2.imshow("Matriz B 256x256 de 3 canais", A)
cv2.waitKey(0);
cv2.destroyWindow("Matriz B 256x256 de 3 canais");

A = numpy.zeros((256,256,3), dtype=numpy.uint8)
for k in range(256):
	A[k,:,1] = numpy.arange(256)
cv2.imshow("Matriz G 256x256 de 3 canais", A)
cv2.waitKey(0);
cv2.destroyWindow("Matriz G 256x256 de 3 canais");

A = numpy.zeros((256,256,3), dtype=numpy.uint8)
for k in range(256):
	A[k,:,2] = numpy.arange(256)
cv2.imshow("Matriz R 256x256 de 3 canais", A)
cv2.waitKey(0);
cv2.destroyWindow("Matriz R 256x256 de 3 canais");