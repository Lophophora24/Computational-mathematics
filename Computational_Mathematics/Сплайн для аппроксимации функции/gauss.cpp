#include <assert.h>
#include <stdio.h>

#define NUM 5

extern double Matr[NUM][NUM];
extern double f[NUM];
extern double sec_deriv[NUM];

double summ(int line_num)
{
    double res = 0;
    for(int j = NUM - 1; j > line_num; --j)
        res += Matr[line_num][j]*sec_deriv[j];
    return res;
}

void solve_triangle_system(double A[][NUM])
{
    for(int i = NUM - 1; i >= 0; --i){
        assert(A[i][i] != 0);
        sec_deriv[i] = (f[i] - summ(i)) / A[i][i];
    }    
}

void substr_lines_mult(int line_1, int line_2, double mul)
{
    for(int j = 0; j < NUM; ++j){
        Matr[line_1][j] -= Matr[line_2][j] * mul;
    }
    f[line_1] -= f[line_2] * mul;
}

void div_line(int line_num, double div)
{
    //printf("line num = %d, div = %lf\n", line_num, div);
    assert(div != 0);
    for(int j = 0; j < NUM; ++j)
        Matr[line_num][j] /= div;
    f[line_num] /= div;
}

void make_matrix_triangle(double A[][NUM])
{
    for(int i = 0; i < NUM; ++i) {
       div_line(i, A[i][i]);
       for(int k = i+1; k < NUM; ++k) {
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

void gauss(double A[][NUM])
{
    make_matrix_triangle(A);
    solve_triangle_system(A);
}