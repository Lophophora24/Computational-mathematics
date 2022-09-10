#include "main.h"

int main()
{
    
    fill_x_and_time();
    fill_u();  

    //------------------------------- 

    Neyavniy_Leviy_Ugolok();

    Laks_Ventroff();

    TVD();

    //------------------------------- 

    //print_sol();

    get_e_max_and_e_rms();

    print_e_max_and_e_rms();

    get_TV();

    print_TV();

    print_Kurant_number();

    //------------------------------- 

    print_sol_to_file();

    print_sol_fix_time_to_file();

    //------------------------------- 

    getchar();

    return 0;
}