import os, stat

try:
	fd = os.open("exercicio4.txt", os.O_RDWR | os.O_CREAT, stat.S_IRWXU)
except OSError:
	print("Erro na abertura do arquivo.")
	exit(-1)
print("Arquivo 'exercicio4.txt' criado. Detalhes:")
os.system("ls -l exercicio4.txt")
os.close(fd)