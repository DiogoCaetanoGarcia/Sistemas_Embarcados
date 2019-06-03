#!/bin/bash

cat /dev/urandom > /dev/null &

for i in {1..5}
do
	./Ex7
done

p=$(pidof cat)
kill $p
