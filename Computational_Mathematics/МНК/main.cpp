#include <stdio.h>
#include <assert.h>

#include "gauss.h"
#include "MNK.h"
#include "MNK_with_func.h"
#include "print_all.h"

#define XSIZE 2
#define YSIZE 26
#define NUMOFFUNC 4

int data[XSIZE][YSIZE] = {
    { 20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,   42,   43,   44,   45},
    {431, 409, 429, 422, 530, 505, 459, 499, 526, 563, 587, 595, 647, 669, 746, 760, 778, 828, 846, 836, 916, 956, 1014, 1076, 1134, 1024}
};

double A[NUMOFFUNC][NUMOFFUNC] = {0};
double f[NUMOFFUNC] = {0};
double x[NUMOFFUNC] = {0};
double (*func[NUMOFFUNC]) (double) = {NULL};

main()
{
    double * MNK_par = find_MNK_params();
    double * MNK_f_par = find_MNK_f_params();

    printf("MNK params: a = %lf, b = %lf\n", *MNK_par, *(MNK_par+1));

    printf("MNK with base functions. Result function:\n");
    for(double i = 20; i <= 45; i += 1e-2){
        printf("%lf    %lf\n", i, res_MNK_func(i));
    }

    getchar();

    return 0;
}