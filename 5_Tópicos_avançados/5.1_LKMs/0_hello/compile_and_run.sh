#!/bin/bash
echo
echo O código \"Olá mundo\" típico reside no user space do sistema operacional.
echo vamos ver as chamadas ao sistema feitas pelo \"Olá mundo\".
echo
read -p "Aperte [ENTER] para continuar..."
echo
gcc hello.c -o hello.out
strace ./hello.out
rm hello.out
