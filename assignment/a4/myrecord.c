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
    char g[14][5] = {"A+", "A", "A-", "B+", "B", "B-", "C+", "C", "C-", "D+", "D", "D-", "F"};
    int b[] = {100, 90, 85, 80, 77, 73, 70, 67, 63, 60, 57, 53, 50, 0};
    int left = 0, right = sizeof(b) / sizeof(float) - 1;
    int mid;
    while (right - left > 1)
    {
        mid = left + (right - left) / 2;
        if (p >= b[mid] && p < b[mid - 1])
        {
            strcpy(r.letter_grade, g[mid - 1]);
            break;
        }
        else if (p < b[mid])
        {
            left = mid;
        }
        else if (p > b[mid])
        {
            right = mid;
        }
    }
    return r;
}

STATS process_data(RECORD *dataset, int n)
{

    STATS stats = {0};
    // compute mean
    stats.mean = 0;
    for (int i = 0; i < n; i++)
    {
        stats.mean += dataset[i].score;
    }
    stats.mean /= n;
    // compute stddev
    stats.stddev = 0;
    for (int i = 0; i < n; i++)
    {
        stats.stddev += (dataset[i].score - stats.mean) * (dataset[i].score - stats.mean);
    }
    stats.stddev = sqrt(stats.stddev / n);
    // compute median: create float *a[n], fill with addresses &dataset[i].score, call a sort function of Q1, get the median
    float *a[n];
    for (int i = 0; i < n; i++)
    {
        a[i] = &dataset[i].score;
    }
    select_sort(a, 0, n - 1);
    if (n % 2 != 0)
    {
        stats.median = *a[n / 2 + 1];
    }
    else
    {
        stats.median = (*a[n / 2 - 1] + *a[n / 2]) / 2;
    }

    stats.count = n;

    return stats;
}

int import_data(char *infilename, RECORD *dataset)
{
    char delimiters[] = ",\n\r";
    char line[MAX_LINE];
    int i = 0; // record counter
    FILE *fp = fopen(infilename, "r");
    char *token = NULL;
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        token = (char *)strtok(line, delimiters);
        strcpy(dataset[i].name, token);
        token = (char *)strtok(NULL, delimiters);
        sscanf(token, "%f", &dataset[i].score);
        i++;
    }
    fclose(fp);
    return i;
}

int report_data(char *outfilename, RECORD dataset[], STATS stats)
{
    int n = stats.count;
    FILE *fp = fopen(outfilename, "w");
    char *file_format = "%s,%s\n";
    int i = 0;
    for (i = 0; i < n; i++)
    {
        for (i = 0; i < stats.count; i++)
        {
            fprintf(fp, file_format, dataset[i].name, grade(dataset[i].score).letter_grade);
        }
    }
    fclose(fp);
    return 1;
}
