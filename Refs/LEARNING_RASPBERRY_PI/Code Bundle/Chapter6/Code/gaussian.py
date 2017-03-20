import cv2
import numpy as np
img = cv2.imread('fly1.jpg') # Read the original image
blur = cv2.GaussianBlur(img,(5,5),0) #Gaussian Blurred image with 5*5 kernal
cv2.imshow("Original" , img ) # Show original image
cv2.imshow("Gaussian Filter" , blur ) # Show Gaussian Filtered image
cv2.waitKey(0)
cv2.destroyAllWindows()
