#include <time.h>
#include <cstdlib>
#include <iostream>
using namespace std;

int primeGen()
{
    return 53;
}

int p = primeGen();

int randomGen(int start, int end)
{
    //srand(time(NULL));
    return rand() % (end - start) + start;
}

int** lowerMatrixGen(int n)
{
    int** L = new int* [n];
    
    srand(time(NULL));

    for (int i = 0; i < n; i++)
    {
        L[i] = new int[n];
        for (int j = 0; j < i; j++)
        {
            L[i][j] = randomGen(0, p);
        }
        L[i][i] = randomGen(1, p - 1);
        for (int j = i + 1; j < n; j++)
        {
            L[i][j] = 0;
        }
    }

    return L;
}

int** upperMatrixGen(int n)
{
    int** U = new int* [n];
    
    srand(time(NULL));

    for (int i = 0; i < n; i++)
    {
        U[i] = new int[n];
        for (int j = 0; j < i; j++)
        {
            U[i][j] = 0;
        }
        U[i][i] = randomGen(1, p - 1);
        for (int j = i + 1; j < n; j++)
        {
            U[i][j] = randomGen(0, p);
        }
    }
    return U;
}

int moduloInverse(int a)
{
    int q, r, x, y, b = p, x2 = 1, x1 = 0, y2 = 0, y1 = 1;
    while (b > 0)
    {
        q = (int)(a / b);
        r = a - q * b;
        x = x2 - q * x1;
        y = y2 - q * y1;
        a = b;
        b = r;
        x2 = x1;
        x1 = x;
        y2 = y1;
        y1 = y;
    }
    if (x2 < 0)
    {
        x = x2 + p;
    }
    else
    {
        x = x2;
    }
    return x;
}

int** invertL(int** L, int n)
{
    int** B = new int* [n];    //I
    for (int i = 0; i < n; i++)
    {
        B[i] = new int[n];
        for (int j = 0; j < i; j++)
        {
            B[i][j] = 0;
        }
        B[i][i] = 1;
        for (int j = i + 1; j < n; j++)
        {
            B[i][j] = 0;
        }
    }

    int** X = new int* [n];
    for (int i = 0; i < n; i++)
    {
        X[i] = new int[n];
    }
    for (int j = 0; j < n; j++)
    {
        X[0][j] = (B[0][j] * moduloInverse(L[0][0])) % p;
        if (X[0][j] < 0)
        {
            X[0][j] += p;
        }
        int sum = 0;
        for (int i = 1; i < n; i++)
        {
            sum += L[i][i - 1] * X[i - 1][j];
            X[i][j] = ((B[i][j] - sum) * moduloInverse(L[i][i])) % p;
            if (X[i][j] < 0)
            {
                X[i][j] += p;
            }
        }
    }
    return X;
}

int** invertU(int** U, int n)
{
    int** B = new int* [n];   //I
    for (int i = 0; i < n; i++)
    {
        B[i] = new int[n];
        for (int j = 0; j < i; j++)
        {
            B[i][j] = 0;
        }
        B[i][i] = 1;
        for (int j = i + 1; j < n; j++)
        {
            B[i][j] = 0;
        }
    }

    int** X = new int* [n];
    for (int i = 0; i < n; i++)
    {
        X[i] = new int[n];
    }
    for (int j = n - 1; j >= 0; j--)
    {
        X[n - 1][j] = (B[n - 1][j] * moduloInverse(U[n - 1][n - 1])) % p;
        if (X[n - 1][j] < 0)
        {
            X[n - 1][j] += p;
        }
        int sum = 0;
        for (int i = n - 2; i >= 0; i--)
        {
            sum += U[i][i + 1] * X[i + 1][j];
            X[i][j] = ((B[i][j] - sum) * moduloInverse(U[i][i])) % p;
            if (X[i][j] < 0)
            {
                X[i][j] += p;
            }
        }
    }
    return X;
}

int** mulMatrices(int** L, int** U, int n)
{
    int** R = new int* [n];    //I
    for (int i = 0; i < n; i++)
    {
        R[i] = new int[n];
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            R[i][j] = 0;
            for (int k = 0; k < n; k++)
            {
                R[i][j] += L[i][k] * U[k][j];
            }
            R[i][j] = R[i][j] % p;
        }
    }
    return R;
}

std::pair<int**, int**> fastKeyGen(int n)
{
    int** L = lowerMatrixGen(n);
    int** U = upperMatrixGen(n);
    int** X = invertL(L, n);
    int** Y = invertU(U, n);
    int** K = mulMatrices(L, U, n);
    int** invK = mulMatrices(Y, X, n);
    return std::make_pair(K, invK);
}
int main()
{
    int n = 3;
    int** L = upperMatrixGen(n);

    for (int i = 0; i <n; i++)
    {
        for (int j = 0; j <n; j++)
        {
            cout << (int)L[i][j] << "\t";
        }
        cout << "\n";
    }
    L = invertU(L, n);
    for (int i = 0; i <n; i++)
    {
        for (int j = 0; j <n; j++)
        {
            cout << (int)L[i][j] << "\t";
        }
        cout << "\n";
    }
    //cout << moduloInverse(11);
    return 1;
}