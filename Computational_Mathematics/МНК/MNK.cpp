#define XSIZE 2
#define YSIZE 26
#define NUMOFFUNC 4

extern int data[XSIZE][YSIZE];

double sum_x_k()
{
    double res = 0;
    for(int i = 0; i < YSIZE; ++i)
        res += data[0][i];
    return res;
}

double sum_x_k_2()
{
    double res = 0;
    for(int i = 0; i < YSIZE; ++i)
        res += data[0][i] * data[0][i];
    return res;
}

double sum_y_k()
{
    double res = 0;
    for(int i = 0; i < YSIZE; ++i)
        res += data[1][i];
    return res;
}

double sum_x_k_y_k()
{
    double res = 0;
    for(int i = 0; i < YSIZE; ++i)
        res += data[0][i] * data[1][i];
    return res;
}

double * find_MNK_params()
{
    static double params[2] = {0, 0};

    params[0] = (YSIZE*sum_x_k_y_k() - sum_x_k()*sum_y_k()) / (YSIZE*sum_x_k_2() - sum_x_k()*sum_x_k());

    params[1] = (sum_y_k()*sum_x_k_2() - sum_x_k_y_k()*sum_x_k()) / (YSIZE*sum_x_k_2() - sum_x_k()*sum_x_k());

    return params;
}