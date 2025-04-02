#include <iostream>
#include <fstream>
#include <cmath>
#include <time.h>
#include <stdlib.h>
#include <numeric>
#include <stdint.h>	// uint64_t
#include <limits.h> // ULLONG_MAX

using namespace std;

static inline uint64_t rotl(const uint64_t x, int k)
{
	return (x << k) | (x >> (64 - k));
}

uint64_t xoroshiro128_next(uint64_t* s0, uint64_t* s1)
{
	const uint64_t _s0 = *s0;
	uint64_t _s1 = *s1;
	const uint64_t result = _s0 + _s1;

	_s1 ^= _s0;
	*s0 = rotl(_s0, 24) ^ _s1 ^ (_s1 << 16);
	*s1 = rotl(_s1, 37);

	return result;
}

double next_double(uint64_t* s0, uint64_t* s1)
{
	return (double)xoroshiro128_next(s0, s1) / (double)ULLONG_MAX;
}

int main(int argc, char** argv)
{
    const int N = 1000, M = 1000;

    srand(time(0));
    uint64_t s0 = rand() << 32 | rand();
    uint64_t s1 = rand() << 32 | rand();

    double* x = new double[N];

    double s[M]={0};

    for (int j = 0; j < M; j++)
    {
        for (int i = 0; i < N; i++)
        {
            x[i] = next_double(&s0, &s1);
        }
        s[j] = accumulate(x, x+N, s[j]);
    }

    //average
    double s_avg = 0, s_sum = 0, s_var = 0;
    s_avg = 1./M*accumulate(s, s+M, s_avg);
    //variance
    for (int i = 0; i < M; i++) s_sum += pow(s[i],2);
    s_var = 1./M*s_sum - pow(s_avg,2);

    cout << "<s> = " << s_avg << endl;
    cout << "var s = " << s_var << endl;
    cout << sqrt(s_var)/s_avg*sqrt(N) << endl;

    //pravdepodobnostne rozdelenie
    double a = s_avg - 5*sqrt(s_var), b = s_avg + 5*sqrt(s_var); //hranice (+-5sigma)
    const int I = 100; //pocet intervalov
    double P[I] = {0}, delta = (b-a)/I;
    int index = 0;
    for (int i = 0; i < M; i++)
    {
        index = int((s[i]-a)/delta);
        P[index] +=  1./(M*delta);
    }

    ofstream fout;
    fout.open("gauss.dat");
    for (int i = 0; i < I; i++)
        fout << a + i*delta + delta/2 << "\t" <<  P[i] << endl; //delta/2 je len korekcia pre plot
    fout.close();

    return 0;
}

