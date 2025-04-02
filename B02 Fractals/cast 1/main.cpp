#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

int main()
{
    ofstream outdata;
    outdata.open("May.dat");
    double x[100],lambda=1.5;
    x[0]=0.01;
    x[1]=0;
    outdata << x[0] << "\t" << x[1] << endl; //pociatocny bod
    for(int n=0;n<100;n++){
        x[n+1] = lambda*x[n]*(1-x[n]);
        outdata << x[n] << "\t" << x[n+1] << endl;
        outdata << x[n+1] << "\t" << x[n+1] << endl;
    }
    outdata.close();
    return 0;
}
