#!/bin/bash
echo Informe valor para contagem
read valor
i=1
echo Contagem:
while [ $i -le $valor ]
do
  echo $i
  i=$((i+1))
done
