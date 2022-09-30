try:
	# O arquivo se chama exemplo.bin e esta localizado no diretório corrente
	fp = open("exemplo.bin","wb")
except OSError as error:
	# Mensagem de erro caso o arquivo nao seja aberto
	print("Erro na abertura do arquivo.")
fp.close()