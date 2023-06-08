/*
--------------------------------------------------
Project: cp264oc-a2q1
File:    fibonacci_main.c public test driver
Author:  HBF
Version: 2023-05-14
Compile: gcc fibonacci.c fibonacci_main.c
--------------------------------------------------
*/
#include <stdio.h>
#include <time.h>
#include "fibonacci.h"

int main(int argc, char *argv[])
{
	int i = 0, n = 40;
	clock_t t1, t2;
	sscanf(argv[1], "%d", &n);

	printf("iterative_fibonacci(%d):%d\n", n, iterative_fibonacci(n));

	printf("recursive_fibonacci(%d):%d\n", n, recursive_fibonacci(n));

	int f[n];
	for (i = 0; i <= n; i++)
		f[i] = -1;
	printf("dpbu_fibonacci(%d):%d\n", n, dpbu_fibonacci(f, n));

	for (i = 0; i <= n; i++)
		f[i] = -1;
	printf("dptd_fibonacci(%d):%d\n", n, dptd_fibonacci(f, n));

	return 0;
}
