#include "Print.h"

void print_sol_fix_time_to_file()
{
    FILE* file = fopen("fix_time sols.txt", "w+");
    // fprintf(file, "Time%13.1lf%21.1lf%21.1lf%21.1lf%21.1lf       \n", time[time_moments[0]], time[time_moments[1]], time[time_moments[2]], time[time_moments[3]], time[time_moments[4]]);
    // fprintf(file, "         X          U         X          U         X          U         X          U         X          U   \n");
    // for(int m = 0; m < SIZE_X; ++m) {
    //     fprintf(file, "%14.6lf%10.6lf%11.6lf%10.6lf%11.6lf%10.6lf%11.6lf%10.6lf%11.6lf%10.6lf\n", x[m], u[time_moments[0]][m], x[m], u[time_moments[1]][m], x[m], u[time_moments[2]][m], x[m], u[time_moments[3]][m], x[m], u[time_moments[4]][m]);
    // }

    for(int m = 0; m < SIZE_X; ++m) {
        fprintf(file, "%10.6lf%15.6lf%15.6lf%15.6lf%15.6lf%15.6lf%15.6lf%15.6lf%15.6lf%15.6lf%15.6lf\n", x[m], u_MC[time_moments[0]][m], u_MC[time_moments[1]][m], u_MC[time_moments[2]][m], u_MC[time_moments[3]][m], u_MC[time_moments[4]][m], u_ONO[time_moments[0]][m], u_ONO[time_moments[1]][m], u_ONO[time_moments[2]][m], u_ONO[time_moments[3]][m], u_ONO[time_moments[4]][m]);
    }

    fclose(file);
} 