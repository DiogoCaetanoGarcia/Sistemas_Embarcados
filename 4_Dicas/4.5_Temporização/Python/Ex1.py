import time, os

timeoftheday = time.time()
print("Data atual:\n   " + time.ctime(timeoftheday))

dias = ["Segunda","Terça", "Quarta", "Quinta","Sexta", "Sábado","Domingo"]
tm_s = time.localtime(timeoftheday)
print("Dia da semana: " + dias[tm_s.tm_wday])

print("Setando estrutura para\n   04/02/2010, 03:30:38")
# Ano, mês, dia do mês, hora-1, minutos, segundos, dia da semana, dia do ano, horário de verão
strtime = time.struct_time([2010,2,4,2,30,38,0,0,0])
print("Tempo retornado:\n   " + time.ctime(time.mktime(strtime)))
print("Conferindo resultado com programa 'cal':")
os.system("cal 2 2010")