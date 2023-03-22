//We copy the .dat file to plot waves
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <iostream>



using namespace std;

const int nb=102;
const int NT=1000;
ifstream f("NLinHopfFig4.dat",ios::in);// data source file
ofstream g("utw4.dat",ios::out);//output





void copy(void)
{  
double x=0;
for (int k=0;k<NT;k++)
  {for (int i=0;i<nb;i++)
   {f>>x;
    if (i%2 ==0)
      {cout<<"x= "<<x<< ", i= "<<i<<endl;
       } 
    else
      {
      g<<x;
       g<<" ";} 
       }
   g<<endl;
   } 

}


int main(int argc, char** argv)
{  

copy();
f.close();
g.close();
}



