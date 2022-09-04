#include "NLU_LV_TVD.h"

#define h 0.001             // шаг по координате
#define t 0.001             // шаг по времени

#define c 0.5               // константа скорости в уравнении переноса

#define eta c*t/h           // число Куранта

#define delta 1             // константа в начальной функции

#define a 0                 // начало пространственного отрезка
#define b 0.2               // конец  пространственного отрезка

#define T 0.2               // конец временного отрезка ( начало в 0 )

#define SIZE_X (int)((b - a) / h)        // кол-во ячеек в дискретном пространственном отрезке
#define SIZE_T (int)((T - 0.) / t)       // кол-во ячеек в дискретном временном отрекзе

double x[SIZE_X];                        // пространственный отрезок
double time[SIZE_T];                     // временной отрезок

double phi (double x) 
{
    if (x <= 0) 
        return 1;
    else 
        return exp(-(x * x) / (delta * delta)); 
}

void fill_x_and_time()
{
    for(int i = 0; i < SIZE_X; ++i)
        x[i] = a + h * i;
    for(int i = 0; i < SIZE_T; ++i)
        time[i] = t * i;
}

double u[SIZE_T][SIZE_X];

void fill_u()
{
    for(int i = 0; i < SIZE_X; ++i)
        for(int j = 0; j < SIZE_T; ++j)
            u[j][i] = 0;

    for(int i = 0; i < SIZE_X; ++i)           
        u[0][i] = phi(x[i]);

    for(int i = 0; i < SIZE_T; ++i)
        u[i][0] = phi(x[0] - c * time[i]);
}

void Neyavniy_Leviy_Ugolok()
{
    for(int n = 1; n < SIZE_T; ++n) {
        for(int m = 1; m < SIZE_X; ++m) {
            u[m][n] = (u[m][n-1] + eta * u[m-1][n]) / (1 + eta); 
            //printf("n = %d, m = %d\n", n, m);
        }
    }
}

void Laks_Ventroff()
{
    double f_m_minus_arr[SIZE_T];

    for(int n = 1; n < SIZE_T; ++n) {
        f_m_minus_arr[n] = c * ( u[0][n-1] + ( u[1][n-1] - u[0][n-1] ) * (( 1 - eta ) / 2) );
    }

    for(int m = 1; m < SIZE_X - 1; ++m) {
        for(int n = 1; n < SIZE_T; ++n) {
            double f_m_plus = c * ( u[m][n-1] + ( u[m+1][n-1] - u[m][n-1] ) * (( 1 - eta ) / 2) );
            double f_m_minus = f_m_minus_arr[n];
            u[m][n] = u[m][n-1] - (t / h) * (f_m_plus - f_m_minus);
        }
    }
}

double psi(int m, int n)
{
    double q_m = (u[m][n] - u[m-1][n]) / (u[m+1][n] - u[m][n]);
    return __max(0, __max(__min(1, 2*q_m), __min(2, q_m)));
}

void TVD()
{
    double f_m_minus_arr[SIZE_T];

    for(int n = 1; n < SIZE_T; ++n) {
        f_m_minus_arr[n] = c * ( u[0][n-1] + ( u[1][n-1] - u[0][n-1] ) * (( 1 - eta ) / 2) * psi(0, n));
    }

    for(int m = 1; m < SIZE_X - 1; ++m) {
        for(int n = 1; n < SIZE_T; ++n) {
            double f_m_plus = c * ( u[m][n-1] + ( u[m+1][n-1] - u[m][n-1] ) * (( 1 - eta ) / 2) * psi(m, n));
            double f_m_minus = f_m_minus_arr[n];
            u[m][n] = u[m][n-1] - (t / h) * (f_m_plus - f_m_minus);
        }
    }    
}

/*
----------------------------------------------------------
 ( x , t ) |    Computer solution    |    Exact solution  
 (334,  4) |         102.455657      |      122.465879      


*/

void print_sol()
{
    printf("----------------------------------------------------------\n");
    printf(" ( x , t ) |    Computer solution    |    Exact solution  \n");
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