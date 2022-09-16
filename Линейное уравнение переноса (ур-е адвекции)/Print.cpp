#include "Print.h"

/*
----------------------------------------------------------
 ( x , t ) |    Computer solution    |    Exact solution  
 (334,  4) |         102.455657      |      122.465879      


*/

void print_sol()
{
    printf("----------------------------------------------------------\n");
    printf(" ( t , x ) |    Computer solution    |    Exact solution  \n");
    for(int n = 0; n < SIZE_T; ++n) {
        for(int m = 0; m < SIZE_X; ++m) {
            printf(" (%3d,%3d) |%19.6lf      |%16.6lf    \n", n, m, u[n][m], phi(x[m] - c * time[n]));
        }
        printf("\n");
    }
    
}

void print_Kurant_number()
{
    printf("Kurant number = %lf\n\n", eta);
}

/*
            Neyavniy Leviy Ugolok       Laks Ventroff                TVD         
---------------------------------------------------------------------------------
   Time       e_max       e_rms       e_max       e_rms       e_max       e_rms  
---------------------------------------------------------------------------------
  9.9999    9.000000    9.000000    9.000000    9.000000    9.000000    9.000000
*/

void print_e_max_and_e_rms()
{
    printf("---------------------------------------------------------------------------------\n");
    printf("            Neyavniy Leviy Ugolok       Laks Ventroff                TVD         \n");
    printf("---------------------------------------------------------------------------------\n");
    printf("   Time       e_max       e_rms       e_max       e_rms       e_max       e_rms  \n");
    printf("---------------------------------------------------------------------------------\n");
    for(int k = 0; k < 5; ++k) {
        printf("%8.4lf%12.6lf%12.6lf%12.6lf%12.6lf%12.6lf%12.6lf\n", time[time_moments[k]], e_max[k][0], e_rms[k][0], e_max[k][1], e_rms[k][1], e_max[k][2], e_rms[k][2]);
    }
    printf("---------------------------------------------------------------------------------\n");
    printf("\n");
}

/*
            Neyavniy Leviy Ugolok       Laks Ventroff                TVD         
----------------------------------------------------------------------------
   Time              TV                      TV                      TV          
----------------------------------------------------------------------------
  9.9999          9.000000                9.000000                9.000000
*/

void print_TV()
{
    printf("----------------------------------------------------------------------------\n");
    printf("            Neyavniy Leviy Ugolok       Laks Ventroff                TVD    \n");
    printf("----------------------------------------------------------------------------\n");
    printf("   Time              TV                      TV                      TV     \n");
    printf("----------------------------------------------------------------------------\n");
    for(int k = 0; k < 5; ++k) {
        printf("%8.4lf%18.6lf%24.6lf%24.6lf\n", time[time_moments[k]], TV[k][0], TV[k][1], TV[k][2]);
    } 
    printf("----------------------------------------------------------------------------\n");
    printf("\n");  
}

/*

      X         T        U(X, T)
  -2.346576   3.475866   0.347658
   0.287498
*/

void print_sol_to_file()
{
    FILE* file = fopen("results.txt", "w+");
    fprintf(file,"      T         X        U(T, X)  \n");
    for(int n = 0; n < SIZE_T; ++n) {
        int n_ = SIZE_T - 1 - n;
        for(int m = 0; m < SIZE_X; ++m) {
            fprintf(file, "%11.6lf%11.6lf%11.6lf\n", time[n_], x[m], u[n_][m]);
        }
    }
    fclose(file);
}

/*
Time          1.5                  2.6                  3.7                  4.9                  4,5       
         X          U         X          U         X          U         X          U         X          U         
    -99.999999 -1.999999 -99.999999 -1.999999 -99.999999 -1.999999 -99.999999 -1.999999 -99.999999 -1.999999
*/

/*

-99.999999  -99999.999999  -99999.999999  -99999.999999  -99999.999999  -99999.999999  -99999.999999  -99999.999999  -99999.999999  -99999.999999  -99999.999999  -99999.999999  -99999.999999  -99999.999999  -99999.999999  -99999.999999  
 99.999999   99999.999999   99999.999999   99999.999999   99999.999999   99999.999999   99999.999999   99999.999999   99999.999999   99999.999999   99999.999999   99999.999999   99999.999999   99999.999999   99999.999999   99999.999999

*/

void print_sol_fix_time_to_file()
{
    FILE* file = fopen("fix_time sols.txt", "w+");
    // fprintf(file, "Time%13.1lf%21.1lf%21.1lf%21.1lf%21.1lf       \n", time[time_moments[0]], time[time_moments[1]], time[time_moments[2]], time[time_moments[3]], time[time_moments[4]]);
    // fprintf(file, "         X          U         X          U         X          U         X          U         X          U   \n");
    // for(int m = 0; m < SIZE_X; ++m) {
    //     fprintf(file, "%14.6lf%10.6lf%11.6lf%10.6lf%11.6lf%10.6lf%11.6lf%10.6lf%11.6lf%10.6lf\n", x[m], u[time_moments[0]][m], x[m], u[time_moments[1]][m], x[m], u[time_moments[2]][m], x[m], u[time_moments[3]][m], x[m], u[time_moments[4]][m]);
    // }

    for(int m = 0; m < SIZE_X; ++m) {
        fprintf(file, "%10.6lf%15.6lf%15.6lf%15.6lf%15.6lf%15.6lf%15.6lf%15.6lf%15.6lf%15.6lf%15.6lf%15.6lf%15.6lf%15.6lf%15.6lf%15.6lf\n", x[m], u[time_moments[0]][m], u[time_moments[1]][m], u[time_moments[2]][m], u[time_moments[3]][m], u[time_moments[4]][m], u_lv[time_moments[0]][m], u_lv[time_moments[1]][m], u_lv[time_moments[2]][m], u_lv[time_moments[3]][m], u_lv[time_moments[4]][m], u_tvd[time_moments[0]][m], u_tvd[time_moments[1]][m], u_tvd[time_moments[2]][m], u_tvd[time_moments[3]][m], u_tvd[time_moments[4]][m]);
    }

    fclose(file);
} 