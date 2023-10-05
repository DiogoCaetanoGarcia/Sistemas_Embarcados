import sys

if len(sys.argv)<2:
	sys.exit()

import os
import cv2
import numpy as np


# Function to detect license plates in an image
def detect_license_plate_Haar_Cascade(image_path):
	# Load the pre-trained cascade classifier for license plate detection
	plate_cascade = cv2.CascadeClassifier('haarcascade_russian_plate_number.xml')

	# Load the image
	image = cv2.imread(image_path)
	
	# Convert the image to grayscale
	gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
	
	# Detect license plates in the image
	plates = plate_cascade.detectMultiScale(gray, scaleFactor=1.1, minNeighbors=5, minSize=(30, 30))
	
	# Draw bounding boxes around the detected license plates
	for (x, y, w, h) in plates:
		cv2.rectangle(image, (x, y), (x+w, y+h), (0, 255, 0), 2)
	
	# Display the image with license plate detection
	cv2.imshow('License Plate Detection', image)
	cv2.waitKey(0)
	cv2.destroyAllWindows()

# Function to detect license plates in an image
def detect_license_plate_image_processing_1(image_path):
	# Load the image
	image = cv2.imread(image_path)

	# Preprocess the image
	gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
	# blurred = cv2.bilateralFilter(gray, 9, 75, 75) #
	blurred = cv2.GaussianBlur(gray, (5, 5), 0)
	edges = cv2.Canny(blurred, 50, 150)

	# Find contours in the edge map
	contours, _ = cv2.findContours(edges.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

	# # Filter and approximate contours to rectangles
	# rectangles = []
	# for contour in contours:
	#     perimeter = cv2.arcLength(contour, True)
	#     approx = cv2.approxPolyDP(contour, 0.02 * perimeter, True)
	#     if len(approx) == 4:  # Select contours with 4 vertices (rectangles)
	#         rectangles.append(approx)

	# Filter and approximate contours to rectangles
	rectangles = []
	for contour in contours:
		perimeter = cv2.arcLength(contour, True)
		approx = cv2.approxPolyDP(contour, 0.02 * perimeter, True)
	
		if len(approx) == 4:  # Select contours with 4 vertices (rectangles)
			# Calculate the angles between edges
			angles = []
			for i in range(4):
				p1 = approx[i]
				p2 = approx[(i + 1) % 4]
				p3 = approx[(i + 2) % 4]
				v1 = p1 - p2
				v2 = p3 - p2
				dot = np.dot(v1.flatten(), v2.flatten())
				norm1 = np.linalg.norm(v1)
				norm2 = np.linalg.norm(v2)
				angle = np.arccos(dot / (norm1 * norm2))
				angles.append(np.degrees(angle))
			
			# Check angles to verify rectangular shape
			if all(angle > 80 and angle < 100 for angle in angles):
				rectangles.append(approx)
			# x, y, w, h = cv2.boundingRect(approx)
			# aspect_ratio = float(w) / h
			# area = cv2.contourArea(contour)
			# # epsilon = 0.02 * perimeter
			# print("--------------")
			# print((x,y,w,h,aspect_ratio,area))
		
			# # Additional conditions: aspect ratio and area
			# #if 0.32 <= aspect_ratio <= 3.1 and area < 100: # and cv2.isContourConvex(approx) and cv2.approxPolyDP(contour, epsilon, True).shape[0] == 4:
			# rectangles.append(approx)

	i=0
	# Draw bounding boxes around the detected rectangles
	for rect in rectangles:
		cv2.drawContours(image, [rect], -1, (0, 255*i/len(rectangles), 255), 2)
		i+=1

	# Display the image with the detected rectangles
	cv2.imshow("Rectangular Features", image)
	cv2.waitKey(0)
	cv2.destroyAllWindows()

# Function to detect license plates in an image
def detect_license_plate_image_processing_2(image_path):
	# Load the image
	image = cv2.imread(image_path)
	# Preprocess the image
	gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
	blurred = cv2.bilateralFilter(gray, 9, 75, 75)
	edges = cv2.Canny(blurred, 50, 150)
	# Find contours in the edge map
	contours, _ = cv2.findContours(edges.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
	plates = []
	for contour in contours:
		x,y,w,h = cv2.boundingRect(contour)
		if (150 <= w <= 500) and (50 <= h <= 150) and (w >=3*h):
			plates.append((x,y,x+w,y+h))
	# Draw bounding boxes around the detected rectangles
	for i, plate in enumerate(plates):
		image = cv2.rectangle(image,
			(plate[0],plate[1]), 
			(plate[2],plate[3]),
			(0, 255*i/len(plates), 255),
			2)

	# Display the image with the detected rectangles
	cv2.imshow("Rectangular Features", image)
	cv2.waitKey(0)
	cv2.destroyAllWindows()


if os.path.isdir(sys.argv[1]):
	folder = sys.argv[1]
	if folder[-1]!='/':
		folder += '/'
	for file in os.listdir(folder):
		detect_license_plate_image_processing_2(folder + file)
else:
	detect_license_plate_image_processing_2(sys.argv[1])
