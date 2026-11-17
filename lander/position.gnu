set terminal pngcairo size 1000,700
set output "position.png"

data_file = "OUT"

set title "Position: Measured vs Estimated"
set grid
set xlabel "Time [s]"
set ylabel "Height [m]"

plot data_file using 1:2 with lines lw 3 lc rgb "#1f77b4" title "Measured Position", \
     data_file using 1:3 with lines lw 2 lc rgb "#d62728" title "Estimated Position"