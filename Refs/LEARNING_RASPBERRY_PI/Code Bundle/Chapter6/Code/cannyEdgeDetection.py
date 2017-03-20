import cv2
import numpy as np
img = cv2.imread('fly1.jpg',0)
edges = cv2.Canny(img,50,200)
cv2.imshow('Original',img)
cv2.imshow('Edge Image',edges)
cv2.waitKey(0)
cv2.destroyAllWindows()

