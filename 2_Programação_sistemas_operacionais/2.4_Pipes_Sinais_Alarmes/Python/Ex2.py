import os

fd = os.pipe()
pid_filho = os.fork()
if pid_filho != 0:
	print("Pai vai ler o pipe")
	mensagem = os.read(fd[0], 30)
	if(len(mensagem)==0):
		print("Erro na leitura do pipe")
	else:
		print("Pai leu: " +  mensagem.decode("utf-8"))
else:
	mensagem = "HELLO PIPE"
	mensagem += "\0"*(30-len(mensagem)) 
	print("Filho vai escrever no pipe")
	if os.write(fd[1], str.encode(mensagem)) < 0:
		print("Erro na escrita do pipe")
	print("Filho terminou de escrever no pipe")