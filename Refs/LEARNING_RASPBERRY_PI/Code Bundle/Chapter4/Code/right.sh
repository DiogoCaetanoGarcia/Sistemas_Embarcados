echo "1" > /sys/class/gpio/gpio14/value
echo "0" > /sys/class/gpio/gpio18/value
echo "0" > /sys/class/gpio/gpio24/value
echo "1" > /sys/class/gpio/gpio23/value
sleep 1
echo "0" > /sys/class/gpio/gpio14/value
echo "0" > /sys/class/gpio/gpio18/value
echo "0" > /sys/class/gpio/gpio24/value
echo "0" > /sys/class/gpio/gpio23/value
