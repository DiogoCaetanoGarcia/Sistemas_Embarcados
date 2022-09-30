def erro_fopen():
	print("Erro na abertura do arquivo.")
	print("Fim de programa.")
	exit(1)

try:
	fp = open("exemplo.bin","wb")
except OSError:
	erro_fopen()
print('Leitura OK')
fp.close()