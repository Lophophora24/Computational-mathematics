#ifndef PARAMETRS_H
#define PARAMETRS_H

#define h 0.006             // шаг по координате
#define t 0.002             // шаг по времени

#define v 1                 // константы в уравнении
#define D 0.004

#define r t/h
#define mu (D*t/(h*h))

#define t0 0.2                // константы в начальном условии
#define a_  0.2

#define a -1                // начало пространственного отрезка
#define b 5                 // конец  пространственного отрезка

#define T 4                 // конец временного отрезка ( начало в 0 )

#define SIZE_X (int)((b - a) / h)        // кол-во ячеек в дискретном пространственном отрезке
#define SIZE_T (int)((T - 0.) / t)       // кол-во ячеек в дискретном временном отрекзе

#endif