import cv2

# Load an color image in grayscale
img = cv2.imread('/home/pi/Desktop/samarth.jpg',0)
cv2.resize(img,(100,100))
cv2.imshow('image',img)
#cv2.resize(img,(100,100))
key=cv2.waitKey(0)
if key == 27:         # wait for ESC key to exit
    cv2.destroyAllWindows()
elif key == ord('s'): # wait for 's' key to save and exit
    cv2.imwrite('/home/pi/Desktop/chapter7/samarth.png',img)
    cv2.destroyAllWindows()
