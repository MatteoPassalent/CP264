/*
--------------------------------------------------
Project: cp264oc-a2q1
File:    fibonacci.c
Author:  Matteo Passalent
Version: 2023-05-23
--------------------------------------------------
*/

#include "fibonacci.h"

int recursive_fibonacci(int n)
{

    if (n <= 1)
        return n;
    else
        return recursive_fibonacci(n - 2) + recursive_fibonacci(n - 1);
}

int iterative_fibonacci(int n)
{

    if (n <= 1)
    {
        return n;
    }

    int f0 = 0;
    int f1 = 1;
    int fnew;
    for (int i = 2; i <= n; i++)
    {
        fnew = f0 + f1;
        f0 = f1;
        f1 = fnew;
    }
    return fnew;
}

int dpbu_fibonacci(int *f, int n)
{
    if (n <= 1)
        return n;

    for (int i = 0; i <= n; i++)
        f[i] = -1;

    f[0] = 0;
    f[1] = 1;

    for (int i = 2; i <= n; i++)
    {
        f[i] = f[i - 2] + f[i - 1];
    }

    return f[n];
}

int dptd_fibonacci(int *f, int n)
{
    if (n <= 1)
    {
        return n;
    }

    if (f[n] > 0)
    {
        return f[n];
    }
    else
    {
        f[n] = dptd_fibonacci(f, n - 2) + dptd_fibonacci(f, n - 1);
        return f[n];
    }
}
