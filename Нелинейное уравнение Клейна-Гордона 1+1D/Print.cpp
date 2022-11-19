#include "Print.h"

void print_sol_fix_time_to_file()
{
    FILE* file = fopen("fix_time sols.txt", "w+");

    for(int i = 0; i < SIZE_X; ++i) {
        fprintf(file, "%10.6lf%15.6lf%15.6lf%15.6lf%15.6lf%15.6lf\n", x[i], phi[time_moments[0]][i], phi[time_moments[1]][i], phi[time_moments[2]][i], phi[time_moments[3]][i], phi[time_moments[4]][i]);
    }

    fclose(file);
}