import sys

if len(sys.argv)<2:
	sys.exit()

import os
import pytesseract
import cv2
# pytesseract.pytesseract.tesseract_cmd = "C://Program Files//Tesseract-OCR//tesseract.exe"

def tesseract_with_config(img, lang, psm, oem, tessdata_dir, dpi):
	# whitelist = '''-.:()<>[]{}*/+-_,=#0123456789qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM\\'\\"	 '''
	whitelist = '''0123456789qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM'''
	tess_cfg = '''--psm %d --oem %d --dpi %d --tessdata-dir "%s" -c tessedit_char_whitelist="%s"''' % (psm, oem, dpi, tessdata_dir, whitelist)
	return pytesseract.image_to_string(img, lang=lang, config=tess_cfg)

def get_text(image_path):
	image = cv2.imread(image_path)
	gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
	scale_percent = 100
	if scale_percent!=100:
		width = int(gray.shape[1] * scale_percent / 100)
		height = int(gray.shape[0] * scale_percent / 100)
		dim = (width, height)
		gray = cv2.resize(gray, dim, interpolation=cv2.INTER_CUBIC) # resized_img = cv2.resize(img, dim, interpolation = cv2.INTER_LANCZOS4)
	rectKernel = cv2.getStructuringElement(cv2.MORPH_RECT, (13, 5))
	blackhat = cv2.morphologyEx(gray, cv2.MORPH_BLACKHAT, rectKernel)
	squareKern = cv2.getStructuringElement(cv2.MORPH_RECT, (3, 3))
	light = cv2.morphologyEx(blackhat, cv2.MORPH_DILATE, squareKern)
	# cv2.imshow('blackhat',blackhat)
	# cv2.imshow('light1',light)
	light = cv2.threshold(light, 0, 255,
			cv2.THRESH_BINARY | cv2.THRESH_OTSU)[1]
	cv2.imshow('light2',light)
	cv2.waitKey(0)
	return tesseract_with_config(light, 'eng', 11, 2, '.', 100)

if os.path.isdir(sys.argv[1]):
	folder = sys.argv[1]
	if folder[-1]!='/':
		folder += '/'
	for file in os.listdir(folder):
		f = get_text(folder + file)
		print('--- ' + folder + file + ' ---')
		print(f)
else:
	f = get_text(sys.argv[1])
	print('--- ' + sys.argv[1] + ' ---')
	print(f)
