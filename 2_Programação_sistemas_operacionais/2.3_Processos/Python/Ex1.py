import os

print("Programas em execução:")
os.system("ps")
print ("Identificador do processo (PID) é: %d" % os.getpid( ))
print ("Identificador do processo-pai (PPID): %d" % os.getppid( ))
