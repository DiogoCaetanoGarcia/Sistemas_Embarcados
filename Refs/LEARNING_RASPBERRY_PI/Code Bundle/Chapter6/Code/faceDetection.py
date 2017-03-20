import numpy as np
import cv2
face_cascade = cv2.CascadeClassifier('/home/pi/chapter8/haarcascade_frontalface_default.xml')
img = cv2.imread('/home/pi/chapter8/samarthutsav.jpg')
gray = cv2.imread('/home/pi/chapter8/samarthutsav.jpg',0)
faces = face_cascade.detectMultiScale(gray, 1.3, 5)
for (x,y,w,h) in faces:
    cv2.rectangle(img,(x,y),(x+w,y+h),(255,0,0),2)
cv2.imshow('img',img)
cv2.waitKey(0)
cv2.destroyAllWindows()

