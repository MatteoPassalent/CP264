/*
-------------------------------------------------------
Project:  cp264oc-a8q2
File:     myrecord_avl_main.c
About:    public test driver
Author:   HBF
Version:  2023-06-21
-------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "queue_stack.h"
#include "avl.h"
#include "myrecord_avl.h"

typedef struct
{
  float count;
  float mean;
  float stddev;
  float median;
} STATS;

int import_data(TREE *tree, char *filename);
STATS process_data(TREE *tree);
void display_inorder(TNODE *root);

int main(int argc, char *args[])
{
  char infilename1[40] = "marks1.txt";
  char infilename2[40] = "marks2.txt";
  if (argc > 1)
  {
    if (argc >= 2)
      strcpy(infilename1, args[1]);
    if (argc >= 3)
      strcpy(infilename2, args[2]);
  }

  printf("\nimport data from %s:\n", infilename1);
  TREE t1 = {0};
  import_data(&t1, infilename1);
  display_inorder(t1.root);
  printf("t1.count:%.1f\n", t1.count);
  printf("t1.mean:%.1f\n", t1.mean);
  printf("t1.stddev:%.1f\n", t1.stddev);

  printf("\ninport data from %s:\n", infilename2);
  TREE t2 = {0};
  import_data(&t2, infilename2);
  display_inorder(t2.root);
  printf("t2.count:%.1f\n", t2.count);
  printf("t2.mean:%.1f\n", t2.mean);
  printf("t2.stddev:%.1f\n", t2.stddev);

  printf("\ntest merge data\n");
  merge_data(&t1, &t2);
  clean_tree(&t2.root);
  display_inorder(t1.root);
  printf("merge.count:%.1f\n", t1.count);
  printf("merge.mean:%.1f\n", t1.mean);
  printf("merge.stddev:%.1f\n", t1.stddev);

  printf("\ntest process data\n");
  STATS stats = process_data(&t1);
  printf("stats.count:%.1f\n", stats.count);
  printf("stats.mean:%.1f\n", stats.mean);
  printf("stats.stddev:%.1f\n", stats.stddev);
  printf("stats.median:%.1f\n", stats.median);

  clean_tree(&t1.root);
  printf("\n");
  return 0;
}

void display_inorder(TNODE *root)
{
  if (root)
  {
    if (root->left)
      display_inorder(root->left);
    printf("%s,%3.1f\n", root->data.name, root->data.score);
    if (root->right)
      display_inorder(root->right);
  }
}

void select_sort(float *a[], int left, int right)
{
  int i, j, k;
  float *temp;
  for (i = left; i <= right; ++i)
  {
    k = i;
    for (j = i + 1; j <= right; ++j)
    {
      if (*a[j] < *a[k])
      {
        k = j;
      }
    }
    if (i != k)
    {
      temp = a[k];
      a[k] = a[i];
      a[i] = temp;
    }
  }
}

int import_data(TREE *tree, char *filename)
{
  char line[40], name[20];
  FILE *fp = fopen(filename, "r");
  char *result = NULL;
  float score = 0;
  char delimiters[] = ",\n";
  if (fp == NULL)
  {
    perror("Error while opening the file.\n");
    return -1;
  }
  while (fgets(line, sizeof(line), fp) != NULL)
  {
    result = strtok(line, delimiters);
    if (result)
    {
      strcpy(name, result);
      result = strtok(NULL, delimiters);
      score = atof(result);
      add_data(tree, name, score);
    }
  }
  fclose(fp);
  return (int)tree->count;
}

STATS process_data(TREE *tree)
{
  int n = (int)tree->count;
  float count = 0;
  float mean = 0;
  float stddev = 0;
  float *a[n];
  TNODE *p = tree->root;
  QUEUE queue = {0};
  enqueue(&queue, p);
  int i = 0;
  while (queue.front)
  {
    p = dequeue(&queue);
    a[i++] = &p->data.score;
    count += 1;
    mean += p->data.score;
    stddev += p->data.score * p->data.score;
    if (p->left)
      enqueue(&queue, p->left);
    if (p->right)
      enqueue(&queue, p->right);
  }

  // compute mean and stddev
  mean /= count;
  stddev = sqrt(stddev / count - mean * mean);
  STATS stats = {};
  stats.count = count;
  stats.mean = mean;
  stats.stddev = stddev;
  // compute median
  n = (int)count;
  select_sort(a, 0, n - 1);
  stats.median = (n % 2 == 1) ? *a[n / 2] : (*a[n / 2 - 1] + *a[n / 2]) / 2;
  return stats;
}
