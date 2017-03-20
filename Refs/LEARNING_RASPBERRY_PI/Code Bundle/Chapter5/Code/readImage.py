#import the python opencv module
import cv2
import numpy
#imread will read an image 
img=cv2.imread('/home/pi/chapter7/test.PNG')
#show an image in new window titled "image"
cv2.imshow('image' , img)
#press ANY key to close the windows
cv2.waitKey(0)
#close the opened window
cv2.destroyAllWindows()

