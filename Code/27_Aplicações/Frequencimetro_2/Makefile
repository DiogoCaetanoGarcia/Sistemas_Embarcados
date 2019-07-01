freq: freq.o lcd.o main.o
	gcc -lwiringPi main.o freq.o lcd.o -o freq
main.o: main.c freq.h
	gcc -lwiringPi -c main.c
freq.o: freq.c freq.h lcd.h
	gcc -lwiringPi -c freq.c
lcd.o: lcd.c lcd.h
	gcc -lwiringPi -c lcd.c
clean:
	rm freq *.o
