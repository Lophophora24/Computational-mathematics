#include "NLU_LV_TVD.h"

int main()
{
    
    fill_x_and_time();
    fill_u();   

    //Neyavniy_Leviy_Ugolok();

    //Laks_Ventroff();

    TVD();

    print_sol();

    print_Kurant_number();


    getchar();

    return 0;
}