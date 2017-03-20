import numpy as np
import cv2
cap = cv2.VideoCapture('unimore.avi')
backgroundObject = cv2.BackgroundSubtractorMOG()
while(1):
    ret, frame = cap.read()
    bg = backgroundObject.apply(frame)
    cv2.imshow('frame',bg)
	cv2.imshow('orginial',frame)
    k = cv2.waitKey(30) & 0xff
    if k == 27:
        break
cap.release()
cv2.destroyAllWindows()

