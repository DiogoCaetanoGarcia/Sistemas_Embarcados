#!/bin/bash

make fib.out CFLAGS="-O3 -pg -static " > /dev/null
echo "---------"
echo "--- C ---"
echo "---------"
./fib.out
gprof ./fib.out -p -b
make clean > /dev/null

echo "--------------"
echo "--- Python ---"
echo "--------------"
python3 fib.py
echo "--------------"
echo "--- Octave ---"
echo "--------------"
octave fib.m
