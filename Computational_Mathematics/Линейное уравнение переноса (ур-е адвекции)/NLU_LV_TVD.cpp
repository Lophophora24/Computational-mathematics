#include "NLU_LV_TVD.h"

double x[SIZE_X];                        // пространственный отрезок
double time[SIZE_T];                     // временной отрезок

double phi (double x) 
{
    if (x <= 0) 
        return 1;
    else 
        return exp(-(x * x) / (delta * delta)); 
}

void fill_x_and_time()
{
    for(int i = 0; i < SIZE_X; ++i)
        x[i] = a + h * i;
    for(int i = 0; i < SIZE_T; ++i)
        time[i] = t * i;
}

double u[SIZE_T][SIZE_X];
double u_lv[SIZE_T][SIZE_X];
double u_tvd[SIZE_T][SIZE_X];

void fill_u()
{
    for(int i = 0; i < SIZE_X; ++i)
        for(int j = 0; j < SIZE_T; ++j) {
           u[j][i]     = 0; 
           u_lv[j][i]  = 0;
           u_tvd[j][i] = 0;
        }
            

    for(int i = 0; i < SIZE_X; ++i){
        u[0][i]     = phi(x[i]);
        u_lv[0][i]  = phi(x[i]);
        u_tvd[0][i] = phi(x[i]);
    }           
        

    for(int i = 0; i < SIZE_T; ++i) {
        u[i][0]     = phi(x[0] - c * time[i]);
        u_lv[i][0]  = phi(x[0] - c * time[i]);
        u_tvd[i][0] = phi(x[0] - c * time[i]);
    }
        
}

void Neyavniy_Leviy_Ugolok()
{
    for(int n = 1; n < SIZE_T; ++n) {
        for(int m = 1; m < SIZE_X; ++m) {
            u[n][m] = (u[n-1][m] + eta * u[n][m-1]) / (1 + eta); 
            //printf("n = %d, m = %d\n", n, m);
        }
    }
}

void Laks_Ventroff()
{
    for(int n = 1; n < SIZE_T; ++n) {
        for(int m = 1; m < SIZE_X - 1; ++m) {
            double f_m_plus = c * ( u_lv[n-1][m] + ( u_lv[n-1][m+1] - u_lv[n-1][m] ) * (( 1 - eta ) / 2) );
            double f_m_minus = c * ( u_lv[n-1][m-1] + ( u_lv[n-1][m] - u_lv[n-1][m-1] ) * (( 1 - eta ) / 2) );
            u_lv[n][m] = u_lv[n-1][m] - (t / h) * (f_m_plus - f_m_minus);    
        }
    }

    // Функцию на конце отрезка построим по точному решению
    for(int n = 1; n < SIZE_T; ++n) {
        u_lv[n][SIZE_X-1] = phi(x[SIZE_X-1] - c * time[n]);
    }
}

double psi(int n, int m)
{
    if (u_tvd[n-1][m+1] - u_tvd[n-1][m] == 0) return 2;
    double q_m = (u_tvd[n-1][m] - u_tvd[n-1][m-1]) / (u_tvd[n-1][m+1] - u_tvd[n-1][m]);
    return __max(0, __max(__min(1, 2*q_m), __min(2, q_m)));
}

void TVD()
{
    for(int n = 1; n < SIZE_T; ++n) {
        for(int m = 1; m < SIZE_X - 1; ++m) {
            double f_m_plus = c * ( u_tvd[n-1][m] + ( u_tvd[n-1][m+1] - u_tvd[n-1][m] ) * (( 1 - eta ) / 2) * psi(n, m));
            double f_m_minus = c * ( u_tvd[n-1][m-1] + ( u_tvd[n-1][m] - u_tvd[n-1][m-1] ) * (( 1 - eta ) / 2) * psi(n, m-1));
            u_tvd[n][m] = u_tvd[n-1][m] - (t / h) * (f_m_plus - f_m_minus);    
        }
    } 

    // Функцию на конце отрезка построим по точному решению
    for(int n = 1; n < SIZE_T; ++n) {
        u_tvd[n][SIZE_X-1] = phi(x[SIZE_X-1] - c * time[n]);
    }
}

double e_max[5][3] = {{0, 0, 0}, };
double e_rms[5][3] = {{0, 0, 0}, };
double TV[5][3] = {{0, 0, 0}, };
int time_moments[5] = {
    (int)(0 * SIZE_T / 5),
    (int)(1 * SIZE_T / 5),
    (int)(2 * SIZE_T / 5),
    (int)(3 * SIZE_T / 5),
    (int)(4.5 * SIZE_T / 5),
};

void get_e_max_and_e_rms()
{
    for(int l = 0; l < 3; ++l) {
        for(int k = 0; k < 5; ++k) {
            for(int m = 0; m < SIZE_X; ++m) {
                double diff = 0;
                if (l == 0) {
                    diff = abs( u[time_moments[k]][m] - phi(x[m] - c * time[time_moments[k]]) );    
                } else if (l == 1) {
                    diff = abs( u_lv[time_moments[k]][m] - phi(x[m] - c * time[time_moments[k]]) );    
                } else if (l == 2) {
                    diff = abs( u_tvd[time_moments[k]][m] - phi(x[m] - c * time[time_moments[k]]) );    
                }
                
                e_max[k][l] = __max(e_max[k][l], diff);   

                e_rms[k][l] += (diff * diff);
            }

            e_rms[k][l] = sqrt( e_rms[k][l] / SIZE_X );
        }
    }
}

void get_TV()
{
    for(int l = 0; l < 3; ++l) {
        for(int k = 0; k < 5; ++k) {
            for(int m = 0; m < SIZE_X - 1; ++m) {
                if (l == 0) {
                    TV[k][l] += abs(u[time_moments[k]][m+1] - u[time_moments[k]][m]);
                } else if (l == 1) {
                    TV[k][l] += abs(u_lv[time_moments[k]][m+1] - u_lv[time_moments[k]][m]);
                } else if (l == 2) {
                    TV[k][l] += abs(u_tvd[time_moments[k]][m+1] - u_tvd[time_moments[k]][m]);
                }
            }
        }    
    }
    
}

