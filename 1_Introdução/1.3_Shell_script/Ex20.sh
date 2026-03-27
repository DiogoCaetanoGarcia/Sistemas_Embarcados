#!/bin/bash

fatorial()
{
  fat=1
  for i in $(seq $1)
  do
    fat=$((fat*i))
  done
  echo $fat
}

echo Insira um número:
read n
f=$(fatorial $n)
echo $n! = $f
