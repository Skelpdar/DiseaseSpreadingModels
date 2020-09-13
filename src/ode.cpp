#include <iostream>
#include <fstream>
#include <Eigen/Dense>
#include <vector>

#include <rungeKutta.h>

using Eigen::MatrixXd;
using Eigen::Vector2d;

using namespace Eigen;

double beta = 0.07;
double alpha = 0.05;

Vector2d SIS(double tn, Vector2d y){
    Vector2d v;

    v(0) = -beta*y(0,0)*y(1,0)/(y(0,0)+y(1,0))+alpha*v(1,0);
    v(1) = beta*y(0,0)*y(1,0)/(y(0,0)+y(1,0))-alpha*v(1,0);

    return v;

}

int main(){
    Vector2d y0;
    y0(0) = 70;
    y0(1) = 30;

    std::vector<Vector2d> data;
    std::vector<Vector2d> error;

    rungeKutta(y0, SIS, 10, 100, data, error);

    std::ofstream SISFile;
    SISFile.open("SISSolution.txt");

    for(int i=0; i<data.size(); i++){
        SISFile << data[i] << std::endl;
        SISFile << error[i] << std::endl;
    }

    SISFile.close();

    return 0;
}
