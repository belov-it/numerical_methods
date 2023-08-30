#pragma once
#include <vector>
#include <Eigen/Dense>

#include <fstream>
#include <iostream>


struct ODE_res_1D {
	// Structure for returning the result 1D of the ODE solver
	std::vector <double> t;
	std::vector <double> u;
};

struct ODE_res_2D {
	// Structure for returning the result 1D of the ODE solver
	Eigen::Matrix <float, 100, 1> t;
	Eigen::Matrix <float, 100, 2> u;
};


class ODE_Solver
{
private:
	int dimension;

public:
	
	ODE_res_1D newton_method_1D(double(*f)(double x), double u0, double t0, double T);
	ODE_res_2D newton_method_2D(Eigen::Matrix <float, 2, 1>(*f)(Eigen::Matrix <float, 2, 1> x),
		Eigen::Matrix <float, 2, 1> u0, float t0, float T);

};

void write_to_txt_1D(std::vector <double> t, std::vector <double> res);
void write_to_txt_2D(Eigen::Matrix <float, 100, 1> t, Eigen::Matrix <float, 100, 2> u);

