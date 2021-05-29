#!/bin/bash
echo 'Selecione uma opção:'
echo '1 - Exibir data e hora do sistema'
echo '2 - Calcular 10/2'
echo '3 - Exibir uma mensagem'
read opcao;
case $opcao in
  '1')
    date +"%T, %d/%m/%y, %A"
    ;;
  '2')
    result=$((10/2))
    echo "10/2 = $result"
    ;;
  '3')
    echo "Informe o seu nome:"
    read nome;
    echo "Olá $nome!"
    ;;
  *)
    echo "Opção inválida!!!"
esac
