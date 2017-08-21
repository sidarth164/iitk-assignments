#!/bin/sh

re='^-?[0-9]+([.][0-9]+)?$'

if ! [[ $# =~ 3 ]]; then
	echo "pass only 3 arguments"
	exit
elif ! [ -f $1 ]; then
	echo "pass correct file name"
	exit
else
	grep "$2" $1 | grep "$3"
fi