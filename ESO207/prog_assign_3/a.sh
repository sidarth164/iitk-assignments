#!/bin/bash

for (( c=1; c<=1000; c++ ))
do  
   { echo "100" ; shuf "file1.txt" | head -n 100; }| ./mergesort.out >> mergecomp2.csv 
done

for (( c=1; c<=1000; c++ ))
do  
   { echo "1000" ; shuf "file1.txt" | head -n 1000; }| ./mergesort.out >> mergecomp3.csv 
done

for (( c=1; c<=1000; c++ ))
do  
   { echo "10000" ; shuf "file1.txt" | head -n 10000; }| ./mergesort.out >> mergecomp4.csv 
done

for (( c=1; c<=1000; c++ ))
do  
   { echo "100000" ; shuf "file1.txt" | head -n 100000; }| ./mergesort.out >> mergecomp5.csv 
done

for (( c=1; c<=1000; c++ ))
do  
   { echo "1000000" ; shuf "file1.txt" | head -n 1000000; }| ./mergesort.out >> mergecomp6.csv 
done