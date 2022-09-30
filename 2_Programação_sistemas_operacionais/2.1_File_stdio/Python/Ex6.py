def abre_arq(arquivo, modo):
	try:
		p = open(arquivo, modo)
	except OSError:
		print("Erro! Impossivel abrir o arquivo!")
		exit(-1)
	return p

fp = abre_arq("arquivo.txt", "w")
string = "0"
while(len(string) > 0):
	print("Digite uma nova string. Para terminar, digite <enter>: ")
	string = input()
	fp.write(string + '\n')
fp.close()