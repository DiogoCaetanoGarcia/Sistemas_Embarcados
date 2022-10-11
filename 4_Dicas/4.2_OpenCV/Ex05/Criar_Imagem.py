import numpy, cv2

A = numpy.zeros((512,256), dtype=numpy.uint8)
for k in range(512):
	A[k] = numpy.arange(256)
cv2.imshow("Matriz 256x256", A)
cv2.waitKey(0);
cv2.destroyWindow("Matriz 512x256");

A = numpy.zeros((512,256,3), dtype=numpy.uint8)
for k in range(512):
	A[k,:,0] = numpy.arange(256)
cv2.imshow("Matriz 256x256", A)
cv2.waitKey(0);
cv2.destroyWindow("Matriz 512x256");

A = numpy.zeros((512,256,3), dtype=numpy.uint8)
for k in range(512):
	A[k,:,1] = numpy.arange(256)
cv2.imshow("Matriz 256x256", A)
cv2.waitKey(0);
cv2.destroyWindow("Matriz 512x256");

A = numpy.zeros((512,256,3), dtype=numpy.uint8)
for k in range(512):
	A[k,:,2] = numpy.arange(256)
cv2.imshow("Matriz 256x256", A)
cv2.waitKey(0);
cv2.destroyWindow("Matriz 512x256");