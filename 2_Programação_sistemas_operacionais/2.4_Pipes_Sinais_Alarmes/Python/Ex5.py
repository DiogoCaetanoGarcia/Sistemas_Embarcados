import signal, sys

def funcao_sigsegv(signum, frame):
	print("Recebi segment fault. Vou morrer!!!")
	exit(1)

def main():
	main()

signal.signal(signal.SIGSEGV, funcao_sigsegv)

print("Vou forçar um segment fault.")

sys.setrecursionlimit(50000)
main()