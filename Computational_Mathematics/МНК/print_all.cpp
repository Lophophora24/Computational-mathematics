#include <stdio.h>

#define XSIZE 2
#define YSIZE 26
#define NUMOFFUNC 4

extern double A[NUMOFFUNC][NUMOFFUNC];
extern double f[NUMOFFUNC];
extern double x[NUMOFFUNC];
extern int data[XSIZE][YSIZE];

void print_A()
{
    for(int i = 0; i < NUMOFFUNC; ++i){
        for(int j = 0; j < NUMOFFUNC; ++j)
            printf("%lf ", A[i][j]);
        printf("\n");
    }
}

void printf_f()
{
    for(int i = 0; i < NUMOFFUNC; ++i)
        printf("%lf ", f[i]);
    printf("\n");
}

void print_x()
{
    for(int i = 0; i < NUMOFFUNC; ++i)
        printf("%lf ", x[i]);
    printf("\n");
}

void print_data()
{
    for(int i = 0; i < XSIZE; ++i) {
        for(int j = 0; j < YSIZE; ++j)
            printf("%4i ", data[i][j]);
        printf("\n");
    }
}