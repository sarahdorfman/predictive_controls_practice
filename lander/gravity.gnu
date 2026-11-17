set terminal pngcairo size 1000,700
set output "gravity.png"

data_file = "OUT"

set title "Gravity: Kalman Filter Estimation"
set grid
set xlabel "Time [s]"
set ylabel "Gravity [m/s^2]"

plot data_file using 1:5 with lines lw 3 lc rgb "#1f77b4" title "Estimated Gravity", \
     data_file using 1:6 with lines lw 2 lc rgb "#d62728" title "Actual Gravity"