#include "main.h"

int main()
{
    
    fill();
    fill_T();

    Crank_Nicolson();

    print_sol_fix_time_to_file();

    return 0;
}