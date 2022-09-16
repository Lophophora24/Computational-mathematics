// Методом обратной интерполяции найти корень
// нелинейного уравнения. Оценить точность
// полученного решения.

#include <stdio.h>

#define STEPS 4

// double data[STEPS][STEPS] = {
//     {   0.5,    0.6,    0.8,     1},
//     {-0.229, -0.205, -0.077, 0.159}
// };

double data[STEPS][STEPS] = {
    {  0.5,    0.6,   0.45,   0.4},
    {0.229, -0.505, -0.677, 0.759}
};

double t[STEPS*(STEPS+1)/2];

double interpolation(double y)
{
    for(int i = 0; i <= STEPS-2; ++i){
        t[i] = (data[0][i] - data[0][i+1]) / (data[1][i] - data[1][i+1]);
    }  
    for(int i = STEPS-1; i <= STEPS; ++i){
        t[i] = (t[i-3] - t[i-2]) / (data[1][i-3] - data[1][i-1]);
    }  
    t[STEPS+1] = (t[3] - t[4]) / (data[1][0] - data[1][3]);

    double res = 0;

    res = data[0][0] + t[0]*(y - data[1][0]) + t[3]*(y - data[1][0])*(y - data[1][1]) + t[5]*(y - data[1][0])*(y - data[1][1])*(y - data[1][2]);

    return res;
}

void print_t()
{
    for(int i = 0; i <= 5; ++i){
        printf("%lf ", t[i]);
    }
    printf("\n");
}

main()
{
    // double x_0 = interpolation(0);

    // printf("x_0 = %lf\n", x_0);
    // printf("t array:\n");
    // print_t();

    for(double y = -1; y <= 1; y+=1e-2){
        printf("%lf      %lf\n", interpolation(y), y);
    }

    getchar();
}
