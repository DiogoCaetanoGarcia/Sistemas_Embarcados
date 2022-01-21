#!/bin/bash

contagem()
{
  echo 3 1os parâmetros = $1 $2 $3
  for i in $(seq $1)
  do
    echo i = $i
  done
}

contagem 6 Ab Cde
echo -------------
contagem 2 10000000
echo -------------
contagem 5
