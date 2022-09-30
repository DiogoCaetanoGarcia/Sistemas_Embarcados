import os, time

def preenche_str(s, n_bytes):
	s += '\0'*(n_bytes-len(s))
	return str.encode(s)

fd = os.pipe()
pid_filho = os.fork()
if pid_filho == 0:
	print("Filho vai ler o pipe")
	buffer_filho = os.read(fd[0], 30).decode("utf-8")
	print("Valor lido pelo filho = " + buffer_filho)
	print("Filho vai escrever no pipe")
	msg_filho = preenche_str("FILHO DIZ: HELLO PIPE", 30)
	os.write(fd[1], msg_filho)
	print("Filho terminou de escrever no pipe")
else:
	msg_pai = preenche_str("PAI DIZ: HELLO PIPE", 30)
	print("Pai vai escrever no pipe")
	os.write(fd[1], msg_pai)
	print("Pai terminou de escrever no pipe")
	print("Pai vai hibernar por 1 segundo, para dar tempo do filho ler o pipe")
	time.sleep(1)
	print("Pai vai ler o pipe")
	buffer_pai = os.read(fd[0], 30).decode("utf-8")
	print("Valor lido pelo pai = " + buffer_pai)