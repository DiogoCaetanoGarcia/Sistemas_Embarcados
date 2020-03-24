#!/bin/bash

nf=0
N=0
for ns in $(grep -oP '[$0-9]+' $1)
do
	N=$((N+1))
	nf=$((nf+ns))
done
nf=$((nf+N/2))
nf=$((nf/N))
echo "Media($N alunos) = $nf"
