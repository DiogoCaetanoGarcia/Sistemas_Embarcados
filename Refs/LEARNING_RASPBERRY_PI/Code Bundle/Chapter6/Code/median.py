import cv2
import numpy as np
img = cv2.imread('fly1.jpg') # Read the original image
median = cv2.medianBlur(img,5) #Median Blur with 5*5 kernel
cv2.imshow("Original" , img ) # Show original image
cv2.imshow("Median Filter" , median) # Show Median Filtered image
cv2.waitKey(0)
cv2.destroyAllWindows()
