#ifndef PRINT_H
#define PRINT_H

#include <stdio.h>
#include "PARAMETRS.h"


extern double x[SIZE_X];                       
extern double time[SIZE_T];

extern double u_MC[SIZE_T][SIZE_X];
extern double u_ONO[SIZE_T][SIZE_X];

extern int time_moments[5];

extern double e_max[5][2];
extern double e_rms[5][2];

#endif