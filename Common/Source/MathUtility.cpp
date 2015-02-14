#include "MathUtility.h"
#include "MyMath.h"

int doFactorial(int n, int accumulator)
{
    if (n == 0)
        return accumulator;

    return doFactorial(n - 1, n * accumulator); //tail recursive
}

int factorial(int n)
{
    return doFactorial(n, 1);
}

int combination(int n, int r)
{
    return doFactorial(n, 1) / (doFactorial(r, 1) * doFactorial(n - r, 1));
}

int permutation(int n, int k)
{
    return (doFactorial(n, 1) / doFactorial(n - k, 1));
}

int arithmetic(int n, int a, int d)
{
    return a + ((n - 1) * d);
}

int Sum_arithmetic(int n, int a, int d)
{
    return (n/2) * ((2 * a) + ((n - 1) * d));
}

int power (int x, int y)
{
    if (y == 0)
    {
        return 1;
    }

    else
    {
        return x * power(x, y-1);
    }
}

int geometric(int n, int a, int r)
{
    return a*(power(r, n - 1));
}

int Sum_geometric(int n, int a, int r)
{
    return (a*(1 - power(r, n))) / (1 - r);
}