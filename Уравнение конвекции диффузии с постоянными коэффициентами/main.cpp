#include "main.h"

int main() 
{
    fill_x_and_time();
    fill_u();  

    //------------------------------- 

    MacCorman();
    ObviousNotObvious();

    //------------------------------- 

    print_sol_fix_time_to_file();

    print_mu_and_Ar();

    //------------------------------- 

    //getchar();

    return 0;
}