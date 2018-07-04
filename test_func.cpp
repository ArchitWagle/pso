#include<math.h>
#include<vector>
#include"test_func.h"
using namespace std;


double booth(vector<double> temp)
 { 
   double x = temp[0];
   double y = temp[1];
   return ((x+2*y-7)*(x+2*y-7)+(2*x+y-5)*(2*x+y-5));
 }

double sphere(vector<double> temp)
 { 
   double x = temp[0];
   double y = temp[1];
   return (x*x+y*y);
 }
 
 
 double ackley(vector<double> temp)
 {
   double x = temp[0];
   double y = temp[1];
   return (-20*exp(-0.2*sqrt(0.5*(x*x+y*y)))-exp(0.5*(cos(2*M_PI*x)+cos(2*M_PI*y))+exp(1)+20));
 }
 
 double holder(vector<double> temp)
 {
   double x = temp[0];
   double y = temp[1];
   return(-abs(sin(x)*cos(y)*exp(abs(1-(sqrt(x*x+y*y)/M_PI)))));
 }
 
 double rosenbrock(vector<double> temp)
 {
   double x = temp[0];
   double y = temp[1];
   double z = temp[2];
   return(100*(pow(y-x*x,2)+pow(z-y*y,2))+(pow(1-x,2)+pow(1-y,2)));
 }

