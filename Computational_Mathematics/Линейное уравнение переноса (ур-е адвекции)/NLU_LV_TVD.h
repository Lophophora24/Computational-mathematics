#ifndef NLU_LV_TVD_H
#define NLU_LV_TVD_H

/*
-------------------------------
| NLU | Neyavniy Leviy Ugolok |
| LV  | Laks Ventroff         |
| TVD | TVD method            |
-------------------------------
*/

#include <math.h>
#include "PARAMETRS.h"

void fill_x_and_time(void);
void fill_u(void);

void Neyavniy_Leviy_Ugolok(void);
void Laks_Ventroff(void);
void TVD(void);

void get_e_max_and_e_rms(void);
void get_TV(void);

#endif