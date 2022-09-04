#include <assert.h>

#define NUMOFFUNC 4

extern double A[NUMOFFUNC][NUMOFFUNC];
extern double f[NUMOFFUNC];
extern double x[NUMOFFUNC];

double summ(int line_num)
{
    double res = 0;
    for(int j = NUMOFFUNC - 1; j > line_num; --j)
        res += A[line_num][j]*x[j];
    return res;
}

void solve_triangle_system(double A[][NUMOFFUNC])
{
    for(int i = NUMOFFUNC - 1; i >= 0; --i){
        assert(A[i][i] != 0);
        x[i] = (f[i] - summ(i)) / A[i][i];
    }    
}

void substr_lines_mult(int line_1, int line_2, double mul)
{
    for(int j = 0; j < NUMOFFUNC; ++j){
        A[line_1][j] -= A[line_2][j] * mul;
    }
    f[line_1] -= f[line_2] * mul;
}

void div_line(int line_num, double div)
{
    assert(div != 0);
    for(int j = 0; j < NUMOFFUNC; ++j)
        A[line_num][j] /= div;
    f[line_num] /= div;
}

void make_matrix_triangle(double A[][NUMOFFUNC])
{
    for(int i = 0; i < NUMOFFUNC; ++i) {
       div_line(i, A[i][i]);
       for(int k = i+1; k < NUMOFFUNC; ++k) {
           substr_lines_mult(k, i, A[k][i]);
       } 
    }

    
/*
    for(int i = 1; i <= DIM; ++i) {
        for(int j = 1; j <= DIM; ++j)
            A[i][j] /= A[i][i];
        f[i] /= div;
        for(int k = i+1; k <= DIM; ++k) {
            for(int j = k; j <= DIM; ++j)
                A[k][j] -= A[i][j] * A[k][i];
            f[k] -= f[i] * A[k][i];
        }
    }
*/
}

void gauss(double A[][NUMOFFUNC])
{
    make_matrix_triangle(A);
    solve_triangle_system(A);
}