#!/bin/bash

cat /dev/urandom > /dev/null &

for i in {1..5}
do
	./Ex6
done

p=$(pidof cat)
kill $p
