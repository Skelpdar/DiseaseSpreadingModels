#include <iostream>
#include <fstream>
#include <Eigen/Dense>
#include <vector>
#include <string>
#include <exception>

#include <rungeKutta.h>
#include <euler.h>

using Eigen::MatrixXd;
using Eigen::Vector2d;
using Eigen::Vector3d;

using namespace Eigen;

double beta = 0.07;
double alpha = 0.05;

Vector2d SIS(double tn, Vector2d y){
    Vector2d v;

    v(0) = -beta*y(0,0)*y(1,0)/(y(0,0)+y(1,0))+alpha*v(1,0);
    v(1) = beta*y(0,0)*y(1,0)/(y(0,0)+y(1,0))-alpha*v(1,0);

    return v;

}

//The SIR model, includes resistant population and vacination of suseptible pop, N = S + I + R
double SIRInfec = 0.1;
double SIRRec = 0.05;
double SIRVac = 0.001;

//vector function for the derivatives of S, I & R respectively, y = (S, I, R), tn for generality
Vector3d SIR(double tn, Vector3d y) {
    Vector3d derivatives;
    double S = y(0,0);
    double I = y(1,0);
    double R = y(2,0);
    double N = S + I + R;

    derivatives(0) = -SIRInfec*S*I/N - SIRVac*S;
    derivatives(1) = SIRInfec*S*I/N - SIRRec*I;
    derivatives(2) = SIRVac*S + SIRRec*I;

    return derivatives;
}


int main(){
/*  
    Vector2d y0;
    y0(0) = 70;
    y0(1) = 30;

    std::vector<Vector2d> data;
    std::vector<Vector2d> error;
 
    euler(y0, SIS, 10, 100, data, error);
    std::ofstream SISFile;
    SISFile.open("SISSolutionEuler.txt");

    for(int i=0; i<data.size(); i++){
        SISFile << data[i] << std::endl;
        SISFile << error[i] << std::endl;
    }

    SISFile.close();
*/
    //test for euler method

    Vector3d y0;
    y0(0) = 70;
    y0(1) = 30;
    y0(2) = 0;

    std::vector<Vector3d> data;
    std::vector<Vector3d> error;
 
    rungeKutta(y0, SIR, 10, 100, data, error);
    std::ofstream SIRFile;
    SIRFile.open("SIRSolution.txt");

    for(int i=0; i<data.size(); i++){
        SIRFile << data[i] << std::endl;
        SIRFile << error[i] << std::endl;
    }

    return 0;
}
