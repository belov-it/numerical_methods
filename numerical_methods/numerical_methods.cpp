// numerical_methods.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <fstream>
#include <cmath>
#include <vector>

#include <Eigen/Dense>
#include "ODE_Solver.h"

double f(double x);
Eigen::Matrix <float, 2, 1> ff(Eigen::Matrix <float, 2, 1> u);


int main()
{
    // Call 1D ode solver
    ODE_Solver ode1D;
    ODE_res_1D res1D;
    res1D = ode1D.newton_method_1D(f, 1, 0, 20);
    write_to_txt_1D(res1D.t, res1D.u);


    // initial condition 2D
    Eigen::Matrix <float, 2, 1> u0;
    u0 << 3.14 / 6, 0;
    float t0 = 0;
    float T = 3 * 3.14;

    ODE_Solver ode2D;
    ODE_res_2D res2D;
    res2D = ode2D.newton_method_2D(ff, u0, t0, T);
    write_to_txt_2D(res2D.t, res2D.u);
}

double f(double x) {
    return x * x;
}

Eigen::Matrix <float, 2, 1> ff(Eigen::Matrix <float, 2, 1> u) {
    // Right-hand side of the differential equation of the pendulum
    double phi = u(0);
    double omega = u(1);
    double g = 9.81; double l = 1;

    Eigen::Matrix <float, 2, 1> res;
    res(0) = omega;
    res(1) = -g / l * phi;
    return res;
}
