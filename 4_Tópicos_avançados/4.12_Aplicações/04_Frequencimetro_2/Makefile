freq: freq.o lcd.o main.o
	$(CC) -lwiringPi main.o freq.o lcd.o -o freq
main.o: main.c freq.h
	$(CC) -lwiringPi -c main.c
freq.o: freq.c freq.h lcd.h
	$(CC) -lwiringPi -c freq.c
lcd.o: lcd.c lcd.h
	$(CC) -lwiringPi -c lcd.c
clean:
	rm freq *.o
