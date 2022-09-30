try:
	fp = open("arquivo.txt","w")
except OSError:
	print("Erro na abertura do arquivo")
	exit(-1)
print("Entre com a string a ser gravada no arquivo: ")
string = input()
fp.write(string + '\n')
fp.close()
