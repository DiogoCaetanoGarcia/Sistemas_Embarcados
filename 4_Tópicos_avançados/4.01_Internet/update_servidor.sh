#!/bin/bash

while true
do
	echo '<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd"><html xmlns="http://www.w3.org/1999/xhtml"><head><meta http-equiv="Content-Type" content="text/html; charset=UTF-8" /><title>Temperatura do Raspberry Pi</title></head><body><div class="container"><h1>' > index.html
	echo $(date) >> index.html
	echo '</h1><p>' >> index.html
	echo $(/opt/vc/bin/vcgencmd measure_temp) >> index.html
	echo '</p></div></body></html>' >> index.html
	sudo cp index.html /var/www/html/index.html
	sleep 1
done
