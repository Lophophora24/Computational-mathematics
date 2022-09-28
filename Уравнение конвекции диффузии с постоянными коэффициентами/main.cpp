#include "main.h"

int main() 
{
    fill_x_and_time();
    fill_u();  

    //------------------------------- 

    MacCormak();
    ObviousNotObvious();

    //------------------------------- 

    get_e_max_and_e_rms();

    print_sol_fix_time_to_file();

    print_mu_and_Ar();

    print_e_max_and_e_rms();

    //------------------------------- 

    //getchar();

    return 0;
}