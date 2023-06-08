/*
 * your program signature
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "mysort.h"
#include "myrecord.h"

#define MAX_LINE 100

GRADE grade(float score)
{
    GRADE r = {"F", 0};
    int p = (int)round(score);
    r.percentage = p;
    if (p >= 90)
        strcpy(r.letter_grade, "A+");

    // your implementation

    return r;
}

STATS process_data(RECORD *dataset, int n)
{
    // your implementation
}

int import_data(char *infilename, RECORD *dataset)
{
    // your implementation
}

int report_data(char *outfilename, RECORD dataset[], STATS stats)
{
    // your implementation
}