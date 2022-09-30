def abre_arq(arquivo, modo):
	try:
		p = open(arquivo, modo)
	except OSError:
		print("Erro! Impossivel abrir o arquivo!")
		exit(-1)
	return p

def le_arq(p):
	c = fp.read(1000)
	while c != '':
		print(c, end='')
		c = fp.read(1000)

frase = "Este é um arquivo chamado: "
print("Entre com um nome para o arquivo:")
str = input()
fp = abre_arq(str, "w");
frase += str + "\n"
fp.write(frase)
fp.close()

fp = abre_arq(str, "r");
le_arq(fp)
fp.close()