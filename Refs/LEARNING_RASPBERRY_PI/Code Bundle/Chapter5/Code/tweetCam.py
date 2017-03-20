import os
import time
import tweepy

OWNER="Utsav91292"
LAST_MESSAGE_ID=0
MESSAGE_NUMBER='2'
DM_MESSAGE1="#TweetCam"
DM_MESSAGE2="Take Picture"

auth = tweepy.OAuthHandler(consumer_key,consumer_secret)
auth.set_access_token(access_token, access_token_secret)
	
api = tweepy.API(auth)
imageNumber=0
while(True):
	test=api.direct_messages(count=MESSAGE_NUMBER)
	for count in range(0,len(test)):
			if(LAST_MESSAGE_ID<test[count].id and test[count].sender_screen_name==OWNER and (test[count].text==DM_MESSAGE1 or test[count].text==DM_MESSAGE2)):
				os.system("raspistill -o image%d.jpg"%(imageNumber))
				api.send_direct_message(user=OWNER,text='I have taken the photo')
				LAST_MESSAGE_ID=test[count].id
				imageNumber+=1
	print("waittime")
	time.sleep(60)
