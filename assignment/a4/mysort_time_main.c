/*
--------------------------------------------------
Project: cp264oc-a4q1
File:    mysort_time_main.c
About:   public test driver for runtime
Author:  HBF
Version: 2023-05-30
--------------------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mysort.h"

// copy data addresses to array of pointers
void copy_data_address(float d[], float *a[], int left, int right);

int main(int argc, char *args[])
{
    printf("Algorithm runtime testing:\n");
    clock_t t1, t2;
    int i, len = 100;
    float d[len];
    float *a[len];
    // generate randomly an array of len elements more modular len

    srand(time(NULL));
    for (i = 0; i < len; i++)
    {
        d[i] = rand() % len;
    }

    // run time measuring for selection_sort
    int m1 = 100;
    t1 = clock();
    for (i = 0; i < m1; i++)
    {
        copy_data_address(d, a, 0, len - 1);
        select_sort(a, 0, len - 1);
    }
    t2 = clock();
    double time_span1 = (double)t2 - t1;
    printf("time_span(select_sort(%d numbers) for %d times)(ms):%0.1f\n", len, m1, time_span1);

    // run time measuring for quick_sort
    int m2 = 1000;
    t1 = clock();
    for (i = 0; i < m2; i++)
    {
        copy_data_address(d, a, 0, len - 1);
        quick_sort(a, 0, len - 1);
    }
    t2 = clock();
    double time_span2 = (double)t2 - t1;
    printf("time_span(quick_sort(%d numbers) for %d times)(ms):%0.1f\n", len, m2, time_span2);

    printf("time_span(select_sort(%d numbers))/time_span(quick_sort(%d numbers)):%0.1f\n", len, len, (time_span1 / 10) / (time_span2 / m2));

    return 0;
}

void copy_data_address(float d[], float *a[], int left, int right)
{
    int i;
    for (i = left; i <= right; i++)
        a[i] = &d[i];
}
