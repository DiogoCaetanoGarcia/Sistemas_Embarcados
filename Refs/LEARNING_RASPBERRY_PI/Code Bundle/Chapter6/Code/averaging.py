import cv2
import numpy as np
img = cv2.imread('fly1.jpg') # Read the original image
blur = cv2.blur(img,(5,5)) #Blurred image ( Averaged Image) with kernel of 5*5
cv2.imshow("Original" , img ) # Show original image
cv2.imshow("Averaging" , blur ) # Show averaged image
cv2.waitKey(0)
cv2.destroyAllWindows()
