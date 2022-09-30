import os

lista_de_argumentos = ["ls"]

pid_filho = os.fork()
if(pid_filho == 0):
	print("Processo-FILHO  %d" % os.getpid())
else:
	print("Processo-PAI    %d" % os.getpid())
	try:
		os.execvp(lista_de_argumentos[0], lista_de_argumentos)
	except:
		print("Processo-PAI: mensagem escrita se houver erro de execucao em execvp()")
print("Fim do processo %d" % os.getpid())