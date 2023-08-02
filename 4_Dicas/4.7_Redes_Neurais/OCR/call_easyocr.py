import sys

if len(sys.argv)<2:
	sys.exit()

import os
import easyocr
reader = easyocr.Reader(['en'])

def easyocr_detect(image_path):
	return reader.readtext(image_path,
		allowlist='0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ',
		min_size=30,
		mag_ratio=3)
		#rotation_info=[0, 90, 180, 270])[0]

def show_results(f, file_name):
	print('--- ' + file_name + ' ---')
	for results in f:
		print('Texto: %s | Confiança = %3.0f%%' % (results[1], 100*results[2]))

if os.path.isdir(sys.argv[1]):
	folder = sys.argv[1]
	if folder[-1]!='/':
		folder += '/'
	for file in os.listdir(folder):
		show_results(easyocr_detect(folder + file),
			folder + file)
else:
	show_results(easyocr_detect(sys.argv[1]),
		sys.argv[1])
