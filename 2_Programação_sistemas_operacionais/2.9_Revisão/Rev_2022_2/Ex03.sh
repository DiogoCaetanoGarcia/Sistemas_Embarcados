#!/bin/bash

function up()
{
	for i in $(seq $1)
	do
		cd ..
	done
}
