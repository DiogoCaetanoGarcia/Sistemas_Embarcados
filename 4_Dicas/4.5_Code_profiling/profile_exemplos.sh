#!/bin/bash

if [ $# -lt 2 ]; then
	echo " Script para profiling de código usando o 'gprof',"
	echo " que produz um perfil de execução de funções do código em C."
	echo " Para isso, precisamos:"
	echo "    1) Compilar o código com a opção '-pg' para o GCC:"
	echo "       -pg : Generate extra code to write profile information suitable"
	echo "             for the analysis program gprof. You must use this option"
	echo "             when compiling the source files you want data about,"
	echo "             and you must also use it when linking."
	echo "    2) Executar o código uma vez para gerar o perfil de execução"
	echo "    3) Rodar o 'gprof' para analisar o perfil de execução."
	echo
	echo " Nos exemplos a seguir, chamamos o GCC com a opção '-static' além de '-pg',"
	echo " que liga o programa criado a outras bibliotecas estaticamente, ao invés de"
	echo " dinamicamente. Assim, conseguimos obter o tempo de execução das funções das"
	echo " bibliotecas usadas nos exemplos, como a 'math.h'."
	echo
	echo " Com relação ao ponto (2), executamos o código com o comando 'time', que indica:"
	echo "    'real': Tempo usado pelo processo, em segundos."
	echo "    'user': Número de segundos-CPU usados pelo processo em user space, em segundos."
	echo "    'sys':  Número de segundos-CPU usados pelo processo em kernel space, em segundos."
	echo " Por exemplo, executando 'time sleep 0.3', obtemos:"
	time sleep 0.3
	echo
	echo " Não é obrigatório executar o código com o 'time' para gerar o perfil de execução."
	echo " Só o utilizamos aqui para mostrar uma segunda ferramenta de profiling, bem mais simples."
	echo
	echo " Modo de uso deste script:"
	echo " $0 NÚMERO_DO_CÓDIGO MODO_OTIMIZAÇÃO"
	echo
	echo "    NÚMERO_DO_CÓDIGO: número do código a ser executado [1-7]"
	echo "    MODO_OTIMIZAÇÃO:  modo de otimização, onde"
	echo "       1: nenhuma otimização"
	echo "       2: otimizar código para executar mais rapidamente"
	echo "       3: opção 2, mas permitindo também funções inline"
	echo
	echo " Referências:"
	echo "    https://www.thegeekstuff.com/2012/08/gprof-tutorial/"
	echo "    https://www.rapidtables.com/code/linux/gcc/gcc-o.html"
	echo
	exit -1
fi

case $1 in
	"1") CODIGO=Ex1.out;;
	"2") CODIGO=Ex2.out;;
	"3") CODIGO=Ex3.out;;
	"4") CODIGO=Ex4.out;;
	"5") CODIGO=Ex5.out;;
	"6") CODIGO=Ex6.out;;
	"7") CODIGO=Ex7.out;;
	* ) echo "O número do código a ser executado deve estar entre 1 e 7!"; exit -2;;
esac

case $2 in
	"1") OTIMIZ_GCC="";;
	"2") OTIMIZ_GCC="-O3 -fno-inline";;
	"3") OTIMIZ_GCC="-O3";;
	* ) echo "O modo de otimização deve estar entre 1 e 3!"; exit -3;;
esac

make ${CODIGO} CFLAGS="${OTIMIZ_GCC} -pg -static "
echo
echo "--- TIME ---"
time ./${CODIGO}
echo
echo "--- GPROF ---"
gprof ./${CODIGO} -p -b
make clean
