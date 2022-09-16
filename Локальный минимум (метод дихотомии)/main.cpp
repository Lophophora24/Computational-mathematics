#include <stdio.h>
#include <math.h>

double f(double x)
{
    return (x - 5)*exp(x);
}

double dihotomia(double (*f)(double), double a, double b)
{
    double u1 = a + (1./3.)*(b - a); 
    double u2 = a + (2./3.)*(b - a); 
    if (abs(u2 - u1) < 1e-5) return (u2 + u1)/2;
    else
    if ((*f)(u1) <= (*f)(u2)) return dihotomia(f, a, u2);
    else 
    if ((*f)(u1) >= (*f)(u2)) return dihotomia(f, u1, b);
    return 0;
}

main()
{
   double inf = dihotomia(f, 0, 10); 
   printf("inf(dihotomia) = %lf\n", inf);

   return 0;
}