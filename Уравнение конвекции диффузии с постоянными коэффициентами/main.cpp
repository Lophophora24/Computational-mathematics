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

    //------------------------------- 

    //getchar();

    return 0;
}