//Eulers method
//given initial value problem, y'(x) = f(x, y(x)), y(x_0) = y_0, Step-size, # of steps

#include <iostream>
#include <vector>
#include <Eigen/Dense>

using namespace std;
using Eigen::MatrixXd;

template<typename vecType,typename func>
vecType eulerStep(vecType y_n, func f, double stepSize, double t) {
    return y_n + stepSize*f(t, y_n);
};
//note f vector valued funtion n -> n where n is size of y_n

template<typename vecType, typename func>
void euler(vecType y0, func f, double stepSize, int N, vector<vecType>& data, vector<vecType>& error) {//y0: vector of initial values; f: vector of derivative expresions; 
//N: number of steps; sysSize: number of OEDs in the system, assumes t0 = 0
    vecType y_n = y0;
//Write approximation to data parameter
    for (int i = 0; i < N; i++) {
        data.push_back(y_n);
        y_n = eulerStep(y_n, f, stepSize, i*stepSize);
    }

//Calculate error and write to the error parameter
    vector<vecType> halfSteps;
    y_n = y0;
    for (int i = 0; i < N*2; i++) {
        halfSteps.push_back(y_n);
        y_n = eulerStep(y_n, f, stepSize/2, i*stepSize/2);
    }

    for (int i = 0; i < N; i++) {
        error.push_back((halfSteps[i*2] - data[i])/(4-1));
    }
    
    
};