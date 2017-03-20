raspistill --nopreview -w 640 -h 480 -q 5 -o /home/pi/stream/pic.jpg -tl 100 -t 9999999 -th 0:0:0 -n &
LD_LIBRARY_PATH=/home/pi/MJPG-streamer/mjpg-streamer/ /home/pi/MJPG-streamer/mjpg-streamer/mjpg_streamer -i "/home/pi/MJPG-streamer/mjpg-streamer/input_file.so -f /home/pi/stream -n pic.jpg" -o "/home/pi/MJPG-streamer/mjpg-streamer/output_http.so -p 8081 -w /home/pi/MJPG-streamer/mjpg-streamer/www" &
echo "14" > /sys/class/gpio/export
echo "18" > /sys/class/gpio/export
echo "24" > /sys/class/gpio/export
echo "23" > /sys/class/gpio/export 
echo "out" > /sys/class/gpio/gpio14/direction
echo "out" > /sys/class/gpio/gpio18/direction
echo "out" > /sys/class/gpio/gpio23/direction
echo "out" > /sys/class/gpio/gpio24/direction
