set title 'Different Distributions'
set xlabel 'Values'
set ylabel 'Frequency'
set style data histograms
set style histogram errorbars gap 0 lw 2
set style fill solid 1 border -1
set xtics offset 4,0
plot newhistogram "NORMAL DISTRIBUTION", 'normalq2' u 4:2:3:xticlabels(1) t 'normal', newhistogram "UNIFORM DISTRIBUTION", 'uniformq2' u 4:2:3:xticlabels(1) t 'uniform'
set terminal postscript eps enhanced color font 'Helvetica,10'
set output 'plot_q2.eps'
replot