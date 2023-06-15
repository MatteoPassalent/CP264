/*
--------------------------------------------------
Project: cp264oc-a4q1
File:    myrecord_sslist.c
Author:  Matteo Passalent
Version: 2023-06-13
--------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myrecord_sllist.h"

NODE *sll_search(SLL *sllp, char *name)
{
    NODE *r = NULL;
    NODE *np = sllp->start;
    while (np != NULL)
    {
        if (strcmp(np->data.name, name) == 0)
        { // if pattern matchr = np; // action
            r = np;
            break;
        }
        else
        {
            np = np->next;
        }
    }
    return r;
}

void sll_insert(SLL *sllp, char *name, float score)
{
    // your implementation
    // need to update the length
    NODE *np = (NODE *)malloc(sizeof(NODE));
    strcpy(np->data.name, name);
    np->data.score = score;
    np->next = NULL;

    NODE *prev = NULL;
    NODE *p = sllp->start;

    while (p != NULL)
    {
        if (strcmp(p->data.name, name) >= 0)
        {
            break;
        }
        else
        {
            prev = p;
            p = p->next;
        }
    }
    if (prev == NULL)
    {
        sllp->start = np;
        np->next = p;
    }
    else
    {

        prev->next = np;
        np->next = p;
    }
    sllp->length += 1;
}

int sll_delete(SLL *sllp, char *name)
{
    // your implementation
    // need to update the length
    NODE *ptr = sllp->start;
    NODE *prev = NULL;

    if (ptr == NULL)
    {
        return -1;
    }

    while (ptr->next != NULL && strcmp(ptr->data.name, name) != 0)
    {
        prev = ptr;
        ptr = ptr->next;
    }

    if (strcmp(ptr->data.name, name) != 0)
    {
        return -1;
    }
    else if (prev == NULL)
    {
        sllp->start = NULL;
        free(ptr);
        sllp->length -= 1;
    }
    else
    {
        prev->next = ptr->next;
        free(ptr);
        sllp->length -= 1;
    }

    return 1;
}

void sll_clean(SLL *sllp)
{
    // your implementation
    // need to reset the start and length
    NODE *ptr = NULL;
    NODE *current = sllp->start;

    while (current != NULL)
    {

        ptr = current;
        current = current->next;
        free(ptr);
    }

    sllp->start = NULL;
    sllp->length = 0;
}