#!/bin/bash
echo 'Digite um número qualquer:'
read numero
if [ $numero -gt 20 ]; then
  echo 'Este número é maior que 20!'
elif [ $numero -gt -1 ]; then
  echo 'Este número é positivo!'
else
  echo 'Este número é negativo!'
fi

