import os

try:
	fd = os.open("exercicio3.txt", os.O_RDWR | os.O_CREAT)
except OSError:
	print("Erro na abertura do arquivo.")
	exit(-1)
print("Arquivo 'exercicio3.txt' criado. Detalhes:")
os.system("ls -l exercicio3.txt")
os.close(fd)