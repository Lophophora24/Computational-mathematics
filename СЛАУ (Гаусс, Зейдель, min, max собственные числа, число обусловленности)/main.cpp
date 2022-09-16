#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <string.h>

#define DIM 20
#define NUM_OF_ITER 500

double A[DIM+1][DIM+1] = {0.0};
double A_[DIM+1][DIM+1] = {0.0}; // обратная матрица

double D[DIM+1][DIM+1] = {0.0};
double L[DIM+1][DIM+1] = {0.0};
double U[DIM+1][DIM+1] = {0.0};

double f[DIM+1] = {0.0};
double x[DIM+1] = {0.0};
double nev[DIM+1] = {0.0};
double x_z[DIM+1] = {0.0};
double nev_z[DIM+1] = {0.0};
double x_z0[DIM+1] = {0, 12353, 3532};      // начальный вектор x для Зейделя

void init(void);

void fill_A(void);
void fill_A_(void);
void fill_DLU(void);

void print_A(void);
void print_A_(void);
void print_f(void);
void print_x(void);
void print_x_and_nev(void);
void print_x_z(void);
void print_x_z_and_nev_z(void);
void print_x_z0(void);

void gauss(double A[][DIM+1]);
void zeidel(double A[][DIM+1]);

double eig_max(double A[][DIM+1]);
double eig_min(double A[][DIM+1]);

double mult(double *, double *);
double * mult(double [][DIM+1], double *, double *);

main()
{

    init();
    
    //getchar();
}

void print_help()
{
    printf( "gauss   :    run the gauss method,\n"
            "zeidel  :    run the zeidel method,\n"
            "eig_max :    run the search for the max eigenvalue\n"
            "eig_min :    run the search for the min eigenvalue\n"
            "find_mu :    find the number of conditionality\n"
            "show_A  :    show the A  matrix,\n"
            "show_A_ :    show the A_ matrix,\n"
            "exit    :    for exit\n"
            "help    :    for help\n"
            );    
}

void init()
{
    char option[10] = {};
    printf("Choose the option...\n");
    print_help();
    while (scanf("%s", option) && strcmp(option, "exit")){
        if (!strcmp(option, "gauss")) {
            printf("----------------------GAUSS METHOD PROCESSING------------------------\n");
            fill_A();
            gauss(A);
            print_x_and_nev();
            printf("---------------------------------------------------------------------\n");
        } else if (!strcmp(option, "zeidel")) {
            printf("----------------------ZEIDEL METHOD PROCESSING-----------------------\n");
            fill_A();
            zeidel(A);
            print_x_z_and_nev_z();
            printf("---------------------------------------------------------------------\n");
        } else if (!strcmp(option, "eig_max")){
            printf("----------------------MAX EIGVALUE PROCESSING------------------------\n");
            fill_A();
            double _eig_max = eig_max(A);
            printf("Max eigenvalue: %lf\n", _eig_max);
            printf("---------------------------------------------------------------------\n");
        } else if (!strcmp(option, "eig_min")){
            printf("----------------------MIN EIGVALUE PROCESSING------------------------\n");
            fill_A();
            fill_A_();
            double _eig_min = eig_min(A);
            printf("Min eigenvalue: %lf\n", _eig_min);
            printf("---------------------------------------------------------------------\n");
        } else if (!strcmp(option, "find_mu")) {
            printf("---------------------NUMBER OF CONDITIONALITY------------------------\n");
            fill_A();
            fill_A_();
            double _eig_min = eig_min(A);
            double _eig_max = eig_max(A);
            double mu = _eig_max / _eig_min;
            printf("Number of conditionality: %lf\n", mu);
            printf("---------------------------------------------------------------------\n");
        } else if (!strcmp(option, "show_A")) {
            printf("---------------------------------------------------------------------\n");
            print_A();
            printf("---------------------------------------------------------------------\n");
        } else if (!strcmp(option, "show_A_")) {
            printf("---------------------------------------------------------------------\n");
            fill_A();
            fill_A_();
            fill_A();
            print_A_();
            printf("---------------------------------------------------------------------\n");
        } else if (!strcmp(option, "help")) {
            print_help();
        } else {
            printf("Error! Try another input...\n");
            print_help();
        }
    }
}

void fill_A()
{
    int _abs = 0;
    for(int i = 1; i <= DIM; ++i){
        f[i] = i;
        for(int j = 1; j <= DIM; ++j) {
            _abs = abs(i-j);
            A[i][j] = _abs <= 2 ? pow(10, 1-_abs) : 0;
        }
    }
}

void fill_A_()
{
    for(int j = 1; j <= DIM; ++j) {
        for(int k = 1; k <= DIM; ++k)
            f[k] = 0;
        f[j] = 1;
        gauss(A);
        fill_A();
        for(int i = 1; i <= DIM; ++i) {
            A_[i][j] = x[i];
        }
    }
}

void fill_DLU()
{
    for(int i = 1; i <= DIM; ++i)
        for(int j = 1; j <= DIM; ++j) {
            if (i > j)       L[i][j] = A[i][j];
            else if (i < j)  U[i][j] = A[i][j];
            else if (i == j) D[i][j] = A[i][j];
        }
}

void print_A()
{
    printf("\nA = (\n");
    for(int i = 1; i <= DIM; ++i) {
        for(int j = 1; j <= DIM; ++j) 
            printf("%3.1lf ", A[i][j]);
        printf("\n");
    }
    printf(")\n");
}

void print_A_()
{
    printf("\nA_ = (\n");
    for(int i = 1; i <= DIM; ++i) {
        for(int j = 1; j <= DIM; ++j) 
            printf("%7.3lf ", A_[i][j]);
        printf("\n");
    }
    printf(")\n");
}

void print_f()
{
    printf("\nf = (\n");
    for(int i = 1; i < DIM; ++i)
        printf("%lf,\n", f[i]);
    printf("%lf\n)\n", f[DIM]);
}

double summ(int line_num)
{
    double res = 0;
    for(int j = DIM; j > line_num; --j)
        res += A[line_num][j]*x[j];
    return res;
}

double summ_z(int line_num)
{
    double res = 0;
    for(int j = 1; j <= DIM; ++j)
        res += A[line_num][j] * x_z[j];
    return (res - A[line_num][line_num] * x_z[line_num]);
}

void solve_triangle_system(double A[][DIM+1])
{
    for(int i = DIM; i > 0; --i){
        assert(A[i][i] != 0);
        x[i] = (f[i] - summ(i)) / A[i][i];
    }    
}

void substr_lines_mult(int line_1, int line_2, double mul)
{
    for(int j = 1; j <= DIM; ++j){
        A[line_1][j] -= A[line_2][j] * mul;
    }
    f[line_1] -= f[line_2] * mul;
}

void div_line(int line_num, double div)
{
    assert(div != 0);
    for(int j = 1; j <= DIM; ++j)
        A[line_num][j] /= div;
    f[line_num] /= div;
}

void make_matrix_triangle(double A[][DIM+1])
{
    for(int i = 1; i <= DIM; ++i) {
       div_line(i, A[i][i]);
       for(int k = i+1; k <= DIM; ++k) {
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

void gauss(double A[][DIM+1])
{
    make_matrix_triangle(A);
    solve_triangle_system(A);

    double res[DIM+1] = {0.0};
    mult(A, x, res);
    for(int i = 1; i <= DIM; ++i)
        nev[i] = res[i] - f[i];
}

void zeidel(double A[][DIM+1])
{
    for(int i = 1; i <= DIM; ++i)
        x_z[i] = x_z0[i];
    for(int k = 1; k <= NUM_OF_ITER; ++k) {
        for(int i = 1; i <= DIM; ++i) {
            x_z[i] = (f[i] - summ_z(i)) / A[i][i];
        }
    }

    double res[DIM+1] = {0.0};
    mult(A, x_z, res);
    for(int i = 1; i <= DIM; ++i)
        nev_z[i] = res[i] - f[i];
}

double mult(double vec1[], double vec2[])
{
    double res = 0;
    for(int i = 1; i <= DIM; ++i)
        res += vec1[i] * vec2[i];
    return res;
}

double* mult(double matr[][DIM+1], double vec[], double res[])
{
    //double res[DIM+1] = {0};
    for(int i = 1; i <= DIM; ++i) {
        res[i] = mult(*matr + i*(DIM+1), vec);
    }
    return res;
}

double eig_max(double A[][DIM+1])
{
    double eig_val_max = 0;
    double u[DIM+1] = {12, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001};
    double res[DIM+1] = {0};
    for(int i = 1; i <= NUM_OF_ITER; ++i) {
        assert(mult(u, u));
        eig_val_max = mult(mult(A, u, res), u) / mult(u, u);
        for(int j = 1; j <= DIM; ++j)
            u[j] = res[j] / (sqrt(mult(u, u)));
    }
    return eig_val_max;
}

double eig_min(double A[][DIM+1])
{
    double eig_val_min = 0;
    eig_val_min = eig_max(A_);
    return eig_val_min;
}

void print_x()
{
    printf("\nx = (\n");
    for(int i = 1; i < DIM; ++i)
        printf("%lf,\n", x[i]);
    printf("%lf\n)\n", x[DIM]);
}

void print_x_and_nev()
{
    printf("\nx = (          nev = (\n");
    for(int i = 1; i < DIM; ++i)
        printf("%lf,      %.25lf,\n", x[i], nev[i]);
    printf("%lf       %.25lf\n", x[DIM], nev[DIM]);
    printf(")              )\n");
}

void print_x_z()
{
    printf("\nx_z = (\n");
    for(int i = 1; i < DIM; ++i)
        printf("%lf,\n", x_z[i]);
    printf("%lf\n)\n", x_z[DIM]);    
}

void print_x_z_and_nev_z()
{
    printf("\nx_z = (        nev_z = (\n");
    for(int i = 1; i < DIM; ++i)
        printf("%lf,      %.25lf,\n", x_z[i], nev_z[i]);
    printf("%lf       %.25lf\n", x_z[DIM], nev_z[DIM]);
    printf(")              )\n");    
}

void print_x_z0()
{
    printf("\nx_z0 = (\n");
    for(int i = 1; i < DIM; ++i)
        printf("%lf,\n", x_z0[i]);
    printf("%lf\n)\n", x_z0[DIM]);    
}