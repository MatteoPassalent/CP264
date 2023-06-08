/*
--------------------------------------------------
Project: cp264oc-a1q3
File:    quadtratic.c
Author:  Matteo Passalent
Version:2023-05-16
--------------------------------------------------
*/

#include <stdio.h>
#include <math.h>

#define EPSILON 1e-6

int main(int argc, char *argv[])
{
    float a, b, c, d, x1, x2;

    if (argc < 2)
    {
        printf("argument input:missing\n");
    }
    else
    {

        int n = sscanf(argv[1], "%f,%f,%f", &a, &b, &c);
        if (n != 3)
        {
            printf("input:invalid\n");
        }
        else
        {
            printf("(%.2f)x^2+(%.2f)x+(%.2f)=0: ", a, b, c);
            if (fabs(a) < EPSILON)
            {
                printf("not a quadratic equation\n");
            }
            else
            {
                float disc = pow(b, 2) - 4 * a * c;
                if (disc >= 0)
                {
                    x1 = (-b + sqrt(disc)) / (2 * a);
                    x2 = (-b - sqrt(disc)) / (2 * a);
                    printf("%.2f, %.2f\n", x1, x2);
                }
                else
                {

                    float real = -b / (2 * a);
                    float imag = sqrt(-disc) / (2 * a);
                    printf("%.2f+%.2fi, %.2f-%.2fi\n", real, imag, real, imag);
                }
            }
        }
    }
    return 0;
}
