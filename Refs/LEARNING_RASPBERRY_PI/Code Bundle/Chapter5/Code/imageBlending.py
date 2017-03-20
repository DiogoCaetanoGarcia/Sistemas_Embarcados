import cv2 
import numpy

img1 = cv2.imread('/home/pi/chapter7/img.PNG')
img2 = cv2.imread('/home/pi/chapter7/img2.PNG')

img = cv2.addWeighted(img1,0.7,img2,0.3,0)
cv2.imshow('img',img)
cv2.waitKey(0)
cv2.destroyAllWindows()

