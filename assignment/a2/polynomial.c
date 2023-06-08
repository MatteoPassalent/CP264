/*
--------------------------------------------------
Project: cp264oc-a2q2
File:    polynomial.c
Author:  Matteo Passalent
Version: 2023-05-24
--------------------------------------------------
*/

#include <stdio.h>
#include <math.h>
#include "polynomial.h"

#define EPSILON 1e-6

float horner(float *p, int n, float x)
{
    float r = 0;
    int i;
    for (i = 0; i < n; i++)
        r = r * x + p[i];
    return r;
}

float bisection(float *p, int n, float a, float b)
{
    float c;

    while (1)
    {
        c = (a + b) / 2;

        if (fabs(horner(p, n, c)) < EPSILON || fabs(c - a) < EPSILON)
        {
            return c;
        }
        else if ((horner(p, n, c) > 0 && horner(p, n, a) > 0) || (horner(p, n, c) < 0 && horner(p, n, a) < 0))
        {
            a = c;
        }
        else
        {
            b = c;
        }
    }
}