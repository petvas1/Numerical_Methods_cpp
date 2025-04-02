#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

const int n = 200; //pocet rovnic

double MatrixInversion(double (&A)[n][n], double (&AInverse)[n][n]);

int main()
{
    ofstream fout;
    fout.open("data.dat");
    double a[n][n];
    double a2[n][n];
    double ainv[n][n];
    double ro[n], b[n], determinants[n];
    double det, det_a2, delta, E;
    E = 0; delta = 1./(n);

    //vytvorenie matice
    for(int i=1;i<=n;i++) //ulozenie rovnic
    {
        for(int j=1;j<=n;j++)
        {
            a[i-1][j-1] = (i-j+0.5)/pow(abs(i-j+0.5),3);
            if (i==n) a[i-1][j-1] = 1;
            //cout << a[i-1][j-1] << "\t";
        }
        //cout << endl;
        b[i-1] = 0;
        if (i==n) b[i-1] = 1;
    }

    for(int k=0;k<n;k++) //na urcenie ostatnych rieseni
    {
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
                a2[i][j] = a[i][j];
                a2[i][k] = b[i];  //nahradenie k-teho stlpca pravou stranou
        }
        det_a2 = MatrixInversion(a2,ainv);
        determinants[k] = det_a2;  //ulozi hodnoty determinantov det a(k)
    }
    if ((det = MatrixInversion(a,ainv))==0)
    {
        cout << "Sustava nema riesenie";
        return 0;
    }

    double sum = 0;
    for (int j=1;j<=n;j++)
    {
        ro[j-1] = determinants[j-1]/det; //riesenia (hustoty naboja)
        sum += j*ro[j-1]; // na normovanie
    }

    int k=0;
    for (int i=n/2;i<=n;i++)
    {
        /*E = 0;
        for (int j=1;j<=n;j++)
        {
            E += ((i-j+0.5)/pow(abs(i-j+0.5),3) + (i+j-0.5)/pow(abs(i+j-0.5),3))*ro[j-1]*sum/delta;
        }
        fout << k*delta << "\t" << E << endl;*/
        fout << k*2*delta << "\t" << ro[i-1]*sum << endl;
        k++;
    }

    fout.close();
    return 0;
}

double MatrixInversion(double (&A)[n][n], double (&AInverse)[n][n])
{
     // A = vstupna matica (n x n)
     // AInverse = inverzna matica (n x n)
     // Tato funkcia invertuje maticu Gauss-Jordanovou eliminaciou.
     // Vracia determinant matice. Ak vrati 0, matica sa neda invertovat.
     // Pozor!!! Povodna matica A sa eliminaciou stane jednotkovou!
     int i, j, iPass, imx, icol, irow;
     double det, temp, pivot, factor;
     det = 1;
     for (i = 0; i < n; i++)
     {
        for (j = 0; j < n; j++)
            AInverse[i][j] = 0;
        AInverse[i][i] = 1;
     }
     // Aktualmnym pivotom riadku je iPass.
     // Pre kazdy prechod - najprv najst najvacsi element v stlpci pivota.
     for (iPass = 0; iPass < n; iPass++)
     {
         imx = iPass;
         for (irow = iPass; irow < n; irow++)
            if (fabs(A[irow][iPass]) > fabs(A[imx][iPass])) imx = irow;

     // Vymenit prvky riadku iPass a riadku imx v A aj AInverse.
     // Zmenit znamienko determinantu na opacne pri zamene riadkov
         if (imx != iPass)
         {
             det *= -1;
             for (icol = 0; icol < n; icol++)
             {
                 temp = AInverse[iPass][icol];
                 AInverse[iPass][icol] = AInverse[imx][icol];
                 AInverse[imx][icol] = temp;
                 if (icol >= iPass)
                 {
                    temp = A[iPass][icol];
                    A[iPass][icol] = A[imx][icol]; A[imx][icol] = temp;
                 }
             }
         }
         // Aktualnym pivotom je teraz A[iPass][iPass].
         // Determinant je sucinom pivotov.
         pivot = A[iPass][iPass];
         det *= pivot;
         if (det == 0)
             return 0;
         for (icol = 0; icol < n; icol++)
         {
             // Normalizovat riadok pivotu delenim hodnotou pivotu.
             AInverse[iPass][icol] = AInverse[iPass][icol] / pivot;
             if (icol >= iPass) A[iPass][icol] = A[iPass][icol] / pivot;
         }
         for (irow = 0; irow < n; irow++)
         // Pricitat nasobok riadku pivotu ku kazdemu riadku.
         // Nasobiaci koef. sa zvoli tak, ze prvok A v stlpci pivota je 0.
         {
             if (irow != iPass) factor = A[irow][iPass];
             for (icol = 0; icol < n; icol++)
             {
                 if (irow != iPass)
                 {
                     AInverse[irow][icol] -= factor * AInverse[iPass][icol];
                     A[irow][icol] -= factor * A[iPass][icol];
                 }
             }
         }
     }
     return det;
}
