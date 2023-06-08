/*
--------------------------------------------------
Project: cp264oc-a1q1
File:    caseflip.c
Author:  Matteo Passalent
Version:2023-05-16
--------------------------------------------------
*/

#include <stdio.h>

int main()
{

    char c = 0, temp;
    do
    {
        printf("Please enter a character\n");
        scanf("%c", &c);

        do
        {
            scanf("%c", &temp);
            if (temp == '\n')
                break;
        } while (1);

        if (c >= 'a' && c <= 'z')
        {
            printf("%c:%d,%c,%d\n", c, c, c - 32, c - 32);
        }
        else if (c >= 'A' && c <= 'Z')
        {
            printf("%c:%d,%c,%d\n", c, c, c + 32, c + 32);
        }
        else if (c >= '0' && c <= '9')
        {
            int digit = c - '0';
            printf("%c:%d,%d,%d\n", c, c, digit, digit * digit);
        }
        else if (c == '!')
        {
            printf("%c", c);
            printf(":quit\n");
            break;
        }
        else
        {
            printf("%c", c);
            printf(":invalid\n");
        }

    } while (1);

    return 0;
}
