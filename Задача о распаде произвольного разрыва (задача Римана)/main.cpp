#include "main.h"

int main()
{
    
    fill();
    fill_T();

    Laks_Vendroff();

    print_sol_fix_time_to_file();

    find_parametrs_analitically();

    return 0;
}