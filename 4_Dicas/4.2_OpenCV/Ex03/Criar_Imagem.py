import numpy

A = numpy.zeros((1,16), dtype=numpy.uint8)
for k in range(16):
	A[0,k] = k+1
print("Vetor [%d x %d]" % (A.shape[0], A.shape[1]))
print(A)

A = numpy.zeros((16,1), dtype=numpy.uint8)
for k in range(16):
	A[k,0] = 255-k
print("Vetor [%d x %d]" % (A.shape[0], A.shape[1]))
print(A)

A = numpy.zeros((4,8), dtype=numpy.uint8)
for j in range(4):
	for k in range(8):
		A[j,k] = k+j*8
print("Vetor [%d x %d]" % (A.shape[0], A.shape[1]))
print(A)