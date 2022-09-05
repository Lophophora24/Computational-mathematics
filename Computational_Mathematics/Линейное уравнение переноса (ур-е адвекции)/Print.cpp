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
   Time       e_max       e_rms
  3.4576    0.457638    0.785674
*/

void print_e_max_and_e_rms()
{
    printf("---------------------------------\n");
    printf("   Time       e_max       e_rms\n");
    printf("---------------------------------\n");
    for(int k = 0; k < 5; ++k) {
        printf("%8.4lf%12.6lf%12.6lf\n", time[time_moments[k]], e_max[k], e_rms[k]);
    }
    printf("---------------------------------\n");
    printf("\n");
}

/*
   Time        TV
  3.4576    0.457638
*/

void print_TV()
{
    printf("---------------------\n");
    printf("   Time        TV\n");
    printf("---------------------\n"); 
    for(int k = 0; k < 5; ++k) {
        printf("%8.4lf%12.6lf\n", time[time_moments[k]], TV[k]);
    } 
    printf("---------------------\n");
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