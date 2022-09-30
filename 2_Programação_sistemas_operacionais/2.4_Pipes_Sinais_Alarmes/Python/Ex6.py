import os, signal, time

def tratamento_SIGUSR1(signum, frame):
	print("Processo %d recebeu sinal SIGUSR1... ele vai parar agora." % os.getpid())
	exit(1)

signal.signal(signal.SIGUSR1, tratamento_SIGUSR1);

pid_filho = os.fork()
if pid_filho == 0:
	print("Processo filho [%d] vai entrar num loop infinito." % os.getpid())
	while True:
		pass
else:
	time.sleep(1)
	print("Processo %d vai enviar o sinal SIGUSR1 para o processo %d" % (os.getpid(), pid_filho))
	os.kill(pid_filho, signal.SIGUSR1)
	print("Processo %d vai dormir por 1 segundo." % os.getpid())
	time.sleep(1)
print("Processo %d encerrando." % os.getpid())