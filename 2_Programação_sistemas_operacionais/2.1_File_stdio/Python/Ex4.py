try:
	fp = open("arquivo.txt","r");
except OSError:
	print("Erro na abertura do arquivo");
	exit(-1)
c = fp.read(1)
while c != '':
	print(c, end='')
	c = fp.read(1)
fp.close()