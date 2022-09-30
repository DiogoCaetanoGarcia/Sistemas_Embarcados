import os

print('Comando: "ls"')
a = os.system("ls")
print("Retorno: %d" % a)

print('Comando: "ls 12345.txt"')
a = os.system("ls 12345.txt")
print("Retorno: %d" % a)

print('Comando: "abcde"')
a = os.system("abcde");
print('Retorno de system("abcde"): %d' % a)
