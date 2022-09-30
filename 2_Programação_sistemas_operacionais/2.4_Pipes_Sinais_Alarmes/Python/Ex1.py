import os

fd = os.pipe()
pid_filho = os.fork()
if pid_filho == 0:
	print("Filho vai ler o pipe")
	mensagem = os.read(fd[0], 30)
	if(len(mensagem)==0):
		print("Erro na leitura do pipe")
	else:
		print("Filho leu: " +  mensagem.decode("utf-8"))
else:
	mensagem = "HELLO PIPE"
	# Vamos garantir o envio de 30 bytes no pipe
	# inserindo 20 caracteres '\0'
	mensagem += "\0"*(30-len(mensagem)) 
	
	print("Pai vai escrever no pipe")
	if os.write(fd[1], str.encode(mensagem)) < 0:
		print("Erro na escrita do pipe")
	print("Pai terminou de escrever no pipe")