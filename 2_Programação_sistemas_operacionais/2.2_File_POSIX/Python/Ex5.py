import os, stat

try:
	fd = os.open("exercicio5.txt", os.O_WRONLY | os.O_CREAT)
except OSError:
	print("Erro na abertura do arquivo.")
	exit(-1)
print("Entre com a string a ser gravada no arquivo: ", end='')
string = input()
os.write(fd, str.encode(string+"\n"))
os.close(fd)