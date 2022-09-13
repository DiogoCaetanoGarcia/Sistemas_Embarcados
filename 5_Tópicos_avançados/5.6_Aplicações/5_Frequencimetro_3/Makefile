freq: freq.o lcd.o main.o
	$(CC) main.o freq.o lcd.o -o freq.out -lpigpio 
main.o: main.c freq.h
	$(CC) -c main.c -lpigpio 
freq.o: freq.c freq.h lcd.h
	$(CC) -c freq.c -lpigpio 
lcd.o: lcd.c lcd.h
	$(CC) -c lcd.c -lpigpio 
clean:
	rm freq.out *.o
