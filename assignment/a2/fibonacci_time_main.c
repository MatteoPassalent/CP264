/*
--------------------------------------------------
Project: cp264oc-a2q1
File:    fibonacci_time_ptest.c public test driver
Author:  HBF
Version: 2023-05-14
Compile: gcc fibonacci.c fibonacci_tine_ptest.c
--------------------------------------------------
*/
#include <stdio.h>
#include <time.h>
#include "fibonacci.h"

int main(int argc, char *argv[]){
	int i, j, n = 40, f[n+1];
	clock_t t1, t2;	
	
	printf("**Function runtime measurement**\n");
	
	//run time measuring for iterative_fibonacci
	int m1 = 50000;
	t1=clock();
	for (i=0; i< m1; i++) {
	  iterative_fibonacci(n);
	}
	t2=clock();
	double time_span1 = (double) t2-t1;
	printf("time_span(iterative_fibonacci(%d) for %d times):%0.1f (ms)\n", n, m1, time_span1);
	
	

	int m2 = 5;
	t1=clock();
	for (i=0; i<m2; i++) {
      recursive_fibonacci(n);
	}
	t2=clock();
	double time_span2 = t2-t1;
	printf("time_span(recursive_fibonacci(%d) for %d times):%0.1f (ms)\n", n, m2, time_span2);
	
	
	int m3 = 50000;
	t1=clock();
	for (i=0; i< m1; i++) {
	  for (j=0; j<=n; j++) f[j]=-1; 	
	  dpbu_fibonacci(f, n);
	}
	t2=clock();
	double time_span3 = (double) t2-t1;
	printf("time_span(iterative_fibonacci(%d) for %d times):%0.1f (ms)\n", n, m3, time_span3);
	
	
	
	int m4 = 5000;
	t1=clock();
	for (i=0; i< m1; i++) {
	  for (j=0; j<=n; j++) f[j]=-1; 	
	  dptd_fibonacci(f, n);
	}
	t2=clock();
	double time_span4 = (double) t2-t1;
	printf("time_span(iterative_fibonacci(%d) for %d times):%0.1f (ms)\n", n, m4, time_span4);
	

	
	printf("\n\n**Comparisons**\n");
	printf("time_span(recursive_fibonacci(%d))/time_span(iterative_fibonacci(%d)):%0.1f\n", n, n, (time_span2/time_span1)*(m1/m2));
	
	printf("time_span(dpbu_fibonacci(%d))/time_span(iterative_fibonacci(%d)):%0.1f\n", n, n, (time_span3/time_span1)*(m1/m3));
	
	printf("time_span(dptd_fibonacci(%d))/time_span(iterative_fibonacci(%d)):%0.1f\n", n, n, (time_span4/time_span1)*(m1/m4));
	

	printf("time_span(recursive_fibonacci(%d))/time_span(dptd_fibonacci(%d)):%0.1f\n", n, n, (time_span2/time_span4)*(m4/m2));	

	
	return 1;
}
