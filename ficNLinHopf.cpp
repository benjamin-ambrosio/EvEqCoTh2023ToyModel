// This program is to write instructions to be used with gnuplot
//It allows to see the solution as a "movie"
#include <iostream>
#include <math.h>
#include <fstream>
using namespace std;
int main()
{
ofstream g("fic.txt",ios::out); //this file will be called with gnuplot: load "fic.txt"
g<<"reset"<<endl;
// g<< "set title 'Evolution de la solution pour quelques cellules'"<< endl;
g<<"set xrange [0:1]"<<endl;
g<<"set yrange [-20:20]"<<endl;
for (int i=0;i<1000;i++)

{
//each line represents u(x) for fixed t. 
//So with gnuplot we see the movie of the time evolution of u(x,t) 
g<<"plot 'NLinHopf.dat' ind"<<' '<<i<<' ';
g<<  "using 1:2 with lines title 't="<<((double)i)/10<<"'"<<endl; 
g<< "pause 0.1"<< endl;

}
g<<"reset"<<endl;
g.close();

//mencoder mf://*.jpg -mf w=800:h=600:fps=25:type=jpg -ovc lavc -lavcopts vcodec=mpeg4 -oac copy -o sortie.avi
// This line is to do a movie with mencoder
}
