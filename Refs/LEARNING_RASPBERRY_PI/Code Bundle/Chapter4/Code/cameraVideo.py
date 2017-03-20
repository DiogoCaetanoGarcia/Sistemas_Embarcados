import picamera
from time import sleep
camera = picamera.PiCamera()
camera.start_recording('video.h264')
sleep(5)
camera.stop_recording()