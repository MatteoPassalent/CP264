/*
 * your program signature
 */

#include <stdio.h>
#include <stdlib.h>
#include "queue_stack.h"
#include "tree.h"

TNODE *new_node(int value)
{
    TNODE *np = (TNODE *)malloc(sizeof(TNODE));
    if (np != NULL)
    {
        np->data = value;
        np->left = NULL;
        np->right = NULL;
    }
    return np;
}

TPROPS get_props(TNODE *root)
{
    TPROPS r = {0};
    if (root)
    {
        TPROPS lp = get_props(root->left);
        TPROPS rp = get_props(root->right);
        r.height = lp.height > rp.height ? 1 + lp.height : 1 + rp.height;
        r.order = 1 + lp.order + rp.order;
    }
    return r;
}

void display_preorder(TNODE *root)
{
    if (root)
    {
        printf("%c ", root->data);
        display_preorder(root->left);
        display_preorder(root->right);
    }
}

void display_inorder(TNODE *root)
{
    if (root)
    {
        display_inorder(root->left);
        printf("%c ", root->data);
        display_inorder(root->right);
    }
}

void display_postorder(TNODE *root)
{
    if (root)
    {
        display_postorder(root->left);
        display_postorder(root->right);
        printf("%c ", root->data);
    }
}

/* use auxiliary queue data structure for the algorithm  */
void display_bforder(TNODE *root)
{
    if (!root)
    {
        return;
    }
    QUEUE queue = {0};
    TNODE *tn = NULL;
    enqueue(&queue, root);

    while (queue.front)
    {
        tn = dequeue(&queue);
        printf("%c ", tn->data);
        if (tn->left)
        {
            enqueue(&queue, tn->left);
        }
        if (tn->right)
        {
            enqueue(&queue, tn->right);
        }
    }
    clean_queue(&queue);
}

/* use auxiliary queue data structure for the algorithm  */
TNODE *iterative_bfs(TNODE *root, int val)
{
    if (!root)
    {
        return NULL;
    }
    QUEUE queue = {0};
    TNODE *tn = NULL, *r = NULL;
    enqueue(&queue, root);

    while (queue.front)
    {
        tn = dequeue(&queue);
        if (tn->data == val)
        {
            r = tn;
            break;
        }
        if (tn->left)
        {
            enqueue(&queue, tn->left);
        }
        if (tn->right)
        {
            enqueue(&queue, tn->right);
        }
    }
    clean_queue(&queue);
    return r;
}

TNODE *iterative_dfs(TNODE *root, int val)
{
    STACK stack = {0};
    TNODE *r = NULL, *p = NULL;
    if (root)
    {
        push(&stack, root);
        while (stack.top)
        {
            p = pop(&stack);
            if (p->data == val)
            {
                r = p;
                break;
            }
            if (p->left)
            {
                push(&stack, p->left);
            }
            if (p->right)
            {
                push(&stack, p->right);
            }
        }
        clean_stack(&stack);
    }
    return r;
}

// the following functions are given, need to add to your program.

void clean_tree(TNODE **rootp)
{
    TNODE *p = *rootp;
    if (p)
    {
        if (p->left)
            clean_tree(&p->left);
        if (p->right)
            clean_tree(&p->right);
        free(p);
    }
    *rootp = NULL;
}

void insert_complete(TNODE **rootp, int val)
{
    if (*rootp == NULL)
    {
        *rootp = new_node(val);
    }
    else
    {
        QUEUE queue = {0};
        TNODE *p;
        enqueue(&queue, *rootp);
        while (queue.front)
        {
            p = dequeue(&queue);
            if (p->left == NULL)
            {
                p->left = new_node(val);
                break;
            }
            else
            {
                enqueue(&queue, p->left);
            }

            if (p->right == NULL)
            {
                p->right = new_node(val);
                break;
            }
            else
            {
                enqueue(&queue, p->right);
            }
        }
    }
}