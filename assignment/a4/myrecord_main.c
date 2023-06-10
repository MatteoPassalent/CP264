/*
--------------------------------------------------
Project: cp264oc-a4q2
File:    myrecord_main.c
About:   public test driver
Author:  HBF
Version: 2023-05-30
--------------------------------------------------
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "myrecord.h"

#define MAX_REC 100

int main(int argc, char *args[])
{
    char infilename[40] = "marks.txt";          // default input file name
    char outfilename[40] = "record_report.txt"; // default output file name
    char *stats_title = "Stats     value\n";
    char *stats_format = "%-10s%-6.1f\n";
    char *data_title = "\nname      score %%     grade\n";
    char *data_format = "%-10s%-6.1f%-6d%-6s\n";

    if (argc > 1)
    {
        if (argc >= 2)
            strcpy(infilename, args[1]);
        if (argc >= 3)
            strcpy(outfilename, args[2]);
    }
    RECORD dataset[MAX_REC]; // declare array of RECORD to store record data
    int record_count = import_data(infilename, dataset);
    if (record_count > 0)
    {
        STATS stats = process_data(dataset, record_count);
        printf(stats_title);
        printf(stats_format, "count", stats.count);
        printf(stats_format, "mean", stats.mean);
        printf(stats_format, "stddev", stats.stddev);
        printf(stats_format, "median", stats.median);

        printf(data_title);
        int i;
        for (i = 0; i < record_count; i++)
        {
            printf(data_format, dataset[i].name, dataset[i].score, grade(dataset[i].score).percentage, grade(dataset[i].score).letter_grade);
        }
        report_data(outfilename, dataset, stats);
    }
    else
        printf("no record");

    return 0;
}
