/*
--------------------------------------------------
Project: cp264oc-a2q2
File:    polynomial.h
Author:  Matteo Passalent
Version: 2023-05-24
--------------------------------------------------
*/
#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

float horner(float *p, int n, float x);
float bisection(float *p, int n, float a, float b);

#endif