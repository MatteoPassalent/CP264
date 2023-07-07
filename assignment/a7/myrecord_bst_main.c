/*
-------------------------------------------------------
Project:  cp264oc-a7q3
File:     myrecord_bst_main.c
About:    public test driver
Author:   HBF
Version:  2023-06-20
-------------------------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "queue_stack.h"
#include "bst.h"
#include "myrecord_bst.h"

typedef struct
{
  float count;
  float mean;
  float stddev;
  float median;
} STATS;

void search_info(char *sf, char *key, TNODE *tnp);
void display_inorder(TNODE *root);
void select_sort(float *a[], int left, int right);
int import_data(TREE *bst, char *filename);
STATS process_data(TREE *tree);

int main(int argc, char *args[])
{
  char infilename[40] = "marks.txt";
  if (argc > 1)
  {
    if (argc >= 2)
      strcpy(infilename, args[1]);
  }

  printf("\n---test import data ---\n");
  TREE dstree = {0};

  import_data(&dstree, infilename);
  display_inorder(dstree.root);

  printf("\n");
  printf("\ntree.count:%.1f\n", dstree.count);
  printf("tree.mean:%.1f\n", dstree.mean);
  printf("tree.stddev:%.1f\n", dstree.stddev);

  printf("\n---test record search---\n");
  char *key = "Smith";
  TNODE *tp = search(dstree.root, key);
  search_info("search", key, tp);

  printf("\n---test adding data---\n");
  key = "Moore";
  float score = 92;
  add_data(&dstree, "Moore", score);
  tp = search(dstree.root, key);
  search_info("search", key, tp);
  printf("tree1.count:%.1f\n", dstree.count);
  printf("tree1.mean:%.1f\n", dstree.mean);
  printf("tree1.stddev:%.1f\n", dstree.stddev);

  printf("\n---test removing data---\n");
  key = "Wang";
  remove_data(&dstree, key);
  tp = search(dstree.root, key);
  search_info("search", key, tp);
  printf("tree2.count:%.1f\n", dstree.count);
  printf("tree2.mean:%.1f\n", dstree.mean);
  printf("tree2.stddev:%.1f\n", dstree.stddev);

  printf("\n---test report data---\n");
  STATS stats = process_data(&dstree);
  printf("stats.count:%.1f\n", stats.count);
  printf("stats.mean:%.1f\n", stats.mean);
  printf("stats.stddev:%.1f\n", stats.stddev);
  printf("stats.median:%.1f\n", stats.median);

  clean_tree(&dstree.root);

  printf("\n");
  return 0;
}

void search_info(char *sf, char *key, TNODE *tnp)
{
  if (tnp)
    printf("%s(%s):%s %.0f\n", sf, key, tnp->data.name, tnp->data.score);
  else
    printf("%s(%s):NULL\n", sf, key);
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

int import_data(TREE *bst, char *filename)
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
      add_data(bst, name, score);
    }
  }
  fclose(fp);
  return (int)bst->count;
}

STATS process_data(TREE *tree)
{
  int n = (int)tree->count;
  float count = 0;
  float mean = 0;
  float stddev = 0;

  float *a[n]; // array store score values for sorting, fill a[] by bf traversing the bst

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
  select_sort(a, 0, count - 1);
  n = (int)count;
  stats.median = (n % 2 == 1) ? *a[n / 2] : (*a[n / 2 - 1] + *a[n / 2]) / 2;
  return stats;
}
