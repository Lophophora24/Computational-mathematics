#ifndef MAIN_H
#define MAIN_H

void fill_x_and_time(void);
void fill_u(void);

void MacCormak(void);
void ObviousNotObvious(void);

void get_e_max_and_e_rms(void);

void print_mu_and_Ar(void);
void print_sol_fix_time_to_file(void);
void print_e_max_and_e_rms(void);

#endif