import os, signal

def tratamento_alarme(signum, frame):
	signal.alarm(1)
	# os.system("date")
	os.system("date +%H:%M:%S.%N")

signal.signal(signal.SIGALRM, tratamento_alarme)
signal.alarm(1)
print("Aperte CTRL+C para acabar:")
while True:
	pass