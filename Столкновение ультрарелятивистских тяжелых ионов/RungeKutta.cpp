#include "RungeKutta.h"

double x[T_SIZE] = {0, };          // t

double y[T_SIZE] = {0, };          // y(t)
double y_[T_SIZE] = {0, };         // (dy/dt)(t)

double Wigner_func(double alpha, double p)
{
    return exp(-(alpha-A)*(alpha-A)/(alpha0*alpha0) - (p*p)/(p0*p0)) / PI;        
}

void fill_x()
{
    for(int n = 0; n < T_SIZE-1; ++n)
        x[n+1] = x[n] + h;           
}

void init(double y0, double y_0)
{ 
    y[0] = y0;
    y_[0] = y_0;
}

double f(double x, double y, double y_) 
{
    return y_;
}

double f_(double x, double y, double y_)
{
    return -l/6 * y * y * y;
}

void rk2()
{
    for(int n = 0; n < T_SIZE-1; ++n) {
        double k1 = h * f(x[n], 0, y_[n]);
        double k2 = h * f(x[n] + h/2, 0, y_[n] + k1/2); 
        y[n+1] = y[n] + k2;

        double k1_ = h * f_(x[n], y[n], 0);
        double k2_ = h * f_(x[n] + h/2, y[n] + k1_/2, 0); 
        y_[n+1] = y_[n] + k2_;     
    }    
}

void rk4()
{
    for(int n = 0; n < T_SIZE-1; ++n) {
        double k1 = h * f(x[n], 0, y_[n]);
        double k2 = h * f(x[n] + h/2, 0, y_[n] + k1/2);
        double k3 = h * f(x[n] + h/2, 0, y_[n] + k2/2);
        double k4 = h * f(x[n] + h, 0, y_[n] + k3); 
        y[n+1] = y[n] + 1./6*k1 + 1./3*k2 + 1./3*k3 + 1./6*k4;

        double k1_ = h * f_(x[n], y[n], 0);
        double k2_ = h * f_(x[n] + h/2, y[n] + k1_/2, 0); 
        double k3_ = h * f_(x[n] + h/2, y[n] + k2_/2, 0);
        double k4_ = h * f_(x[n] + h, y[n] + k3_, 0);
        y_[n+1] = y_[n] + 1./6*k1_ + 1./3*k2_ + 1./3*k3_ + 1./6*k4_;     
    }  
}

void solve_with_these_conditions(double y0, double y_0)
{
    init(y0, y_0);
    rk4();    
}

//-------------------------------------------------------------------------------//

double get_random_number_with_normal_distribution(double mean, double deviation)
{
    return 0;
}

double e[T_SIZE] = {0, };
double p[T_SIZE] = {0, };

void average_over_conditions()
{
    std::random_device rd{};
    std::mt19937 gen{rd()}; 
    std::normal_distribution<> d1(A, alpha0);  
    std::normal_distribution<> d2(0, p0); 

    for(int i = 0; i < N; ++i) {
        double y0 = d1(gen);
        double y_0 = d2(gen);
        double w = Wigner_func(y0, y_0);
        solve_with_these_conditions(y0, y_0);

        for(int t = 0; t < T_SIZE; ++t) {
            e[t] += (y_[t]*y_[t]/2 + l*y[t]*y[t]*y[t]*y[t]/24)/N;
            p[t] += (y_[t]*y_[t]/2 - l*y[t]*y[t]*y[t]*y[t]/24)/N;
        }
    }   
}

