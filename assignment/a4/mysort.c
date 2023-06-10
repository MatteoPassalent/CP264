/*
 * your program signature
 */

#include "mysort.h"

void select_sort(float *a[], int left, int right)
{

    int i, j, k;
    float *temp;
    for (i = 0; i < right + 1; ++i)
    {
        k = i;
        for (j = i + 1; j < right + 1; ++j)
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

void quick_sort(float *a[], int left, int right)
{
    int i, j;
    float key, *temp;
    if (left < right)
    {
        key = *a[left];
        i = left + 1;
        j = right;
        while (i <= j)
        {
            while (i <= right && *a[i] <= key)
                i++;
            while (j >= left && *a[j] > key)
                j--;
            if (i < j)
            { // swap a[i] and a[j]; }
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
            else
            {
                // swap a[left] and a[j];
                temp = a[left];
                a[left] = a[j];
                a[j] = temp;
            }
        }
        quick_sort(a, left, j - 1);
        quick_sort(a, j + 1, right);
    }
}