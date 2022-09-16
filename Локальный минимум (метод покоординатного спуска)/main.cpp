#include <stdio.h>
#include <math.h>

double x_0 = 5;
double y_0 = 5;

double dihotomia(double (*f)(double, double), double a, double b, double var)
{
    double u1 = a + (1./3.)*(b - a); 
    double u2 = a + (2./3.)*(b - a);

    if (var == 1){
        if (abs(u2 - u1) < 1e-5) return (u2 + u1)/2;
        else
        if ((*f)(u1, y_0) <= (*f)(u2, y_0)) return dihotomia(f, a, u2, 1);
        else 
        if ((*f)(u1, y_0) >= (*f)(u2, y_0)) return dihotomia(f, u1, b, 1);
        return 0;
    } else if (var == 2){
        if (abs(u2 - u1) < 1e-5) return (u2 + u1)/2;
        else
        if ((*f)(x_0, u1) <= (*f)(x_0, u2)) return dihotomia(f, a, u2, 2);
        else 
        if ((*f)(x_0, u1) >= (*f)(x_0, u2)) return dihotomia(f, u1, b, 2);
        return 0;
    }
    return 0;
}

void koord_spusk(double (*f)(double, double))
{
    double x0 = 0, y0 = 0;
    for(int i = 0; i < 10; ++i){
        x0 = dihotomia(f, 0, 10, 1);
        x_0 = x0;
        y0 = dihotomia(f, 0, 10, 2);
        y_0 = y0;
    } 
}

double f(double x, double y)
{
    return x*x*x + 8*y*y*y - 6*x*y + 1;
}

double f1(double x, double y)
{
    return (x*x + y*y - 1)*(x*x + y*y - 1) + (y - x*sin(x))*(y - x*sin(x));
}

main()
{
    koord_spusk(f1);
    
    printf("x = %.5lf, y = %.5lf\n", x_0, y_0);

    return 0;
}