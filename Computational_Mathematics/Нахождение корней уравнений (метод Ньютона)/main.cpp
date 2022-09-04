#include <stdio.h>
#include <math.h>

double phi(double x)
{
    double res = 0;
    res = x - (3*x + 4*x*x*x - 12*x*x - 5) / (3 + 12*x*x - 24*x);
    return res;
}

main()
{
    double x = 4;
    for(int i = 0; i < 100; ++i){
        x = phi(x);
        printf("%.10lf\n", x);
    }
    return 0;
}