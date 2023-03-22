#ifndef LinHopf1dRK4_H
#define LinHopf1dRK4_H
#include <iostream>
#include <math.h>
#include <fstream>
#include <time.h>
#include <stdlib.h>
// This will be seen by the compiler only once 

using namespace std;
const double T=100, T0=0 ; // Maximal time T and initial time to write in files T0

const double h=0.02;//space step
const double al1=0,al2=0,be1=0,be2=0;// not used in this program
const double du=1, dv=0.0;// diffusion  coefficients
const double eps=0.1;//slow fast; not used here
const double A=1/eps;
const double a=0,b=1;// space domain (a,b)
const double al=15;
//const double al=9.86960440108936; //=pi*pi
const int nb=int(floor((b-a)/h)); // size of our double* u
double dt=0.00001; // timestep


double* alea1;
double* alea2;













// This class represents the solution (u,v) at time t
class syst {
public:
  syst();
  syst(double, double *, double *);
  syst(const syst&);
  syst& operator=(const syst&);
  syst& affect(double, double *, double *);
  syst& affect(double, double, double);
  syst& init(double, double);
  syst& init(double (*)(int), double (*)(int)); 
  void F();
 
void printu(ofstream& );
void printv(ofstream& );
  void printuv(ofstream& );

  void printt(ofstream& );
  int debut(){return t>T0;};
  int fin(){return t<T;};
 int cent(){return ((int)t==20);};
 int cent2(){return ((int)t==1090);};
  int div(){return (floor(10*t)-floor(10*(t-dt)));};
  int div2(){return ((int)(100*t)% 700)==0;};
int div3(){return ((int)(1000*t)% 100 )==0;};
int div4(){return (floor((100)*t)-floor((100)*(t-dt)));};
  ~syst();
private:
 double t;  
 double* u;
 double* v;       
};














// function f1(u,v)=al*u-u^3-v
double f1(double x, double y)
{return (double)(al*x-y-x*x*x);}

//function f2(u,v)=u
double f2(double x, double y)
{return (double)(x);}



//function c0(x)
double c0(int i)
{
return 1;
  }

double c1(int i)
{
return 1*cos((a+(double)i*0.1*h)*M_PI);
  }
double c2(int i)
{
if (i<((nb)/2))
  return 0.5;
if (i==((nb)/2))
  return 0.0;
if (i>((nb)/2))
  return -0.5;
  }


double c3(int i)
{
if (i<((nb)/2))
  return 0.5;
if (i==((nb)/2))
  return 0.0;
if (i>((nb)/2))
  return 0.0;
  }
double c4(int i)
{
return 0;
  }

double c5(int i)
{
if ((i%2)==0)
  return 1;
else
  return -1;
  }


double tau12ter(int i)
{


  return 1-2*alea1[i];

}

double tau12bis(int i)
{


  return 1-2*alea2[i];

}














#endif
