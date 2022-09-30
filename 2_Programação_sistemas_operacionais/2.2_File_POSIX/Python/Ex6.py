import os, stat

try:
	fd = os.open("exercicio5.txt", os.O_RDONLY)
except OSError:
	print("Erro na abertura do arquivo.")
	exit(-1)
s = os.read(fd, 1)
while len(s):
	print(s.decode("utf-8"), end='')
	s = os.read(fd, 1)
os.close(fd)