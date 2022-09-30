import struct

def abre_arq(arquivo, modo):
	try:
		p = open(arquivo, modo)
	except OSError:
		print("Erro! Impossivel abrir o arquivo!")
		exit(-1)
	return p

pi = 3.1415
fp = abre_arq("arquivo.bin", "w")
fp.write("pi = %f" % pi)
fp.close()
fp = abre_arq("arquivo.bin", "r")
c1,c2,pilido = fp.readline().split()
print("O valor de PI (lido do arquivo) é", pilido)
fp.close()