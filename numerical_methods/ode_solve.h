
#include <vector>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

struct ODE_res {
    // Structure for returning the result 1D of the ODE solver
    vector <double> t;
    vector <double> u;
};

struct ODE_res_2D {
    // Structure for returning the result 1D of the ODE solver
    Matrix <float, 100, 1> t;
    Matrix <float, 100, 2> u;
};



ODE_res_2D ODE_newton_2D(Matrix <float, 2, 1>(*f)(Matrix <float, 2, 1> x), Matrix <float, 2, 1> u0, float t0, float T) {
    ODE_res_2D res;

    int N = 100; // Count of iteration
    float dt = (T - t0) / static_cast <float> (N);

    // Add initial condition
    res.t(0) = t0;
    for (int i = 0; i < 2; i++) {
        res.u(0, i) = u0(i);
    }

    // Temporary storage of function result
    Matrix <float, 2, 1> f_tmp;

    for (int m = 1; m < N; m++) {

        f_tmp = f(res.u.row(m - 1));
        for (int i = 0; i < 2; i++) {
            res.u(m, i) = res.u(m - 1, i) + dt * f_tmp(i);
        }
        res.t(m) = res.t(m - 1) + dt;
    }

    return res;
}

ODE_res ODE_newton(double(*f)(double x), double u0, double t0, double T) {
    // Solve 1D ODE using newton method
    // Params:
    // f - Right-hand side of the differential equation
    // u0  - Initial condition
    // t0, T - Integration time
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