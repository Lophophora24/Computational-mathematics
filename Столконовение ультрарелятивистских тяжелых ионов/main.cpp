#include "main.h"

int main(void)
{
    fill_x();
    average_over_conditions();
    print_Y_e_p_to_file();

    unsigned int end_time = clock();
    printf("Time needed: %.3lf sec\n", end_time/1000.);

    return 0;    
}