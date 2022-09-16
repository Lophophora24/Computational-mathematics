#include <stdio.h>
#include <conio.h>

#define MAX_VAL 20

void get_input(void);
double gorner(int, int*, double);

int N = 0, coeff[MAX_VAL] = {0}, 
coeff_sp[10] = {-1*512, 9*256, -36*128, 84*64, -126*32, 126*16, -84*8, 36*4, -9*2, 1};
double x = 2;

main(void)
{
    //get_input();
    //double res = gorner(N, coeff, x);
    //printf("Result = %lf\n", res);

    double a = 1.99;   // 1.92
    double res = 0;
    while (a <= 2.01){ // 2.08
        res = gorner(10, coeff_sp, a);
        //printf("%lf    %.15lf\n", a, res);
        a += 1e-4;
    }

    getchar();

    //double res = gorner(10, coeff_sp, x);
    //printf("(x - 2)^9 = %lf\n", res);
}

void get_input()
{
    int i;
    scanf("%d", &N);
    for(i = 0; i < N; ++i)
        scanf("%d", coeff + i);
    scanf("%lf", &x);
}

double gorner(int N, int* coeff, double x)
{
    double p = coeff[N];
    printf("x = %lf\n", x);
    printf("--------------------------------------------------\n");
    for (int j = N-1; j >= 0; --j) {
        //printf("p = %lf\n", p);
        printf("coeff[%d] = %d\n", j, coeff[j]);
        printf("p_old = %.15lf\n", p);
        p = x*p + coeff[j];
        printf("p_new = %.15lf\n", p);
    }
    printf("--------------------------------------------------\n");
    return p;
}