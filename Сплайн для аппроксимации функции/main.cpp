#include <stdio.h>
#include <math.h>
#include "gauss.h"

#define NUM 5

double data[2][NUM] = {
    {0.3, 2, 3.6, 4, 4.5},
    {3, -4, 3, -6, -4}
};

// double data[2][NUM] = {
//     {0, 1,     2,      3,      4},
//     {0, 0.5, 0.86603, 0.5, 0.86603}
// };

double A(double x, double x_j, double x_j_1)
{
    return (x_j_1 - x) / (x_j_1 - x_j);
}

double B(double x, double x_j, double x_j_1)
{
    return (x - x_j) / (x_j_1 - x_j);
}

double C(double x, double x_j, double x_j_1)
{
    double a = pow(A(x, x_j, x_j_1), 3) - A(x, x_j, x_j_1);
    double b = pow((x_j_1 - x_j), 2);
    return (1./6.)*a*b;
}

double D(double x, double x_j, double x_j_1)
{
    double a = pow(B(x, x_j, x_j_1), 3) - B(x, x_j, x_j_1);
    double b = pow((x_j_1 - x_j), 2);
    return (1./6.)*a*b;
}

double Matr[NUM][NUM];
double f[NUM];
double sec_deriv[NUM];

void fill_Matr_and_f()
{
    double a = 0, b = 0, c = 0, d = 0;
    for(int j = 1; j <= NUM-2; ++j){
        for(int i = j-1; i <= j+1; ++i){
            if(i == j-1){
                Matr[j][i] = (1./6.)*(data[0][j]-data[0][j-1]);
            } else 
            if(i == j){
                Matr[j][i] = (1./3.)*(data[0][j+1]-data[0][j-1]);
            } else
            if(i == j+1){
                Matr[j][i] = (1./6.)*(data[0][j+1]-data[0][j]);
            }
        }
        a = data[1][j+1] - data[1][j];
        b = data[0][j+1] - data[0][j];
        c = data[1][j] - data[1][j-1];
        d = data[0][j] - data[0][j-1];
        f[j] = a/b - c/d;
    }
    Matr[0][0] = 1;
    f[0] = 0;
    Matr[NUM-1][NUM-1] = 1;
    f[NUM-1] = 0;
}

double splain_inter(double x)
{
    double a = 0, b = 0, c = 0, d = 0;
    double res = 0;
    for(int j = 0; j <= NUM-2; ++j){
        if(x >= data[0][j] && x <= data[0][j+1]){
            a = A(x, data[0][j], data[0][j+1]);
            //printf("A = %lf, sec_deriv[%d] = %lf\n", a, j, sec_deriv[j]);
            b = B(x, data[0][j], data[0][j+1]);
            //printf("B = %lf, sec_deriv[%d] = %lf\n", b, j+1, sec_deriv[j+1]);
            c = C(x, data[0][j], data[0][j+1]);
            //printf("C = %lf, sec_deriv[%d] = %lf\n", c, j, sec_deriv[j]);
            d = D(x, data[0][j], data[0][j+1]);
            //printf("D = %lf, sec_deriv[%d] = %lf\n", d, j+1, sec_deriv[j+1]);
            res = a*data[1][j] + b*data[1][j+1] + c*sec_deriv[j] + d*sec_deriv[j+1];
        }
    }
    return res;
}

void print_Matr()
{
    for(int i = 0; i < NUM; ++i){
        for(int j = 0; j < NUM; ++j){
            printf("%lf  ", Matr[i][j]);
        }
        printf("\n");
    }
}

void print_sec_deriv()
{
    for(int i = 0; i < NUM; ++i){
        printf("sec_deriv[%d] = %lf\n", i, sec_deriv[i]);
    }
}

main()
{   
    fill_Matr_and_f();
    //print_Matr();
    gauss(Matr);
    for(double x = 0.3; x <= 4.5; x+=1e-3){
        printf("%lf      %lf\n", x, splain_inter(x));
    }
    // for(double x = 0; x <= 4; x+=1e-3){
    //     printf("%lf      %lf\n", x, splain_inter(x));
    // }

    //print_sec_deriv();

    getchar();
}