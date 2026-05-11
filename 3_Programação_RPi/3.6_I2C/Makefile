all: Ex1.out Ex2.out Ex3.out Ex4.out
Ex1.out: Ex1.c
	gcc Ex1.c -o Ex1.out
Ex2.out: Ex2_HC05_UART.c
	gcc Ex2_HC05_UART.c    -o Ex2.out -lwiringPi
Ex3.out: Ex4_HMC5883L_I2C.c
	gcc Ex3_HMC5883L_I2C.c -o Ex3.out -lm
Ex4.out: Ex4_HMC5883L_I2C.c
	gcc Ex4_HMC5883L_I2C.c -o Ex4.out -lm
clean:
	rm -f *.out *.o *.bin *.txt *.html
