#!/bin/bash
echo 'Informe o que você quiser, -1 para sair'
read dado
while [ $dado != '-1' ]
do
  echo 'Você digitou' $dado
  read dado
done
echo SAIU!
