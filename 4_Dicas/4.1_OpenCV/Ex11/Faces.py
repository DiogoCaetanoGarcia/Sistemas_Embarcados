import cv2, numpy, sys

def detectAndDisplay(image, faceCascade, eyesCascade):
	gray  = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
	gray = cv2.equalizeHist(gray)
	faces = faceCascade.detectMultiScale(gray)
	for (x, y, w, h) in faces:
		cv2.ellipse(image, (int(x+w/2), int(y+h/2)), (int(w/2),int(h/2)), 0, 0, 360, ( 255, 0, 255 ), 4 )
		faceROI = gray[y:y+h,x:x+h]
		eyes = eyesCascade.detectMultiScale(faceROI)
		for (xe, ye, we, he) in eyes:
			cv2.circle(image, (int(x+xe+we/2), int(y+ye+he/2)), round((we + he)*0.25), ( 255, 0, 0 ), 4 )
	cv2.imshow("Faces found", image)
	cv2.waitKey(0)

if len(sys.argv)<4:
	print("Modo de uso: " + sys.argv[0] + " Nome_Imagem Cascade_Face Cascade_Olhos")
	sys.exit(-1)

face_cascade = cv2.CascadeClassifier()
if not face_cascade.load(sys.argv[2]):
	print("--(!)Error loading face cascade")
	sys.exit(-1)

eyes_cascade = cv2.CascadeClassifier()
if not eyes_cascade.load(sys.argv[3]):
	print("--(!)Error loading eyes cascade")
	sys.exit(-1)

detectAndDisplay(cv2.imread(sys.argv[1]), face_cascade, eyes_cascade)