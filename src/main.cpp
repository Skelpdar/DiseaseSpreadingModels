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
using Eigen::Vector4d;
using Eigen::VectorXd;

using namespace Eigen;

double beta = 3;
double alpha = 0.14;

Vector2d SIS(double tn, Vector2d y){
    Vector2d v;

    v(0) = -beta*y(0,0)*y(1,0)/(y(0,0)+y(1,0))+alpha*v(1,0);
    v(1) = beta*y(0,0)*y(1,0)/(y(0,0)+y(1,0))-alpha*v(1,0);

    return v;

}

//The SIR model, includes resistant population and vacination of suseptible pop, N = S + I + R
double SIRInfec = 3;
double SIRRec = 0.14;
double SIRVac = 0;

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

//SIR with traveling
//populations
Vector4d SusV;//S1 to S4 with initial suseptible population in four diferent groups
Vector4d InfV;
Vector4d RecV;

//SIR parameters given as vectors
Vector4d TInf =  Vector4d (1, 1, 1, 1);
double TRec =  0.14; //recovery rate is the same for all populations
Vector4d TVac =  Vector4d (0, 0, 0, 0);




//Vector function containing derivatives of all pops, y(S1, S2, S3, S4,, I1, I2, I3, I4 R1, R2, R3, R4)
VectorXd TravelSIR(double tn, VectorXd y){
    VectorXd sol(12);
    Vector4d S = Vector4d (y(0,0), y(1,0), y(2,0), y(3,0));
    Vector4d R = Vector4d (y(4,0), y(5,0), y(6,0), y(7,0));
    Vector4d I = Vector4d (y(8,0), y(9,0), y(10,0), y(11,0));

    //Traveling parameters into relevant population, balanced w_nm = w_mn required
    MatrixXd Tcoff(4,4);
    Tcoff << 0, 0.1, 0.1, 0.1,
             0.1, 0, 0.1, 0.1,
             0.1, 0.1, 0, 0.1,
             0.1, 0.1, 0.1, 0;
    //Sn
    for (int i = 0; i < 4; i++) {//for each pop
        double sumT = 0;
        for (int j = 0; j < 4; j++) {//calculate sum of traveling, from j going to i
        if (j != i) {
            sumT += Tcoff(i, j)*S(j) - Tcoff(j,i)*S(i);
        };
        };
        sol(i,0) = -TInf(i)*S(i)*I(i)/(S(i)+R(i)+I(i))- TVac(i)*S(i) + sumT;        
        };
    //In
    for (int i = 0; i < 4; i++) {//for each pop
        double sumT = 0;
        for (int j = 0; j < 4; j++) {//calculate sum of traveling, from j going to i
        if (j != i) {
            sumT += Tcoff(i, j)*I(j) - Tcoff(j,i)*I(i);
        };
        };
        sol(i+4,0) = TInf(i)*S(i)*I(i)/(S(i)+R(i)+I(i))- TRec*I(i) + sumT;        
        };
    //Rn
    for (int i = 0; i < 4; i++) {//for each pop
        double sumT = 0;
        for (int j = 0; j < 4; j++) {//calculate sum of traveling, from j going to i
        if (j != i) {
            sumT += Tcoff(i, j)*R(j) - Tcoff(j,i)*R(i);
        };
        };
        sol(i+8,0) = TVac(i)*S(i) + TRec*I(i) + sumT;        
        };
    return sol;
};


int main(){
    /*
    Vector2d y0;
    y0(0) = 199;
    y0(1) = 1;

    std::vector<Vector2d> data;
    std::vector<Vector2d> error;
 
    rungeKutta(y0, SIS, 0.5, 60, data, error);
    std::ofstream SISFile;
    SISFile.open("SISSolutionRK.txt");

    for(int i=0; i<data.size(); i++){
        SISFile << data[i] << std::endl;
        SISFile << error[i] << std::endl;
    }

    SISFile.close();

    //test for euler method

    Vector3d y0;
    y0(0) = 199;
    y0(1) = 1;
    y0(2) = 0;

    std::vector<Vector3d> data;
    std::vector<Vector3d> error;
 
    euler(y0, SIR, 0.5, 60, data, error);
    std::ofstream SIRFile;
    SIRFile.open("SIRSolutionEuler.txt");

    for(int i=0; i<data.size(); i++){
        SIRFile << data[i] << std::endl;
        SIRFile << error[i] << std::endl;
    }
*/
//SIR with traveling
    std::vector<VectorXd> data;
    std::vector<VectorXd> error;

    VectorXd initPop(12);
    initPop <<  800, 800, 800, 800, 
                10, 0, 0, 0,
                0, 0, 0, 0;
 
    rungeKutta(initPop, TravelSIR, 0.1, 300, data, error);
    std::ofstream SISFile;
    SISFile.open("SIRTravel.txt");

    for(int i=0; i<data.size(); i++){
        SISFile << data[i] << std::endl;
        SISFile << error[i] << std::endl;
    }

    SISFile.close();
    return 0;
}
