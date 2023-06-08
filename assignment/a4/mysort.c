/*
 * your program signature
 */

#include "mysort.h"

void select_sort(float *a[], int left, int right)
{
    int i, j, k;
    float *temp;
    for (i = 0; i < n; ++i)
    {
        k = i;
        for (j = i + 1; j < n; ++j)
        {
            if (*a[j] < *a[k])
            {
                k = j;
            }
        }
        if (i != k)
        {
            // swap the address at a[k] and a[i\]
            temp = a[k];
            a[k] = a[i];
            a[i] = temp;
        }
    }
}
}

void quick_sort(float *a[], int left, int right)
{
    // your implementation
}