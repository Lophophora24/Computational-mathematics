#ifndef PARAMETRS_H
#define PARAMETRS_H

#define h 0.001     // шаг по координате
#define t 0.0001     // шаг по времени

//------------------------------------------------//

#define a -0.5       
#define b 0.5       

#define T 0.2      // конец временного промежутка (начало в 0)

//--------------Константы в уравнении-------------//

#define u1 0     // скорость
#define u2 1      

#define ro1 0.8   // плотность
#define ro2 1.2

#define p1 0.7       // давление
#define p2 0.9

#define g 1.4         // показатель адиабаты

#define q 0.1        // параметр сглаживания

#define SET_PARAMS(i) \
    if (x[i] < 0) {   \
        u[i] = u1;    \
        ro[i] = ro1;  \
        p[i] = p1;    \
    } else {          \
        u[i] = u2;    \
        ro[i] = ro2;  \
        p[i] = p2;    \
    }

//------------------------------------------------//

#define N (b - a)/h     // число ячеек            

#define SIZE_X (int)(N)          // размер массива координат
#define SIZE_T (int)((T - 0.) / t)   // размер массива времени

#endif
