#include "Laks_Vendroff.h"

double x   [SIZE_X];
double time[SIZE_T];

double u   [SIZE_X];
double ro  [SIZE_X];
double p   [SIZE_X];
double e   [SIZE_X];

void fill()
{
    for(int i = 0; i < SIZE_X; ++i) {
        x[i] = i*h/(b-a)-0.5;
        SET_PARAMS(i)
    }

    for(int i = 0; i < SIZE_T; ++i)
        time[i] = t * i;
}

std::vector<double> f[SIZE_T][SIZE_X];
std::vector<double> F[SIZE_T][SIZE_X];

double pressure[SIZE_T][SIZE_X];             //!!!!!!!!!!!!!!!!!!!!!!!!!!!!

std::vector<double> F_(int j, int i) {
    double ro = f[j][i].at(0);
    double U = f[j][i].at(1);
    double E = f[j][i].at(2);
    double p = (E - U*U/2/ro)*(g-1);
    std::vector<double> res = {U, U*U/ro+p, U/ro*(E+p)};

    return res;
}

void fill_T()
{
    for(int i = 0; i < SIZE_X; ++i) {
        for(int j = 0; j < SIZE_T; ++j) { 
            double E = p[i]/(g-1)+ro[i]*u[i]*u[i]/2;
            f[j][i] = {ro[i], ro[i]*u[i], E};
            F[j][i] = F_(j, i);

            pressure[j][i] = (f[j][i].at(2) - f[j][i].at(1)*f[j][i].at(1)/2/f[j][i].at(0))*(g-1);
        }
    }
}

std::vector<double> operator+(std::vector<double> v1, const std::vector<double>& v2)
{
    for(unsigned int i = 0; i<v1.size(); i++)
    {
        v1[i] += v2[i];
    }
    return v1;
}

std::vector<double> operator-(std::vector<double> v1, const std::vector<double>& v2)
{
    for(unsigned int i = 0; i<v1.size(); i++)
    {
        v1[i] -= v2[i];
    }
    return v1;
}

std::vector<double> operator*(std::vector<double> v1, double x)
{
    for(unsigned int i = 0; i<v1.size(); i++)
    {
        v1[i] *= x;
    }
    return v1;
}

std::vector<double> operator/(std::vector<double> v1, double x)
{
    for(unsigned int i = 0; i<v1.size(); i++)
    {
        v1[i] /= x;
    }
    return v1;
}

void Laks_Vendroff()
{
    for(int j = 0; j < SIZE_T-1; ++j) {
        for(int i = 1; i < SIZE_X-1; ++i) {
            std::vector<double> f_plus = (f[j][i+1]+f[j][i])*0.5 - (F[j][i+1]-F[j][i])*t/2/h;
            std::vector<double> f_mins = (f[j][i]+f[j][i-1])*0.5 - (F[j][i]-F[j][i-1])*t/2/h;

            double rop = f_plus.at(0);
            double Up = f_plus.at(1);
            double Ep = f_plus.at(2);
            double pp = (Ep-Up*Up/2/rop)*(g-1);
            double rom = f_mins.at(0);
            double Um = f_mins.at(1);
            double Em = f_mins.at(2);
            double pm = (Em-Um*Um/2/rom)*(g-1);

            std::vector<double> F_plus = {Up, Up*Up/rop+pp, Up/rop*(Ep+pp)};
            std::vector<double> F_mins = {Um, Um*Um/rom+pm, Um/rom*(Em+pm)};

            f[j+1][i] = f[j][i] - (F_plus - F_mins)*t/h;
            F[j+1][i] = F_(j+1, i);

            pressure[j+1][i] = (f[j+1][i].at(2) - f[j+1][i].at(1)*f[j+1][i].at(1)/2/f[j+1][i].at(0))*(g-1); 

            //printf("ro = %lf, U = %lf, E = %lf\n", f[j+1][i].at(0), f[j+1][i].at(1), f[j+1][i].at(2)); 
        }

        for(int i = 2; i < SIZE_X-2; ++i) {
            double r_1 = f[j+1][i-1].at(0);
            double r_2 = f[j+1][i-2].at(0);
            double r_0 = f[j+1][i].at(0);
            double r2  = f[j+1][i+2].at(0);
            double r1  = f[j+1][i+1].at(0);

            double D_MM = r_1 - r_2, D_M = r_0 - r_1;
            double D_P = r1 - r_0, D_PP = r2 - r1;

            std::vector<double> Q_m, Q_p; 

            if (D_MM*D_M <= 0 || D_M*D_P <= 0) 
                Q_m = f[j+1][i] - f[j+1][i-1];
            else 
                Q_m = {0, 0, 0};
            
            if (D_M*D_P <= 0 || D_P*D_PP <= 0)
                Q_p = f[j+1][i+1] - f[j+1][i];
            else 
                Q_p = {0, 0, 0};
            
            f[j+1][i] = f[j+1][i] + (Q_p - Q_m)*q;
            F[j+1][i] = F_(j+1, i);

            pressure[j+1][i] = (f[j+1][i].at(2) - f[j+1][i].at(1)*f[j+1][i].at(1)/2/f[j+1][i].at(0))*(g-1);
        }
    }           
}

void Mc_Cormack()
{
    for(int j = 0; j < SIZE_T-1; ++j) {
        for(int i = 1; i < SIZE_X-1; ++i) {
            std::vector<double> f_ = f[j][i] - (F[j][i+1] - F[j][i])*t/h;  // это f_i с чертой
            std::vector<double> f__ = f[j][i-1] - (F[j][i] - F[j][i-1])*t/h; // это f_{i-1} с чертой

            double ro = f_.at(0);                  // это компоненты первого f
            double U = f_.at(1);
            double E = f_.at(2);
            double p = (E-U*U/2/ro)*(g-1);         // заодно можем давление посчитать

            double ro_ = f__.at(0);                // это компоненты второго f
            double U_ = f__.at(1);
            double E_ = f__.at(2);
            double p_ = (E_-U_*U_/2/ro_)*(g-1);    // и тут тоже давление посчитаем

            std::vector<double> F__ = {U, U*U/ro+p, U/ro*(E+p)};   // это F_i с чертой
            std::vector<double> F___ = {U_, U_*U_/ro_+p_, U_/ro_*(E_+p_)}; // а это F_{i-1} с чертой

            f[j+1][i] = (f[j][i] + f_)*0.5 - (F__ - F___)*t/2/h;
            F[j+1][i] = F_(j+1, i);                // это заполнение F, он весь выражается через f, ф-я где-то наверху

            pressure[j+1][i] = (f[j+1][i].at(2) - f[j+1][i].at(1)*f[j+1][i].at(1)/2/f[j+1][i].at(0))*(g-1); // это давление на j+1 временном слое в точке i, оно у меня в отдельном двумерном массиве хранится


        }

        for(int i = 2; i < SIZE_X-2; ++i) {
            double r_1 = f[j+1][i-1].at(0);
            double r_2 = f[j+1][i-2].at(0);
            double r_0 = f[j+1][i].at(0);
            double r2  = f[j+1][i+2].at(0);
            double r1  = f[j+1][i+1].at(0);

            double D_MM = r_1 - r_2, D_M = r_0 - r_1;
            double D_P = r1 - r_0, D_PP = r2 - r1;

            std::vector<double> Q_m, Q_p; 

            if (D_MM*D_M <= 0 || D_M*D_P <= 0) 
                Q_m = f[j+1][i] - f[j+1][i-1];
            else 
                Q_m = {0, 0, 0};
            
            if (D_M*D_P <= 0 || D_P*D_PP <= 0)
                Q_p = f[j+1][i+1] - f[j+1][i];
            else 
                Q_p = {0, 0, 0};
            
            f[j+1][i] = f[j+1][i] + (Q_p - Q_m)*q;
            F[j+1][i] = F_(j+1, i);     // после уточнения

            pressure[j+1][i] = (f[j+1][i].at(2) - f[j+1][i].at(1)*f[j+1][i].at(1)/2/f[j+1][i].at(0))*(g-1); // после уточнения
        }
    }    
}

double a1(double P) 
{
    return sqrt(ro1/2*((g+1)*P+(g-1)*p1));
}

double a2(double P)
{
    return sqrt(ro2/2*((g+1)*P+(g-1)*p2));
}

double phi(double P) 
{
    return (a2(P)*p1+a1(P)*p2+a1(P)*a2(P)*(u1-u2)) / (a1(P)+a2(P));
}

void find_parametrs_analitically()
{
    double P0 = 0.5*(p1+p2);
    double recent = 100;
    double P = 0;
    while (abs(P - recent) > 1e-8) {
        recent = P;
        P = phi(P);
    } 
    double U = (a1(P)*u1+a2(P)*u2+p1-p2) / (a1(P)+a2(P)); 
    double R1 = ro1*((g+1)*P+(g-1)*p1)/((g-1)*P+(g+1)*p1); 
    double R2 = ro2*((g+1)*P+(g-1)*p2)/((g-1)*P+(g+1)*p2);
    double D1 = u1 - a1(P)/ro1;
    double D2 = u2 + a2(P)/ro2;

    printf("\n|| -----------------------------------||\n");
    printf("|| Pressure P             = %9.3lf ||\n", P); 
    printf("|| Velocity U             = %9.3lf ||\n", U); 
    printf("|| Density left R1        = %9.3lf ||\n", R1); 
    printf("|| Density right R2       = %9.3lf ||\n", R2); 
    printf("|| Velocity left wave D1  = %9.3lf ||\n", D1); 
    printf("|| Velocity right wave D2 = %9.3lf ||\n", D2);
    printf("|| -----------------------------------||\n\n");
}

int time_moments[5] = {
    (int)(0    * SIZE_T / 5), 
    (int)(1 * SIZE_T / 4), 
    (int)(2  * SIZE_T / 4),
    (int)(3   * SIZE_T / 4),
    (int)(4 * SIZE_T / 4 - 1),
};






