/*
--------------------------------------------------
Project: cp264oc-a3q1
File:    mystring.c
Author:  Matteo Passalent
Version: 2023-06-01
--------------------------------------------------
*/

#include "mystring.h"

int str_len(char *s)
{
    if (!s)
    {
        return -1;
    }
    int counter = 0;
    char *p = s;
    while (*p)
    {
        counter++;
        p++;
    }
    return counter;
}

int str_wc(char *s)
{
    if (!s)
    {
        return -1;
    }
    int counter = 0;
    char *p = s;
    while (*p)
    {
        if (*p != ' ' && (*(p - 1) == ' ' || *(p - 1) == *s))
        {
            counter++;
        }
        p++;
    }
    return counter;
}

void str_lower(char *s)
{
    if (!s)
        return;
    char *p = s;
    while (*p)
    {
        if (*p >= 'A' && *p <= 'Z')
            *p += 32;
        p++;
    };
}

void str_trim(char *s)
{
    char *p = s, *dp = s;
    while (*p)
    {
        if (*p != ' ' || (p > s && *(p - 1) != ' '))
        {
            *dp = *p;
            dp++;
        }
        p++;
    }
    *dp = '\0'; // Add null character at the end
    if (dp > s && *(dp - 1) == ' ')
    {
        *(dp - 1) = '\0';
    }
    // final action to deal with case like “This is it “
}