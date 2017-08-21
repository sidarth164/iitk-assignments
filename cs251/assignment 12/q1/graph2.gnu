#!/usr/bin/gnuplot
set terminal pdf
set output 'graph2.pdf'
set title 'Cubic Function'
set xlabel 'x'
set ylabel 'y'
plot 'graph2.csv' with lines t 'y=x³'
