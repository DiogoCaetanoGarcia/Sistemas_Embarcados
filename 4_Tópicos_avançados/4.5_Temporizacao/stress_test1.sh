#!/bin/bash

cat /dev/urandom > /dev/null &

printf "Cálculo de tempo usando "
printf "clock_gettime():\n\n"
printf "clock_gettime(CLOCK_MONOTONIC)\n"
printf "   retorna o tempo do clock\n"
printf "   'monotônico' - isto é, não\n"
printf "   afetado por descontinuidades\n"
printf "   no tempo do sistema (p.ex.,\n"
printf "   se o administrador mudar o\n"
printf "   relógio do sistema.\n"

for i in {1..5}
do
	./Ex6
done

p=$(pidof cat)
kill $p
