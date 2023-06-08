/*
--------------------------------------------------
Project: cp264oc-a3q2
File:    myword.c
Author:  Matteo Passalent
Version: 2023-06-01
--------------------------------------------------
*/

#include <stdio.h>
#include <string.h>
#include "mystring.h"
#include "myword.h"

void stopword_dictionay(char *filename, char *stopwords[])
{
    FILE *fp = fopen(filename, "r");
    char line[1000];
    char delimiters[] = " .,\n\t\r";
    char *token;
    int i;
    while (fgets(line, 1000, fp) != NULL)
    {
        token = (char *)strtok(line, delimiters);
        while (token != NULL)
        {
            i = (int)(*token - 'a');
            // *word_token represent the first character of the token word,
            strcat(stopwords[i], token);
            strcat(stopwords[i], ",");
            token = (char *)strtok(NULL, delimiters);
        }
    }
}

int is_stopword(char *stopwords[], char *word)
{
    if (word == NULL || *word == '\0')
        return 0;
    else
    {
        char temp[20] = {0}; // build the searching pattern like ,word,
        strcat(temp, ",");
        strcat(temp, word);
        strcat(temp, ",");
        if (strstr(stopwords[(int)(*word - 'a')], temp) != NULL)
            return 1;
        else
            return 0;
    }
}

int process_word(char *filename, WORDSUMMARY *words, char *stopwords[])
{
    FILE *fp = fopen(filename, "r");
    char delimiters[] = " .,\n\t\r";
    char *word_token;
    char line[1000];
    while (fgets(line, MAX_LINE_LEN, fp) != NULL)
    { // traversing all lines
        words->line_count++;
        str_lower(line);                               // your function in mystring.c
        str_trim(line);                                // your function in mytring.c
        word_token = (char *)strtok(line, delimiters); // get the first wordwhile (word_token != NULL) { // traversing all words in a line
        while (word_token != NULL)
        {
            if (is_stopword(stopwords, word_token) == 0)
            { // pattern: not a stop word // action: insert word_token into data structure words->word_array[]
                int existing_index = -1;
                for (int i = 0; i < words->word_count; i++)
                {
                    if (strcmp(words->word_array[i].word, word_token) == 0)
                    {
                        existing_index = i;
                        break;
                    }
                }
                if (existing_index != -1)
                {
                    words->word_array[existing_index].frequency++;
                }
                else
                {

                    int index = words->non_common_word_count;
                    strcpy(words->word_array[index].word, word_token);
                    words->word_array[index].frequency = 1;
                    words->non_common_word_count++;
                }
            }
            words->word_count++;
            word_token = (char *)strtok(NULL, delimiters); // next word
        }
    }
    fclose(fp);
    return 1;
}
