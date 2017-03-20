#Setup Start

# Import required Python libraries
import time
import RPi.GPIO as GPIO

# Use BCM GPIO referencesinstead of physical pin numbers
# Throughout this book you will be using BCM GPIO reference to maintain the consistency
GPIO.setmode(GPIO.BCM)

# Defines the GPIO port number which will be used for Trigger and Echo
# As mentioned before Pin 24 (BCM GPIO Pin number 8) and Pin 26 (BCM GPIO Pin number 7) will be used for Trigger and Echo respectively.
GPIO_TRIGGER = 8
GPIO_ECHO = 7

#setup the GPIO port of raspberry pi to OUTPUT and INPUT
# It will set GPIO Trigger Pin as OUTPUT as you will be sending Trigger signal to the Ultrasonic module. Similarly it will set the GPIO Echo Pin as INPUT as you will get the response from the Ultrasoinc module once you have send the Trigger Pulse to the module.
GPIO.setup(GPIO_TRIGGER,GPIO.OUT)  # Trigger
GPIO.setup(GPIO_ECHO,GPIO.IN)      # Echo

# Set trigger to False (Low)
GPIO.output(GPIO_TRIGGER, False)

# Allow module to settle
time.sleep(0.5)

#SetUp Ends

#Processing Start
# As mentioned in the Ultrasonic sensor module section , first you need to send the 10uS Trigger pulse to Trigger Pin and then module will send the output to the Echo pin
# Send 10us pulse to trigger
GPIO.output(GPIO_TRIGGER, True)
time.sleep(0.00001)
GPIO.output(GPIO_TRIGGER, False)
# Once you have send the Trigger Pulse , as explained in the Ultrasonic sensor module section , after some time you will receive the reflected sound waves. You need to calculate the time that is taken by sound waves to bounce back.
start = time.time()
while GPIO.input(GPIO_ECHO)==0:
	start = time.time()

while GPIO.input(GPIO_ECHO)==1:
	stop = time.time()

# Calculate pulse length
elapsed = stop-start

# Distance pulse travelled in that time is time
# multiplied by the speed of sound (cm/s)
distance = elapsed * 34000

# Thatis the total distance that is covered by the sound waves. To calculate the distance to the nearest wall , you need to divide it by 2
distance = distance / 2

print "Ultrasonic Measurement Distance : %.1f" % distance

# Reset GPIO settings
GPIO.cleanup()

#Processing Ends
