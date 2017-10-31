#!/bin/bash
i=1
n=10000
while [ $i -lt 50000 ];do
	y=$( echo $( echo $n) | ./a.out);
	echo $y >> distribution.txt;
	let i=i+10;
done;