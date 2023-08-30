// numerical_methods.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

#include <Eigen/Dense>
#include "ode_solve.h"

using namespace std;
using namespace Eigen;


double f(double x) {
    return x * x;
}

Matrix <float, 2, 1> ff(Matrix <float, 2, 1> u) {
    // Right-hand side of the differential equation of the pendulum
    double phi = u(0);
    double omega = u(1);
    double g = 9.81; double l = 1;

    Matrix <float, 2, 1> res;
    res(0) = omega;
    res(1) = -g / l * phi;
    return res;
}


void print_to_txt(vector <double> t, vector <double> res) {
    // Function writes array's data to .txt file
    std::ofstream out;          // поток для записи
    out.open("results1D.txt");      // открываем файл для записи
    if (out.is_open())
    {
        for (int i = 0; i < t.size(); i++) {
            out << t[i] << "\t" << res[i] << std::endl;
        }
    }
    out.close();
    std::cout << "File has been written" << std::endl;
}



int main()
{
    // Call 1D ode solver
    ODE_res res1D;
    res1D = ODE_newton(f, 1, 0, 30);
    
    print_to_txt(res1D.t, res1D.u);

    // Call 2D ode solver (pendulum)
    ODE_res_2D res2D;
    // initial condition
    Matrix <float, 2, 1> u0;
    u0 << 3.14 / 6, 0;
    float t0 = 0;
    float T = 3 * 3.14;

    res2D = ODE_newton_2D(ff, u0, t0, T);
 
   // Write data to .txt
    ofstream out;         
    out.open("results2D.txt");     
    if (out.is_open())
    {
        for (int i = 0; i < 100; i++) {
            out << res2D.t(i) << "\t" << res2D.u(i,0) << std::endl;
        }
    }
    out.close();
    cout << "File has been written" << std::endl;

 
}

