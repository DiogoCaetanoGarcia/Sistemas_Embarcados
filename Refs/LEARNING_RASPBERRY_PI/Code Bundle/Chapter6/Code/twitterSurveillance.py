import numpy as np
import cv2
import tweepy  
import os
import time

# Consumer keys and access tokens, used for OAuth  
consumer_key = 'ENTER YOUR CONSUMER KEY'  
consumer_secret = 'ENTER YOUR CONSUMER SECRET'  
access_token = 'ENTER YOUR ACCESS TOKEN'  
access_token_secret = 'ENTER YOUR ACCESS TOKEN SECRET'  
  
# OAuth process, using the keys and tokens  
auth = tweepy.OAuthHandler(consumer_key, consumer_secret)  
auth.set_access_token(access_token, access_token_secret)  
   
# Creation of the actual interface, using authentication  
api = tweepy.API(auth)
tweetUserID=’@Utsav91292’
face_cascade = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')
while True:
	os.system("raspistill -q 10 -o image.jpg")
	print 'pic taken'
	img = cv2.imread('/home/pi/chapter8/image.jpg')
	gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
	faces = face_cascade.detectMultiScale(gray, 1.3, 5)
	for (x,y,w,h) in faces:
		cv2.rectangle(img,(x,y),(x+w,y+h),(255,0,0),2)
		# Send the tweet with photo  
		photo_path = '/home/pi/chapter8/image.jpg'
		status = tweetUserID+' Photo tweet from Pi: ' + time.strftime('%Y/%m/%d %H:%M:%S')   
		api.update_with_media(photo_path, status=status)  
	print 'end'
	time.sleep(60)
cv2.destroyAllWindows()

