#include "main.h"

int main()
{
    fill();
    fill_phi();

    Strauss_Vazquez();

    print_sol_fix_time_to_file();

    return 0;
}