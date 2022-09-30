import os

try:
	fd = os.open("exemplo.bin", os.O_RDWR)
except OSError:
	print("Erro na abertura do arquivo.")
	exit(-1)
os.close(fd)