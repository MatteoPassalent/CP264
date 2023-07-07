/*
 * your program signature
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"

TNODE *search(TNODE *root, char *name)
{

    while (root && (strcmp(root->data.name, name) != 0))
    {

        if (strcmp(name, root->data.name) < 0)
        {
            root = root->left;
        }
        else
        {
            root = root->right;
        }
    }
    return root;
}

void insert(TNODE **rootp, char *name, float score)
{

    TNODE *np = new_node(name, score);

    if (!*rootp)
    {
        *rootp = np;
    }
    else
    {
        TNODE *parent = NULL, *ptr = *rootp;

        while (ptr)
        {
            parent = ptr;
            if (strcmp(name, ptr->data.name) == 0)
            {
                break;
            }
            else if (strcmp(name, ptr->data.name) < 0)
            {
                ptr = ptr->left;
            }
            else
            {
                ptr = ptr->right;
            }
        }

        if (strcmp(name, parent->data.name) < 0)
        {
            parent->left = np;
        }
        else
        {
            parent->right = np;
        }
    }
}

void delete(TNODE **rootp, char *name)
{
    TNODE *ptr = *rootp, *parent = NULL;

    while (ptr && strcmp(name, ptr->data.name) != 0)
    {
        parent = ptr;
        ptr = (strcmp(name, ptr->data.name) < 0) ? ptr->left : ptr->right;
    }
    if (ptr)
    {
        if (!ptr->left && ptr->right)
        {
            if (!parent)
            {
                *rootp = ptr->right;
            }
            else if (parent->left == ptr)
            {
                parent->left = ptr->right;
                ptr->right = NULL;
            }
            else
            {
                parent->right = ptr->right;
                ptr->right = NULL;
            }
        }
        else if (ptr->left && !ptr->right)
        {
            if (!parent)
            {
                *rootp = ptr->left;
            }
            else if (parent->left == ptr)
            {
                parent->left = ptr->left;
                ptr->left = NULL;
            }
            else
            {
                parent->right = ptr->left;
                ptr->left = NULL;
            }
        }
        else
        {
            TNODE *smallest_node = extract_smallest_node(&ptr->right);

            if (!parent)
            {
                *rootp = smallest_node;
            }
            else if (parent->left == ptr)
            {
                parent->left = smallest_node;
            }
            else if (parent->right == ptr)
            {
                parent->right = smallest_node;
            }

            if (smallest_node)
            {
                smallest_node->left = ptr->left;
                smallest_node->right = ptr->right;
            }
        }
        free(ptr);
    }
}

TNODE *new_node(char *name, float score)
{
    TNODE *np = (TNODE *)malloc(sizeof(TNODE));
    if (np)
    {
        strcpy(np->data.name, name);
        np->data.score = score;
        np->left = NULL;
        np->right = NULL;
    }
    return np;
}

TNODE *extract_smallest_node(TNODE **rootp)
{
    TNODE *p = *rootp, *parent = NULL;
    if (p)
    {
        while (p->left)
        {
            parent = p;
            p = p->left;
        }

        if (parent == NULL)
            *rootp = p->right;
        else
            parent->left = p->right;

        p->left = NULL;
        p->right = NULL;
    }

    return p;
}

void clean_tree(TNODE **rootp)
{
    TNODE *root = *rootp;
    if (root)
    {
        if (root->left)
            clean_tree(&root->left);
        if (root->right)
            clean_tree(&root->right);
        free(root);
    }
    *rootp = NULL;
}
