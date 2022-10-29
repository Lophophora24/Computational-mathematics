#include "Crank_Nicolson.h"

double x   [SIZE_X];
double time[SIZE_T];

double c   [SIZE_X];
double ro  [SIZE_X];
double k   [SIZE_X];
double q   [SIZE_X];

double T0(double x) 
{
    if (x < b) return 310;
    else return 300;
}

void fill()
{
    for(int i = 0; i < SIZE_X; ++i) {
        x[i] = (i-0.5)*h;
        SET_PARAMS(i)
    }

    for(int i = 0; i < SIZE_T; ++i)
        time[i] = t * i;
}

double T_CN[SIZE_T][SIZE_X];

void fill_T()
{
    for(int i = 0; i < SIZE_X; ++i) {
        T_CN[0][i] = T0(x[i]);
        for(int j = 1; j < SIZE_T; ++j) 
            T_CN[j][i] = 0;
    }

}

void Crank_Nicolson()
{
    for(int m = 0; m < SIZE_T-1; ++m) {
        double A[SIZE_X]; A[1] = 1;
        double B[SIZE_X]; B[1] = 0;

        for(int i = 2; i < SIZE_X; ++i) {
            double a_ = -(k[i-1]*(i-2)) / (2*h*h*(i-1.5));
            double b_ = (c[i-1]*ro[i-1]) / t + (k[i]*(i-1) + k[i-1]*(i-2)) / (2*h*h*(i-1.5));
            double c_ = -(k[i]*(i-1)) / (2*h*h*(i-1.5));
            double f_ = -a_ * T_CN[m][i-2] + (2*c[i-1]*ro[i-1]/t - b_) * T_CN[m][i-1] -c_ * T_CN[m][i] + (q[i-1] + q[i-1]) / 2; 

            A[i] = -c_ / (a_*A[i-1] + b_);
            B[i] = (f_ - a_*B[i-1]) / (a_*A[i-1] + b_);
        }

        double a_ = -k[SIZE_X-1]/h + alpha/2;
        double b_ =  k[SIZE_X-1]/h + alpha/2;
        double f_ = alpha*TT; 
        double g_ = -sigma;     //g_ = 0;

        double prev_temp = 100;
        while (abs(T_CN[m+1][SIZE_X-1] - prev_temp) > 1e-10) {

            prev_temp = T_CN[m+1][SIZE_X-1];
            T_CN[m+1][SIZE_X-1] = (-B[SIZE_X-1]*a_ + f_ + g_*pow((T_CN[m+1][SIZE_X-1] + T_CN[m+1][SIZE_X-2])/2, 4)) / (A[SIZE_X-1]*a_ + b_);

            for(int n = SIZE_X-1; n >= 1; --n)
                T_CN[m+1][n-1] = A[n]*T_CN[m+1][n] + B[n];

        }

        // if (m == SIZE_T-2) {
        //     printf("i = 1, test_solution = %lf\n", T_CN[m+1][0] - T_CN[m+1][1]);
        //     for(int i = 2; i < SIZE_X; ++i) {
        //         double a_ = -(k[i-1]*(i-2)) / (2*h*h*(i-1.5));
        //         double b_ = (c[i-1]*ro[i-1]) / t + (k[i]*(i-1) + k[i-1]*(i-2)) / (2*h*h*(i-1.5));
        //         double c_ = -(k[i]*(i-1)) / (2*h*h*(i-1.5));
        //         double f_ = -a_ * T_CN[m][i-2] + (2*c[i-1]*ro[i-1]/t - b_) * T_CN[m][i-1] -c_ * T_CN[m][i] + (q[i-1] + q[i-1]) / 2;
        //         double test_solution = a_*T_CN[m+1][i-2]+b_*T_CN[m+1][i-1]+c_*T_CN[m+1][i]-f_;
        //         printf("i = %d, test_solution = %lf\n", i, test_solution);
        //     } 
        //     double a_ = -k[SIZE_X-1]/h + alpha/2;
        //     double b_ =  k[SIZE_X-1]/h + alpha/2;
        //     double f_ = alpha*TT; 
        //     double g_ = -sigma; //g_ = 0;
        //     printf("i = %d, test_solution = %lf\n", SIZE_X, a_*T_CN[m+1][SIZE_X-2]+b_*T_CN[m+1][SIZE_X-1]-f_-g_*pow((T_CN[m+1][SIZE_X-2]+T_CN[m+1][SIZE_X-1])/2, 4));
        // }     
    }    
}

int time_moments[5] = {
    (int)(0    * SIZE_T / 5), 
    (int)(0.625 * SIZE_T / 5), 
    (int)(1.25  * SIZE_T / 5),
    (int)(2.5   * SIZE_T / 5),
    (int)(5  * SIZE_T / 5 - 1),
};

