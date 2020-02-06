//
// Created by Ronanndex on 2/3/2020.
//

#include "stdio.h"
#include <math.h>


void print_line() {

    FILE * pipe = _popen("D:\\program\\gnuplot\\bin\\gnuplot.exe -persistent", "w");
    fprintf(pipe, "cd 'D:\\msu\\program_msu\\progi_msu\\praktikum_4_2\\Adams_Multon\\cmake-build-debug'\n");
    //fprintf(pipe, "set style line 1 linecolor rgb 'green' linetype 1 linewidth 1 pointtype 7 pointsize 0.5\n");
    //fprintf(pipe, "set style line 2 linecolor rgb 'black' linetype 1 linewidth 1 pointtype 7 pointsize 0.5\n");
    // fprintf(pipe, "set style data linespoints\n");
    //fprintf(pipe, "set key left top reverse Left spacing 1.25\n");
    fprintf(pipe, "set grid\n");
    //fprintf(pipe, "p 'lss_20_16_out.txt' using 4:xtic(1), 'lss_20_16_out.txt' using 1:3\n");
    fprintf(pipe, "set xlabel '[a;b]'\n");
    fprintf(pipe, "set ylabel 'f(x),P(x)'\n");
    //fprintf(pipe, " set key title 'MAX VALUE = %lf'\n", fabs(tmp));
    //fprintf(pipe, "set arrow from 1.5, 0.3 to 4,0.22\n");
    //if (test_num == 1 || test_num == 2) {
    fprintf(pipe, "plot 'istina.txt'  w l lw 2 lc rgb '#000000' lt 1 ti 'Y',\'istina.txt' u 1:2 w l lw 2  lc rgb '#00ff00' lt 1 ti 'F'\n");
    //} else {
      //  fprintf(pipe, "p 'lss_20_16_out.txt' u 2:3 with linespoints ls 1 title 'P(x)'\n");
    //}
    fflush(pipe);
    _pclose(pipe);
}