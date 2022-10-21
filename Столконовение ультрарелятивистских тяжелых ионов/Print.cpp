#include "Print.h"

void print_y_to_file()
{
    FILE* file = fopen("y(t).txt", "w+");

    for(int n = 0; n < T_SIZE; ++n) {
        fprintf(file, "%6.3lf %9.4lf\n", x[n], y[n]);
    }

    fclose(file);
}

/*

40.999  999.9999  99.9999  0.333333

*/

void print_Y_e_p_to_file()
{
    FILE* file = fopen("sol.txt", "w+");

    for(int n = 0; n < T_SIZE; ++n) {
        fprintf(file, "%6.3lf%9.4lf%10.6lf\n", x[n], p[n]/e[n], 1./3);
    }

    fclose(file);
}



