/*
--------------------------------------------------
Project: cp264oc-a2q3
File:    matrix.c
Author:  Matteo Passalent
Version: 2023-05-24
--------------------------------------------------
*/

#include <stdio.h>
#include <math.h>
#include "matrix.h"

/*
 * Computes and returns the sum of all elements of vector v[n]
 */
float sum(float *v, int n)
{
    float total = 0;
    for (int i = 0; i < n; i++)
    {
        total += v[i];
    }
    return total;
}

/*
 * Computes and returns the norm of vector v, namely, the square root of the sum of
 * squares of elements of v.
 */
float norm(float *v, int n)
{
    float total = 0;
    for (int i = 0; i < n; i++)
    {
        total += v[i] * v[i];
    }
    return sqrtf(total);
}

/*
 * Computes and returns the dot product of vectors v1[n] and v2[n], the sum of product of
 * corresponding elements of v1 and v2.
 * squares of elements of v.
 */
float dot_product(float *v1, float *v2, int n)
{

    float total = 0;
    for (int i = 0; i < n; i++)
    {
        total += v1[i] * v2[i];
    }
    return total;
}

/*
 * Transposes the n by n matrix m1 and save the resulted matrix in m2.
 */
void transpose_matrix(float *m1, float *m2, int n)
{
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
        {
            *(m2 + j * n + i) = *(m1 + i * n + j);
        }
}
/*
 * Computes n by n matrix multiplies n-vector m*v1 and saves the result vector in v2.
 */
void matrix_multiply_vector(float *m, float *vin, float *vout, int n)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        vout[i] = 0;
        for (j = 0; j < n; j++)
        {
            vout[i] += *(m + i * n + j) * vin[j];
        }
    }
}

/*
 * Computes the matrix multiplication m1*m2 and saves the resulted matrix in m3.
 */
void multiply_matrix(float *m1, float *m2, float *m3, int n)
{
    float s = 0;
    int i, j, k;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < 3; j++)
        {
            s = 0;
            for (k = 0; k < n; k++)
            {
                s += *(m1 + i * n + k) * *(m2 + k * 3 + j);
            }
            *(m3 + i * n + j) = s;
        }
    }
}
