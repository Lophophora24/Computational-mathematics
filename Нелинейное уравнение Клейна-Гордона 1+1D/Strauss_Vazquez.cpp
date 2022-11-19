#include "Strauss_Vazquez.h"

double x[SIZE_X];
double time[SIZE_T];

double phi_0(double x)
{
    return (1 + cos(2*3.1415*x/b)) * 0.1;
}

double d_phi_0(double x)
{
    return 0;
}

void fill()
{
    for(int i = 0; i < SIZE_X; ++i)
        x[i] = i*h;
    for(int i = 0; i < SIZE_T; ++i)
        time[i] = i*t;
}

double phi[SIZE_T][SIZE_X];

void fill_phi()
{
    for(int i = 0; i < SIZE_X; ++i) {
        for(int j = 1; j < SIZE_T; ++j)
            phi[j][i] = 0.2;
        phi[0][i] = phi_0(x[i]);
        phi[1][i] = phi_0(x[i]) + d_phi_0(x[i])*h;
    }
}

double F(int j, int i) 
{
    return m*m*phi[j][i]*phi[j][i]/2 + g*phi[j][i]*phi[j][i]*phi[j][i]*phi[j][i]/4;
}

void Strauss_Vazquez()
{
    for(int j = 1; j < SIZE_T-1; ++j) {
        for(int i = 1; i < SIZE_X-1; ++i) {
            double recent = 100;
            while (abs(recent-phi[j+1][i]) > 1e-4) {
                recent = phi[j+1][i];
                phi[j+1][i] = r*r*phi[j][i-1] + 2*(1-r*r)*phi[j][i] + r*r*phi[j][i+1] - phi[j-1][i] - t*t*(F(j+1, i) - F(j-1, i)) / (phi[j+1][i] - phi[j-1][i]);
            }
        }
    }
}

int time_moments[5] = {
    (int)(0    * SIZE_T / 5), 
    (int)(0.625 * SIZE_T / 5), 
    (int)(1.25  * SIZE_T / 5),
    (int)(2.5   * SIZE_T / 5),
    (int)(5  * SIZE_T / 5 - 1),    
};