/*
 * your program signature
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"

// help functions
TNODE *extract_smallest_node(TNODE **rootp);
int max(int a, int b);
void update_height(TNODE **node);

// this is a help function for balance factor.
int height(TNODE *np)
{
    // your implementation
    if (np)
    {
        return np->height;
    }
    else
    {
        return 0;
    }
}

int balance_factor(TNODE *np)
{
    if (np)
    {
        return height(np->left) - height(np->right);
    }
    else
    {
        return 0;
    }
}

int is_avl(TNODE *root)
{
    // your implementation
    if (!root)
    {
        return 1;
    }
    else if (balance_factor(root) > 1 || balance_factor(root) < -1)
    {
        return 0;
    }
    else
    {
        return is_avl(root->left) && is_avl(root->right);
    }
}

TNODE *rotate_right(TNODE *y)
{
    // your implementation
    TNODE *np = y->left;
    y->left = np->right;
    np->right = y;
    y->height = max(height(y->left), height(y->right)) + 1;
    np->height = max(height(np->left), height(np->right)) + 1;
    return np;
}

TNODE *rotate_left(TNODE *x)
{
    // your implementation
    TNODE *np = x->right;
    x->right = np->left;
    np->left = x;
    x->height = max(height(x->left), height(x->right)) + 1;
    np->height = max(height(np->left), height(np->right)) + 1;
    return np;
}

void insert(TNODE **rootp, char *name, float score)
{
    // 1. Perform the normal BST insertion
    if (*rootp == NULL)
    {
        // moved inside if statement to avoid uneccesary allocations
        TNODE *np = (TNODE *)malloc(sizeof(TNODE));
        if (np == NULL)
            return;
        strcpy(np->data.name, name);
        np->data.score = score;
        np->height = 1;
        np->left = NULL;
        np->right = NULL;
        *rootp = np;
        return;
    }

    TNODE *root = *rootp;
    if (strcmp(name, root->data.name) < 0)
        insert(&root->left, name, score);
    else if (strcmp(name, root->data.name) > 0)
        insert(&root->right, name, score);
    else
        return;
    // printf("root: %s\n", (*rootp)->data.name);
    (*rootp)->height = max(height((*rootp)->left), height((*rootp)->right)) + 1;
    if (balance_factor(*rootp) > 1)
    {
        if (balance_factor((*rootp)->left) >= 0)
        {

            *rootp = rotate_right(*rootp);
        }
        else
        {
            (*rootp)->left = rotate_left((*rootp)->left);
            *rootp = rotate_right(*rootp);
        }
    }
    else if (balance_factor(*rootp) < -1)
    {
        if (balance_factor((*rootp)->right) <= 0)
        {
            *rootp = rotate_left(*rootp);
        }
        else
        {
            (*rootp)->right = rotate_right((*rootp)->right);
            *rootp = rotate_left(*rootp);
        }
    }
    // 2. update height of this root node

    // 3. Get the balance factor of this ancestor node to check whether this node became unbalanced

    // 4. re-balance if not balanced
}

void delete(TNODE **rootp, char *name)
{
    TNODE *root = *rootp;
    TNODE *np;

    if (root == NULL)
        return;

    if (strcmp(name, root->data.name) == 0)
    {
        if (root->left == NULL && root->right == NULL)
        {
            free(root);
            *rootp = NULL;
        }
        else if (root->left != NULL && root->right == NULL)
        {
            np = root->left;
            free(root);
            *rootp = np;
        }
        else if (root->left == NULL && root->right != NULL)
        {
            np = root->right;
            free(root);
            *rootp = np;
        }
        else if (root->left != NULL && root->right != NULL)
        {
            np = extract_smallest_node(&root->right);
            np->left = root->left;
            np->right = root->right;
            free(root);
            *rootp = np;
        }
    }
    else
    {
        if (strcmp(name, root->data.name) < 0)
        {
            delete (&root->left, name);
        }
        else
        {
            delete (&root->right, name);
        }
    }

    // If the tree had only one node then return
    if (*rootp == NULL)
        return;

    root = *rootp;
    (*rootp)->height = max(height((*rootp)->left), height((*rootp)->right)) + 1;

    if (balance_factor(*rootp) > 1)
    {
        // need to fix, must use balance factor instead of comparing string name for insertion too??
        if (balance_factor((*rootp)->left) >= 0)
        {
            *rootp = rotate_right(*rootp);
        }
        else
        {
            (*rootp)->left = rotate_left((*rootp)->left);
            *rootp = rotate_right(*rootp);
        }
    }
    else if (balance_factor(*rootp) < -1)
    {
        if (balance_factor((*rootp)->right) <= 0)
        {
            *rootp = rotate_left(*rootp);
        }
        else
        {
            (*rootp)->right = rotate_right((*rootp)->right);
            *rootp = rotate_left(*rootp);
        }
    }

    // 2: update the this root node's height

    // 3: get the balance factor of this root node

    // 4: re-balance if not balanced
}

// You are allowed to use the following functions
int max(int a, int b)
{
    return (a > b) ? a : b;
}

TNODE *extract_smallest_node(TNODE **rootp)
{
    TNODE *tnp = *rootp;
    TNODE *parent = NULL;
    if (tnp == NULL)
    {
        return NULL;
    }
    else
    {
        while (tnp->left)
        {
            parent = tnp;
            tnp = tnp->left;
        }
        if (parent == NULL)
            *rootp = tnp->right;
        else
            parent->left = tnp->right;
        tnp->left = NULL;
        tnp->right = NULL;
        return tnp;
    }
}

// the following functions are from A7
TNODE *search(TNODE *root, char *name)
{
    TNODE *tp = root;
    while (tp)
    {
        if (strcmp(name, tp->data.name) == 0)
        {
            return tp;
        }
        else if (strcmp(name, tp->data.name) < 0)
            tp = tp->left;
        else
            tp = tp->right;
    }
    return NULL;
}

void clean_tree(TNODE **rootp)
{
    if (*rootp)
    {
        TNODE *np = *rootp;
        if (np->left)
            clean_tree(&np->left);
        if (np->right)
            clean_tree(&np->right);
        free(np);
    }
    *rootp = NULL;
    ;
}