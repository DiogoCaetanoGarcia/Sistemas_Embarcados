#!/bin/bash

echo "Execute \"source $0\" para a função up() ser reconhecida no terminal"

function up()
{
	cnt=0
	while [ $cnt -lt $1 ]
	do
		cd ..
		cnt=$((cnt+1))
	done
}
