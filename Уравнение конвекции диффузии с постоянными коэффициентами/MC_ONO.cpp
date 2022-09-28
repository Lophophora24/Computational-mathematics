#include "MC_ONO.h"

double x[SIZE_X];                        // пространственный отрезок
double time[SIZE_T];                     // временной отрезок

double phi(double t_, double x_, double t0_) 
{
    if ((t_ > 0) || (t0_ > 0)) {
        double arg0 = sqrt(4*D*(t_ + t0_));
        double arg1 = a_ - x_ + v*t_;
        double arg2 = a_ + x_ - v*t_;
        return 0.5*(erf(arg1/arg0) + erf(arg2/arg0));
    } 
    else 
    if ((t_ == 0) && (t0_ == 0)) {
        if (abs(x_) <= a_) {
            return 1;
        } else
        if (abs(x_) > a_) {
            return 0;
        }    
    }
    return 0;
}

void fill_x_and_time()
{
    for(int i = 0; i < SIZE_X; ++i)
        x[i] = a + h * i;
    for(int i = 0; i < SIZE_T; ++i)
        time[i] = t * i;
}

double u_MC[SIZE_T][SIZE_X];
double u_ONO[SIZE_T][SIZE_X];

void fill_u()
{
    for(int i = 0; i < SIZE_X; ++i)
        for(int j = 0; j < SIZE_T; ++j) {
           u_MC[j][i]  = 0; 
           u_ONO[j][i] = 0;
        }

    for(int i = 0; i < SIZE_X; ++i){
        u_MC[0][i]  = phi(0, x[i], t0);
        u_ONO[0][i] = phi(0, x[i], t0);
    }           
        
    for(int i = 0; i < SIZE_T; ++i) {
        // u_MC[i][0]  = phi(time[i], x[0], t0);
        // u_ONO[i][0] = phi(time[i], x[0], t0);
        u_MC[i][0]  = 0;
        u_ONO[i][0] = 0;
    }
}

void MacCormak()
{
    for(int n = 0; n < SIZE_T; ++n) {
        u_MC[n][0] = 0;
        u_MC[n][1] = phi(time[n], x[1], t0);
        u_MC[n][SIZE_X-2] = phi(time[n], x[SIZE_X-2], t0);
        u_MC[n][SIZE_X-1] = 0;
    }
    
    for(int n = 0; n < SIZE_T - 1; ++n) {
        for(int m = 2; m <= SIZE_X-3; ++m) {
            double u_j       = u_MC[n][m]   - r*v*(u_MC[n][m+1] - u_MC[n][m])   + mu*(u_MC[n][m+1] - 2*u_MC[n][m]   + u_MC[n][m-1]);
            double u_j_plus  = u_MC[n][m+1] - r*v*(u_MC[n][m+2] - u_MC[n][m+1]) + mu*(u_MC[n][m+2] - 2*u_MC[n][m+1] + u_MC[n][m]);
            double u_j_minus = u_MC[n][m-1] - r*v*(u_MC[n][m]   - u_MC[n][m-1]) + mu*(u_MC[n][m]   - 2*u_MC[n][m-1] + u_MC[n][m-2]);
            u_MC[n+1][m] = 0.5*(u_MC[n][m] + u_j) - r/2*v*(u_j - u_j_minus) + mu/2*(u_j_plus - 2*u_j + u_j_minus);
        }
    }
}

void ObviousNotObvious()
{
    for(int n = 0; n < SIZE_T; ++n) {
        u_ONO[n][SIZE_X-1] = 0;
    }

    for(int n = 0; n < SIZE_T - 1; ++n) {
        double A[SIZE_X]; A[1] = 0;
        double B[SIZE_X]; B[1] = u_ONO[n+1][0];

        for(int j = 1; j < SIZE_X - 1; ++j) {
            A[j+1] = mu / (1 + 2*mu - mu*A[j]);
            B[j+1] = (r*u_ONO[n][j-1] + (1-r)*u_ONO[n][j] + mu*B[j]) / (1 + 2*mu - mu*A[j]);
        }

        for(int j = SIZE_X-2; j > 0; --j) {
            u_ONO[n+1][j] = A[j+1]*u_ONO[n+1][j+1] + B[j+1];
        }
    }

}

int time_moments[5] = {
    (int)(0 * SIZE_T / 5),
    (int)(1 * SIZE_T / 5),
    (int)(2 * SIZE_T / 5),
    (int)(3 * SIZE_T / 5),
    (int)(4.5 * SIZE_T / 5),
};

double e_max[5][2] = {{0, 0}, };
double e_rms[5][2] = {{0, 0}, };

void get_e_max_and_e_rms()
{
    for(int l = 0; l < 2; ++l) {
        for(int k = 0; k < 5; ++k) {
            for(int m = 0; m < SIZE_X; ++m) {
                double diff = 0;
                if (l == 0) {
                    diff = abs( u_MC[time_moments[k]][m] - phi(time[time_moments[k]], x[m], t0) );    
                } else if (l == 1) {
                    diff = abs( u_ONO[time_moments[k]][m] - phi(time[time_moments[k]], x[m], t0) );    
                }
                
                e_max[k][l] = __max(e_max[k][l], diff);   

                e_rms[k][l] += (diff * diff);
            }

            e_rms[k][l] = sqrt( e_rms[k][l] / SIZE_X );
        }
    }
}