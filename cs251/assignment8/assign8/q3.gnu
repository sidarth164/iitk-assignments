set title 'Analysis of {/Symbol a}, {/Symbol b}'
set ylabel 'Time'
set style data histograms

set style histogram errorbars gap 0 lw 2
set style fill solid 1 border -1

set yrange [0:50]

set xtics offset 4,0

plot newhistogram "GROUP 1" lt 3, 'normalq3_G1' u 3:1:2 t 'normal', 'uniformq3_G1' u 4:2:3:xticlabels(1) t 'uniform', newhistogram "GROUP 2" lt 3, 'normalq3_G1' u 3:1:2 notitle, 'uniformq3_G2' u 4:2:3:xticlabels(1) notitle

set terminal postscript eps enhanced color font 'Helvetica,10'
set output 'plot_q3.eps'
replot