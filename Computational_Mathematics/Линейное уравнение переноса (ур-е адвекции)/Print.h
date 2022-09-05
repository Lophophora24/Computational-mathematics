#ifndef PRINT_H
#define PRINT_H

#include <stdio.h>
#include "PARAMETRS.h"

double phi(double x);

void print_sol(void);
void print_Kurant_number(void);
void print_TV(void);
void print_e_max_and_e_rms(void);
void print_sol_to_file(void);

extern double x[SIZE_X];                       
extern double time[SIZE_T];

extern double u[SIZE_T][SIZE_X];

extern double e_max[5];
extern double e_rms[5];
extern double TV[5];
extern int time_moments[5];

#endif