import os, struct, stat

try:
	fd = os.open("exercicio8.txt", os.O_RDWR | os.O_CREAT, stat.S_IRWXU)
except OSError:
	print("Erro na abertura do arquivo.")
	exit(-1)
pi = 3.1415
os.write(fd, str.encode("pi = %f" % pi))
os.close(fd)
fd = os.open("exercicio8.txt", os.O_RDONLY)
cnt = ''
c = os.read(fd, 100)
while len(c):
	cnt += c.decode("utf-8")
	c = os.read(fd, 100)
c1,c2,pilido = cnt.split()
print("O valor de PI (lido do arquivo) é", pilido)
os.close(fd)