freq: freq.o lcd.o main.o
	$(CC) main.o freq.o lcd.o -o freq.out -lwiringPi 
main.o: main.c freq.h
	$(CC) -c main.c -lwiringPi 
freq.o: freq.c freq.h lcd.h
	$(CC) -c freq.c -lwiringPi 
lcd.o: lcd.c lcd.h
	$(CC) -c lcd.c -lwiringPi 
clean:
	rm freq.out *.o
