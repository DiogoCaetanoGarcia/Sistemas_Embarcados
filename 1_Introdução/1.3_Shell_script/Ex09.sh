#!/bin/bash
echo 'Digite um número qualquer:'
read numero
if [ $numero -gt 20 ]; then
  echo 'Este número é maior que 20!'
elif [ $numero -gt 0 ]; then
  echo 'Este número é positivo!'
elif [ $numero -eq 0 ]; then
  echo 'Este número é nulo!'
else
  echo 'Este número é negativo!'
fi

