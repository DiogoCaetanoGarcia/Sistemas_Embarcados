import signal

def funcao_para_control_c(signum, frame):
	print("\nQuem mandou você pressionar CTRL-C?")
	print("Vou ter de fechar o programa!")
	exit(1)

signal.signal(signal.SIGINT, funcao_para_control_c)
print("Pressione CTRL-C para retirar o programa do loop infinito abaixo.")
while True:
	pass