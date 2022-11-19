#include "Print.h"

void print_sol_fix_time_to_file()
{
    FILE* file = fopen("fix_time sols.txt", "w+");

    for(int m = 0; m < SIZE_X; ++m) {
        fprintf(file, "%10.6lf%15.6lf%15.6lf%15.6lf%15.6lf%15.6lf%15.6lf%15.6lf%15.6lf%15.6lf%15.6lf%15.6lf%15.6lf%15.6lf%15.6lf%15.6lf%15.6lf%15.6lf%15.6lf%15.6lf%15.6lf\n", x[m], f[time_moments[0]][m].at(0), f[time_moments[1]][m].at(0), f[time_moments[2]][m].at(0), f[time_moments[3]][m].at(0), f[time_moments[4]][m].at(0), f[time_moments[0]][m].at(1)/f[time_moments[0]][m].at(0), f[time_moments[1]][m].at(1)/f[time_moments[1]][m].at(0), f[time_moments[2]][m].at(1)/f[time_moments[2]][m].at(0), f[time_moments[3]][m].at(1)/f[time_moments[3]][m].at(0), f[time_moments[4]][m].at(1)/f[time_moments[4]][m].at(0), f[time_moments[0]][m].at(2), f[time_moments[1]][m].at(2), f[time_moments[2]][m].at(2), f[time_moments[3]][m].at(2), f[time_moments[4]][m].at(2), pressure[time_moments[0]][m], pressure[time_moments[1]][m], pressure[time_moments[2]][m], pressure[time_moments[3]][m], pressure[time_moments[4]][m]);
    }

    fclose(file);
} 