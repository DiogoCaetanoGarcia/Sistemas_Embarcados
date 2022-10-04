import time

curtime = time.time()
loc_time = time.localtime(curtime)
print(time.asctime(loc_time))
print(time.strftime("Dia:  %A, %b %d\nHora: %I:%M %p",loc_time))