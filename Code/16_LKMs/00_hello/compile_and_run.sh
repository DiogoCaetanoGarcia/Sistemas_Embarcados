#!/bin/bash
echo
echo O código "Olá mundo" típico reside no user space do sistema operacional.
echo vamos ver as chamadas ao sistema feitas pelo "Olá mundo".
echo
read
echo
gcc hello.c -o hello
strace ./hello
rm hello
