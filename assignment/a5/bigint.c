/*
--------------------------------------------------
Project: cp264oc-a4q3
File:    bigint.c
Author:  Matteo Passalent
Version: 2023-06-13
--------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include "bigint.h"

BIGINT bigint(char *p)
{
    BIGINT bn = {0};
    if (p == NULL)
        return bn;
    else if (!(*p >= '0' && *p <= '9'))
    { // not begin with digits
        return bn;
    }
    else if (*p == '0' && *(p + 1) == '\0')
    { // just "0"
        dll_insert_end(&bn, new_node(*p - '0'));
        return bn;
    }
    else
    {
        while (*p)
        {
            if (*p >= '0' && *p <= '9')
            {
                dll_insert_end(&bn, new_node(*p - '0'));
            }
            else
            {
                dll_clean(&bn);
                break;
            }
            p++;
        }
        return bn;
    }
}

BIGINT add(BIGINT op1, BIGINT op2)
{
    BIGINT sum = bigint(NULL);
    NODE *p1 = op1.end;
    NODE *p2 = op2.end;
    int c = 0;
    int a;
    int b;
    int s;

    while (p1 || p2)
    {
        a = 0;
        b = 0;
        if (p1)
        {
            a = p1->data;
            p1 = p1->prev;
        }
        if (p2)
        {
            b = p2->data;
            p2 = p2->prev;
        }

        s = a + b + c;
        if (s >= 10)
        {
            s -= 10;
            c = 1;
        }
        else
        {
            c = 0;
        }
        NODE *new = new_node(s);

        dll_insert_start(&sum, new);
    }
    if (c == 1)
    {
        NODE *new = new_node(1);
        dll_insert_start(&sum, new);
    }
    return sum;
}

BIGINT Fibonacci(int n)
{
    BIGINT f2 = bigint("1");
    if (n <= 2)
    {
        return bigint("1");
    }
    else
    {
        BIGINT temp = bigint(NULL);
        BIGINT f1 = bigint("1");

        for (int i = 3; i <= n; i++)
        {
            temp = f2;
            f2 = add(f1, f2);
            f1 = temp;
        }
        dll_clean(&temp);
        dll_clean(&f1);
    }

    return f2;
}