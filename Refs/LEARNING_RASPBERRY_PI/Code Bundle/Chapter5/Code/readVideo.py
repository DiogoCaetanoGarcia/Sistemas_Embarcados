import numpy as np #import numeric python module
import cv2 #import opencv python
cap = cv2.VideoCapture('/home/pi/chapter7/timelapse.mp4') #It will read  the video file
while(cap.isOpened()):
	ret, frame = cap.read()
	gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY) #Convert each frame to grayscale
	cv2.imshow('frame',gray) #display grayscale image
	if cv2.waitKey(34) & 0xFF == ord('q'): # disaply grayscale image and wait for 34 millisecond before displaying new image
		break
cap.release() # release the videocapture object
cv2.destroyAllWindows() # close the display window

