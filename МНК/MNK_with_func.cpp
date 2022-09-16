#include "gauss.h"

#define XSIZE 2
#define YSIZE 26
#define NUMOFFUNC 4

extern int data[XSIZE][YSIZE];

extern double A[NUMOFFUNC][NUMOFFUNC];
extern double f[NUMOFFUNC];
extern double x[NUMOFFUNC];
extern double (*func[NUMOFFUNC]) (double);



double func_1(double x)
{
    if (x >= 20 && x <= 28)
        return (28 - x) / 8;
    else 
        return 0;
}

double func_2(double x)
{
    if (x >= 20 && x <= 28)
        return (x - 20) / 8;
    else if (x > 28 && x <= 39)
        return (39 - x) / 11;
    else 
        return 0;
}

double func_3(double x)
{
    if (x >= 28 && x <= 39)
        return (x - 28) / 11;
    else if (x > 39 && x <= 45)
        return (45 - x) / 6;
    else 
        return 0;
}

double func_4(double x)
{
    if (x >= 39 && x <= 45)
        return (x - 39) / 6;
    else    
        return 0;
}

double func_mult(double (*f1)(double), double (*f2)(double))
{
    double res = 0;
    for(int i = 0; i < YSIZE; ++i)
        res += (*f1)(data[0][i]) * (*f2)(data[0][i]);
    return res;
}

double func_mult_by_f(double (*f)(double))
{
    double res = 0;
    for(int i = 0; i < YSIZE; ++i)
        res += (*f)(data[0][i]) * data[1][i];
    return res;
}

void fill_func()
{
    func[0] = func_1;
    func[1] = func_2;
    func[2] = func_3;
    func[3] = func_4;
}

void fill_A_and_f()
{
    for(int i = 0; i < NUMOFFUNC; ++i) {
        for(int j = 0; j < NUMOFFUNC; ++j)
            A[i][j] = func_mult(func[i], func[j]);
        f[i] = func_mult_by_f(func[i]);
    }
}

double * find_MNK_f_params()
{
    static double params[NUMOFFUNC] = {0, 0, 0, 0};

    fill_func();
    fill_A_and_f();

    gauss(A);

    for(int i = 0; i < NUMOFFUNC; ++i)
        *(params+i) = x[i];
    
    return params;
}

double res_MNK_func(double arg)
{
    double res = 0;

    for(int i = 0; i < NUMOFFUNC; ++i){
        res += x[i] * (*(func[i]))(arg);
    }

    return res;
    
}