import os

try:
	fd = os.open("exemplo.bin", os.O_RDWR | os.O_CREAT)
except OSError:
	print("Erro na abertura do arquivo.")
	exit(-1)
print("Abertura ok.")
os.close(fd)