import time
import os
import threading , feedparser, time
import RPi.GPIO as GPIO
from time import strftime
from datetime import datetime
from time import sleep
from random import randint
import subprocess
import sys

class HD44780:

	def __init__(self, pin_rs=7, pin_e=8, pins_db=[18,23,24,25]):

		self.pin_rs=pin_rs
		self.pin_e=pin_e
		self.pins_db=pins_db

		GPIO.setmode(GPIO.BCM)
		GPIO.setup(self.pin_e, GPIO.OUT)
		GPIO.setup(self.pin_rs, GPIO.OUT)
		for pin in self.pins_db:
			GPIO.setup(pin, GPIO.OUT)

		self.clear()

	def clear(self):
		""" Blank / Reset LCD """

		self.cmd(0x33) 
		self.cmd(0x32) 
		self.cmd(0x28) 
		self.cmd(0x0C)
		self.cmd(0x06) 
		self.cmd(0x01) 

	def cmd(self, bits, char_mode=False):
		""" Send command to LCD """

		sleep(0.001)
		bits=bin(bits)[2:].zfill(8)

		GPIO.output(self.pin_rs, char_mode)

		for pin in self.pins_db:
			GPIO.output(pin, False)

		for i in range(4):
			if bits[i] == "1":
				GPIO.output(self.pins_db[i], True)

		GPIO.output(self.pin_e, True)
		GPIO.output(self.pin_e, False)

		for pin in self.pins_db:
			GPIO.output(pin, False)

		for i in range(4,8):
			if bits[i] == "1":
				GPIO.output(self.pins_db[i-4], True)


		GPIO.output(self.pin_e, True)
		GPIO.output(self.pin_e, False)

	def message(self, text="' '+datetime.now().strftime('%H:%M:%S')"):
		""" Send string to LCD. Newline wraps to second line"""

		for char in text:
			if char == '\n':
				self.cmd(0xC0) # next line
			else:
				self.cmd(ord(char),True)

if __name__=='__main__':
	lcd = HD44780()
	lcd.message(" Enter Hour \n 24hr Format")
	alarm_HH = input("Enter the hour you want to wake up at: ")
	lcd.clear()
	lcd.message(" Enter Minute ")
	alarm_MM = input("Enter the minute you want to wake up at: ")
	lcd.clear()
	lcd.message(" Alarm set at \n "+str(alarm_HH)+":"+str(alarm_MM))
	print("Alarm Set at: {0:02}:{1:02}").format(alarm_HH, alarm_MM)
	hours=int(alarm_HH)
	minutes=int(alarm_MM)
	keep_running=True;

	while keep_running:
		now = time.localtime()
		if (now.tm_hour == hours and now.tm_min == minutes):
			print("ALARM NOW!\n")
			#lcd.clear()
			#lcd.message(" Alarm Now")
			p=subprocess.Popen(['omxplayer Samjhawan.mp3'],stdin=subprocess.PIPE,shell=True)
			correctAnswerCount=0
			while True:
				number1=randint(0,9)
				number2=randint(10,19)
				time.sleep(1)
				lcd.clear()
				lcd.message(" "+str(number1)+" + "+str(number2))
				userInput=raw_input(str(number1)+"+"+str(number2))
				try:
					answer = int(userInput)
					if(answer==number1+number2):
						correctAnswerCount+=1
					if(correctAnswerCount==2):
						print "Alarm Off"
						lcd.clear()
						lcd.message(" Alarm Off")
						keep_running=False
						p.communicate('q')
						os._exit(1)
				except ValueError:
					print("That's not an int!")
		else:
			time.sleep(60)
