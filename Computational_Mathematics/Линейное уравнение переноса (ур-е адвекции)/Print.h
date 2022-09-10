#ifndef PRINT_H
#define PRINT_H

#include <stdio.h>
#include "PARAMETRS.h"

double phi(double x);

extern double x[SIZE_X];                       
extern double time[SIZE_T];

extern double u[SIZE_T][SIZE_X];
extern double u_lv[SIZE_T][SIZE_X];
extern double u_tvd[SIZE_T][SIZE_X];

extern double e_max[5][3];
extern double e_rms[5][3];
extern double TV[5][3];
extern int time_moments[5];

#endif