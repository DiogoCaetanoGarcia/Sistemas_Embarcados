#https://drive.google.com/file/d/0B87aGq7vEpoFZ3hDYjlub01rdEk/edit
#https://drive.google.com/file/d/0B87aGq7vEpoFdDFQNGlxbWZUU1U/edit
import os
import cv2
import math

##Resize with resize command
def resizeImage(img):
    dst = cv2.resize(img,None, fx=0.25, fy=0.25, interpolation = cv2.INTER_LINEAR)
    return dst

##Take image with Raspberry Pi camera
#os.system("raspistill -o image.jpg")

##Load image
img = cv2.imread("/home/pi/Desktop/image.jpg") 
grey = cv2.imread("/home/pi/Desktop/image.jpg",0) #0 for grayscale

##Run Threshold on image to make it black and white
ret, thresh = cv2.threshold(grey,50,255,cv2.THRESH_BINARY)

##Use houghcircles to determine centre of circle
circles = cv2.HoughCircles(thresh,cv2.cv.CV_HOUGH_GRADIENT,1,75,param1=50,param2=13,minRadius=0,maxRadius=175)
for i in circles[0,:]:
    #draw the outer circle
    cv2.circle(img,(i[0],i[1]),i[2],(0,255,0),2)
    #draw the centre of the circle
    cv2.circle(img,(i[0],i[1]),2,(0,0,255),3)

##Determine co-ordinates for centre of circle
x1 = circles[0][0][0]
y1 = circles[0][0][1]
x2 = circles[0][1][0]
y2 = circles[0][1][1]
##Angle betwen two circles
theta = math.degrees(math.atan((y2-y1)/(x2-x1)))

##print information
print "x1 = ",x1
print "y1 = ",y1
print "x2 = ",x2
print "y2 = ",y2
print theta
print circles

##Resize image
img = resizeImage(img)
thresh = resizeImage(thresh)
##Show Images 
cv2.imshow("thresh",thresh)
cv2.imshow("img",img)

cv2.waitKey(0)
