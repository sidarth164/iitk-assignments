#!/bin/bash
for (( i=1; i<=1000; i++ ))
do
	{ echo "100" ; shuf "file1.txt" | head -n 100; }| ./quicksort.out >> quicktime2.csv 
done;