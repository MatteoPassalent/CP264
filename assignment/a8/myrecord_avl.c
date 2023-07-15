/*
 * your program signature
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "queue_stack.h"
#include "avl.h"
#include "myrecord_avl.h"

void merge_tree(TNODE **rootp1, TNODE **rootp2)
{
    // use recursive or iterative algorithm to traverse tree rootp2,
    // get record data of each node and insert into rootp1
    if (!*rootp2)
    {
        return;
    }
    else
    {
        merge_tree(rootp1, &(*rootp2)->left);
        merge_tree(rootp1, &(*rootp2)->right);

        char *name = strdup((*rootp2)->data.name);
        float score = (*rootp2)->data.score;
        insert(rootp1, name, score);
        return;
    }
}

void merge_data(TREE *t1, TREE *t2)
{
    // call the merge_tree function to merge t2->root into t1->root
    // update the simple stats of the merged data set using the stats of t1 and t2.
    merge_tree(&t1->root, &t2->root);
    int t1count = t1->count;
    int t2count = t2->count;
    float t1mean = t1->mean;
    float t2mean = t2->mean;
    float t1stddev = t1->stddev;
    float t2stddev = t2->stddev;

    t1->count += t2->count;
    t1->mean = ((t1->mean * t1count) + (t2->mean * t2count)) / (t1count + t2count);
    t2->stddev = sqrt((1 / (t1->count)) * (t1count * t1stddev * t1stddev + t1mean * t1mean * t1count + t2count * t2stddev * t2stddev + t2mean * t2mean * t2count) - t1->mean * t1->mean);
}

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
