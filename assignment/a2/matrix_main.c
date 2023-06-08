/*
--------------------------------------------------
Project: CP264-a2q3
File:    matrix_main.c  public test driver
Author:  HBF
Version: 2023-05-14
Compile: gcc matrix.c matrix_main.c
--------------------------------------------------
*/

#include<stdio.h>
#include "matrix.h"

void display_vector(float *v, int n) {
	int i;
	for (i = 0; i < n; i++) {
       printf("%6.1f", v[i]); 
	}
	printf("\n");
}

void display_matrix(float *m, int n) {
	float *p = m;
    int	i, j;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) printf("%6.1f", *(p+i*n+j));
		printf("\n");
	}
}

int main() {
  int n = 3; 
  float v1[] = {1, 1, 1};
  printf("\nv1:");
  display_vector(v1, n);
  printf("\nsum(v1):%.1f\n", sum(v1, n));
  printf("\nnorm(v1):%.1f\n", norm(v1, n));
  printf("\ndot_product(v1 v1):%.1f\n", dot_product(v1, v1, n));
  
  float v2[] = {1, 2, 3};
  printf("\nv2:");
  display_vector(v2, n);
  printf("\nsum(v2):%.1f\n", sum(v2, n));
  printf("\nnorm(v2):%.1f\n", norm(v2, n));
  printf("\ndoc_product(v2 v2):%.1f\n", dot_product(v2, v2, n)); 
  printf("\ndoc_product(v1 v2):%.1f\n", dot_product(v1, v2, n));

  
  float m1[n][n];
  float m2[n][n];
  float m3[n][n];
  float v[9] = { 8, 1, 6, 3, 5, 7, 4, 9, 2 };
  float *p = &v[0];
  float *p1 = &m1[0][0];
  int i;
  for (i = 0; i < 9; i++) *p1++ = *p++;
  
  printf("\nm1:\n");
  display_matrix(&m1[0][0], n);
  printf("sum(m1[0]):%.1f\n", sum(m1[0], n));
    
  transpose_matrix(&m1[0][0], &m2[0][0], n);
  printf("\nm2=m1':\n");  
  display_matrix(&m2[0][0], n);
  printf("sum(m2[0]):%.1f\n", sum(m2[0], n));
  
  multiply_matrix(&m1[0][0], &m2[0][0], &m3[0][0], n);  
  printf("\nm3=m1*m2':\n");
  display_matrix(&m3[0][0], n);
  
  matrix_multiply_vector(&m1[0][0], v1, v2, n);  
  printf("\nv2=m1*v1':");
  display_vector(v2, n);  
  
  return 0;
}
