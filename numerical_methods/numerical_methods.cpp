// numerical_methods.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <array>

using namespace std;

double f(double x) {
    return x * x;
}

double* ff(double* u, float t) {
    double phi = u[0];
    double omega = u[1];
    double g = 9.81; double l = 1;

    double res[2] = {0., 0.};
    res[0] = omega;
    res[1] = -g / l * phi;
    return res;
}


void print_to_txt(vector <double> t, vector <double> res) {
    // Функция для печати массивов в .txt. Сначала в стоблец вектор t, затем res
    std::ofstream out;          // поток для записи
    out.open("hello.txt");      // открываем файл для записи
    if (out.is_open())
    {
        for (int i = 0; i < t.size(); i++) {
            out << t[i] << "\t" << res[i] << std::endl;
        }
    }
    out.close();
    std::cout << "File has been written" << std::endl;
}

struct ODE_res {
    // Структура для возврата результа интегирования функции ODE_newton
    vector <double> t;
    vector <double> u;
};

ODE_res ODE_newton(double(*f)(double x), double u0, double t0, double T) {
    // Функция решает линейное дифференциальное уравнение методом Ньютона 
    // Входные параметры:
    // f - функция, возвращающая праву часть
    // u0  - начальное условие
    // t0, T - время интегрирования
    ODE_res res;

    int N_MAX = 200;
    double dt = (T - t0) / static_cast <double>(N_MAX);

    res.t.push_back(t0);
    res.u.push_back(u0);

    double next_u = u0;
    double next_t = t0;
    for (int i = 1; i < N_MAX + 1; i++) {
        next_u = res.u[i - 1] + dt * f(res.t[i - 1]);
        next_t = next_t + dt;
        res.u.push_back(next_u);
        res.t.push_back(next_t);
    }
    return res;    
}



int main()
{
    ODE_res res;
    res = ODE_newton(f, 1, 0, 30);
    
    print_to_txt(res.t, res.u);
 
    
 
}

