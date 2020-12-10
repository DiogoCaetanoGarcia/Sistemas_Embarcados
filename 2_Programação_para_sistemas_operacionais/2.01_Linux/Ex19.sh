#!/bin/bash
echo O nome deste script é $0
echo $# argumentos passados pelo usuário
if [ $# -ge 1 ]; then
  echo Os parâmetros de entrada foram:
  echo '  ' $@
  echo Em particular...
  echo '   Arg1 =' $1
fi
if [ $# -ge 2 ]; then
  echo '   Arg2 =' $2
fi
