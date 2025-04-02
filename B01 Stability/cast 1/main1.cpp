#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

int main()
{
    ofstream outdata;
    outdata.open("g_post.dat");
    double x1,g[100];
    x1 = 0.5*(sqrt(5)-1);
    g[0] = 1;
    g[1] = x1;
    for (int n=1;n<=100;n++){
        g[n+1] = g[n-1]-g[n];
        outdata << n-1 << "\t" << g[n-1] << endl;
    }
    outdata.close();
    return 0;
}
