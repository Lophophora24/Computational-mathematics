#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>

void fill_x_and_time(void);
void fill_u(void);

void Neyavniy_Leviy_Ugolok(void);
void Laks_Ventroff(void);
void TVD(void);

void get_e_max_and_e_rms(void);
void get_TV(void);

void print_sol(void);
void print_Kurant_number(void);
void print_TV(void);
void print_e_max_and_e_rms(void);
void print_sol_to_file(void);
void print_sol_fix_time_to_file(void);

#endif