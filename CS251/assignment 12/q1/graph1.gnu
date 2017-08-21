#!/usr/bin/gnuplot
set terminal pdf
set output 'graph1.pdf'
set title 'Quadratic Function'
set xlabel 'x'
set ylabel 'y'
plot 'graph1.csv' with lines t 'y=x²'
