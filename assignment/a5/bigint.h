/*
--------------------------------------------------
Project: cp264oc-a4q3
File:    bigint.H
Author:  Matteo Passalent
Version: 2023-06-13
--------------------------------------------------
*/

#ifndef BIGINT_H
#define BIGINT_H
#include "dllist.h"

typedef DLL BIGINT;
BIGINT bigint(char *digitstr);
BIGINT add(BIGINT oprand1, BIGINT oprand2);
BIGINT Fibonacci(int n);

#endif
