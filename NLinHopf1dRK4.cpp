#include <iostream>
#include <math.h>
#include <fstream>
#include "NLinHopf1dRK4.h"
using namespace std; 
// This program simulates a 2d reaction-diffusion system in a 1d bounded domain
// The equation are u'=f1(u,v)+duDelta(u) and v'=f2(u,v)+dvDelta(v) 
//The equation is solved to a finite difference in space with space step h and a RK4 scheme in time with step dt



    
        

// Laplacian (Neumann Boundary Conditions)
double delta(double* x, int i)
 {
 if (i==0)
  return ((x[1]-x[0])/(h*h));
 if (i==nb)
  return ((x[nb-1]-x[nb])/(h*h));
 if ((i>0) && (i<nb)) 
   return ((x[i-1]+x[i+1]-2*x[i])/(h*h));
   }




// Constructor
syst::syst()
{ t=0;
  u= new double[nb+1];
  v= new double[nb+1]; 
  for(int i=0;i<nb+1;i++)
      {u[i]=0;
         v[i]=0;
        }
     
}




// Constructor
syst::syst(double a,double* x, double* y)
{ t=a;
  u= new double[nb+1];
  v= new double[nb+1]; 
  for(int i=0;i<nb+1;i++)
      {u[i]=x[i];
         v[i]=y[i];
        }
     
}

//Constructor
syst::syst(const syst& r)
{t=r.t;
 u= new double[nb+1];
  v= new double[nb+1]; 
 for(int i=0;i<nb+1;i++)
        {u[i]=r.u[i];
         v[i]=r.v[i];
         }
}

//surcharge of operator =
syst& syst::operator=(const syst& r)
{t=r.t;
  for(int i=0;i<nb+1;i++)
   {u[i]=r.u[i];
    v[i]=r.v[i];
   }
  return *this;
}

// Operator of affectation
syst& syst::affect(double a,double* x, double* y)
{t=a;
  for(int i=0;i<nb+1;i++)
    {u[i]=x[i];
     v[i]=y[i];
     }
  return *this;
}

//Second operator of affectation
syst& syst::affect(double a,double b, double c)
{t=a;
  for(int i=0;i<nb+1;i++)  
       {u[i]=b;
       v[i]=c;
       }
return *this;
}


//operator for initial conditions: with constant functions
syst& syst::init(double a,double b)
{t=0;
  for(int i=0;i<nb+1;i++)  
       {u[i]=a;
       v[i]=b;
       }
return *this;
}

// second operator for initial conditions: 
//fonctions *pf1 et *pf2
syst& syst::init(double(*pf1)(int k), double(*pf2)(int k))
{t=0;
  for(int i=0;i<nb+1;i++)
   {u[i]=(*pf1)(i);
    v[i]=(*pf2)(i);
    } 
  return *this;
}



//write data u into a file
void syst::printu(ofstream& f )
{for(int i=0;i<nb+1;i++)
    f<<a+i*h<<' '<<u[i]<<' '<<endl; 
f<<endl;
f<<endl;
}

// write data v into a file
void syst::printv(ofstream& f )
{for(int i=0;i<nb+1;i++)
    f<<a+i*h<<' '<<v[i]<<' '<<endl; 
f<<endl;
f<<endl;
}


// write u and v into a file
void syst::printuv(ofstream& f )
{for(int i=0;i<nb+1;i++)
    f<<u[i]<<' '; 
 f<<endl<<endl;
for(int i=0;i<nb+1;i++)
    f<<v[i]<<' '; 
 f<<endl<<endl;
}




// write only at some points in space. Useful for plotting functions of time 
void syst::printt(ofstream& f )
{
{f<<t<<" ";
for (int i=0;i<nb+1;i++)
f<<u[i]<<' '<<v[i]<<' ';
f<<' ';
f<<endl;
//if (div2())    //for some applications it is useful to add a line
//f<<endl<<endl;  
}
}

//destructor
syst::~syst()
{
 delete[]u;
 delete[]v;
} 




//function to iterate at each time step

void syst::F()
{
double* x=new double[nb+1];
double* y=new double[nb+1];
double* yu2=new double[nb+1];
double* yu3=new double[nb+1];
double* yu4=new double[nb+1];
double* yv2=new double[nb+1];
double* yv3=new double[nb+1];
double* yv4=new double[nb+1];


for(int i=0;i<nb+1;i++)
{ 

yu2[i]=u[i]+(dt/2)*(f1(u[i],v[i])+du*delta(u,i));
yv2[i]=v[i]+(dt/2)*(f2(u[i],v[i])+dv*delta(v,i));
}

for(int i=0;i<nb+1;i++)
{ 
yu3[i]=u[i]+(dt/2)*(f1(yu2[i],yv2[i])+du*delta(yu2,i));
yv3[i]=v[i]+(dt/2)*(f2(yu2[i],yv2[i])+dv*delta(yv2,i));
}

for(int i=0;i<nb+1;i++)
{ 
yu4[i]=u[i]+dt*(f1(yu3[i],yv3[i])+du*delta(yu3,i));
yv4[i]=v[i]+dt*(f2(yu3[i],yv3[i])+dv*delta(yv3,i));
}

for(int i=0;i<nb+1;i++)
{    
x[i]=u[i]+(dt/6)*((f1(u[i],v[i])+du*delta(u,i))
   +2*(f1(yu2[i],yv2[i])+du*delta(yu2,i))
   +2*(f1(yu3[i],yv3[i])+du*delta(yu3,i))
   +(f1(yu4[i],yv4[i])+du*delta(yu4,i)));
   
y[i]=v[i]+(dt/6)*((f2(u[i],v[i])+dv*delta(v,i))
   +2*(f2(yu2[i],yv2[i])+dv*delta(yv2,i))
   +2*(f2(yu3[i],yv3[i])+dv*delta(yv3,i))
   +(f2(yu4[i],yv4[i])+dv*delta(yv4,i)));
}




 
cout<<" "<<u[0]<<" "<<u[1]<<" "<<u[nb/2]<<" "<<u[nb-1]<<" "<<u[nb]<<" "<<delta(u,0)<<" "<<delta(u,nb);
cout<<" "<<nb<<" "<<t<<endl<<endl;
 affect(t+dt,x,y); 


 delete[]x;
 delete[]y;
 delete[]yu2;
 delete[]yv2;
delete[]yu3;
 delete[]yv3;
 delete[]yu4;
 delete[]yv4;
}




  


int main()
{
alea1 =new double[nb];
alea2 =new double[nb];
   for(int m=0;m<nb;m++)
   {
       
       alea1[m]=((double)random()/ (double)(RAND_MAX));
       alea2[m]=((double)random()/ (double)(RAND_MAX));
  }





ofstream g("NLinHopf.dat",ios::out); //all values of u for all space 
ofstream l("NLinHopf-v.dat",ios::out);  //all values of v for all space 
ofstream h("NLinHopfev.dat",ios::out);// fichier receuillant les valeurs
syst S;
//S.init(-1.5,2.0)
S.init(c3,c3);// initial conditions
while(S.fin())
   { S.F();
   if ((S.debut()) && (S.div4()))
   S.printt(h);
   if ((S.debut()) && (S.div())) // we write only at some times
    {S.printu(g);     
     S.printv(l);}
}


  g.close();
  h.close();
   l.close();





   
delete alea1;
delete alea2;

}
