import os

try:
	fd = os.open("exercicio2.txt", os.O_RDWR | os.O_CREAT)
except OSError:
	print("Erro na abertura do arquivo.")
	exit(-1)
print("Abertura ok.")
os.close(fd)