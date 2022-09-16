#include <stdio.h>

#define h 0.020
#define NUM 100

double x[NUM];
double y[NUM];
double z[NUM];

double f_1(double z)
{
    return z;
} 

double f_2(double y, double z)
{
    return -100 * y - 101 * z;
}

void Euler()
{
    x[0] = 0;
    y[0] = 2;
    z[0] = 10;

    for(int i = 0; i < NUM - 1; ++i){
        x[i+1] = x[i] + h;
        y[i+1] = y[i] + h * f_1(z[i]); 
        z[i+1] = z[i] + h * f_2(y[i], z[i]);
    }    
}

void print_solution() 
{
    for(int i = 0; i < NUM; ++i){
        printf("%10.5f  %10.5f\n", x[i], y[i]);
    }
    printf("\n");
}

int main()
{
    Euler();
    print_solution();

    getchar();
}