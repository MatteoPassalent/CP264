/*
--------------------------------------------------
Project: cp264oc-a1q2
File:    overflow.c
Author:  Matteo Passalent
Version:2023-05-16
--------------------------------------------------
*/

#include <stdio.h>

int main(int argc, char *args[])
{

    int i, n = 0, sum = 1, b = 1, p = 1, is_overflow = 0;
    if (argc > 2)
    {
        int s1 = sscanf(args[1], "%d", &b);
        int s2 = sscanf(args[2], "%d", &n);

        if (b >= 1 && n >= 0 && s1 + s2 == 2)
        {

            for (i = 1; i <= n; i++)
            {
                if (p * b < p || sum + p * b < sum)
                {
                    is_overflow = 1;
                    printf("powersum(%d %d):overflow\n", b, n);
                    break;
                }
                else
                {
                    p = p * b;
                    sum = sum + p;
                }
            }
            if (is_overflow == 0)
            {
                printf("powersum(%d %d):%d\n", b, n, sum);
            }
        }
        else
        {
            printf("invalid argument\n");
        }
    }
    else
    {
        printf("arguments:b>0 n>0\n");
    }

    return 0;
}