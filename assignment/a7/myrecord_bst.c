/*
 * your program signature
 */

#include <stdio.h>
#include <math.h>
#include "queue_stack.h"
#include "bst.h"
#include "myrecord_bst.h"

void add_data(TREE *tree, char *name, float score)
{
    insert(&tree->root, name, score);
    tree->count += 1;
    float old_mean = tree->mean;
    tree->mean = (tree->mean * (tree->count - 1) + score) / tree->count;
    tree->stddev = sqrt((((tree->count - 1) * (pow(tree->stddev, 2) + pow(old_mean, 2)) + pow(score, 2)) / tree->count) - pow(tree->mean, 2));
}

void remove_data(TREE *tree, char *name)
{
    TNODE *rn = search(tree->root, name);
    delete (&tree->root, name);
    tree->count -= 1;
    float old_mean = tree->mean;
    tree->mean = (tree->mean * (tree->count + 1) - rn->data.score) / tree->count;
    tree->stddev = sqrt((((tree->count + 1) * (pow(tree->stddev, 2) + pow(old_mean, 2))) - pow(rn->data.score, 2)) / tree->count - pow(tree->mean, 2));
}