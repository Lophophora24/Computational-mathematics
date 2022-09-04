#include <stdio.h>
#include <math.h>

#define EPS 1e-3

double phi(double y)
{
    double res = 0;

    res = 1.5 - sin(2.5 - cos(y-2));

    return res;
}

main()
{
    double y = 0.5;
    double y_ = y;
    double x = 0;
    y_ = phi(y);
    while (abs(y - y_) > 1e-6) {
        y = y_;
        y_ = phi(y);
        //printf("%.10lf\n", y);
    }

    x = 0.5 - cos(y-2);

    printf("x = %.3lf, y = %.3lf\n", x, y);
    
}