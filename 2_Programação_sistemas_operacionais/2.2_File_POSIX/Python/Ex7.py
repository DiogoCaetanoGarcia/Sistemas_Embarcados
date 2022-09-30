import os, struct, stat

try:
	fd = os.open("exercicio7.txt", os.O_RDWR | os.O_CREAT, stat.S_IRWXU)
except OSError:
	print("Erro na abertura do arquivo.")
	exit(-1)

pi = float(3.1415)
os.write(fd, struct.pack('f',pi))
os.close(fd)
fd = os.open("exercicio7.txt", os.O_RDONLY)
pilido = struct.unpack('f',os.read(fd,4))
print("O valor de PI (lido do arquivo) é", pilido[0])
os.close(fd)