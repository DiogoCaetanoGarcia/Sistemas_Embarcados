#!/bin/bash
nome=Fulano
echo Ola $nome
echo Vamos procurar arquivos com seu nome:
ls -l *$nome*.*
echo Vamos conferir o conteúdo da variável:
echo \$nome = $nome
