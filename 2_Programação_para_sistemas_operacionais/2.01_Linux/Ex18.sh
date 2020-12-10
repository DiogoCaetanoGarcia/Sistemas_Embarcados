#!/bin/bash

listar_lixeira()
{
  ls -l ~/.local/share/Trash/files
}
elevar_quad()
{
  echo 'Informe um número:'
  read x
  x2=$((x*x))
  echo $x^2 = $x2
}

echo "Escolha uma opção:"
echo "1 - Listar a lixeira"
echo "2 - Elevar número ao quadrado"
read opcao
if [ $opcao -eq 1 ]; then
  listar_lixeira
elif [ $opcao -eq 2 ]; then
  elevar_quad
fi
