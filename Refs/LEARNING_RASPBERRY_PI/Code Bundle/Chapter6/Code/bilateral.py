import cv2
import numpy as np
img = cv2.imread('fly1.jpg') # Read the original image
blur = cv2.bilateralFilter(img,9,75,75)
cv2.imshow("Original" , img ) # Show original image
cv2.imshow("Bilateral Filter" , blur) # Show Bilateral Filtered image
cv2.waitKey(0)
cv2.destroyAllWindows()
