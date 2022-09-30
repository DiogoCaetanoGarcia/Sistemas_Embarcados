import struct

def abre_arq(arquivo, modo):
	try:
		p = open(arquivo, modo)
	except OSError:
		print("Erro! Impossivel abrir o arquivo!")
		exit(-1)
	return p

pi = float(3.1415)
fp = abre_arq("arquivo.bin", "wb")
fp.write(struct.pack('f',pi))
fp.close()
fp = abre_arq("arquivo.bin", "rb")
pilido = struct.unpack('f',fp.read(4))
print("O valor de PI (lido do arquivo) é", pilido[0])
fp.close()