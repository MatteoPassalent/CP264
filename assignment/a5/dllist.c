/*
--------------------------------------------------
Project: cp264oc-a4q2
File:    dllist.c
Author:  Matteo Passalent
Version: 2023-06-13
--------------------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
#include "dllist.h"

NODE *new_node(char data)
{
    NODE *node = (NODE *)malloc(sizeof(NODE));
    node->prev = NULL;
    node->next = NULL;
    node->data = data;

    return node;
}

void dll_insert_start(DLL *dllp, NODE *np)
{

    NODE *temp = dllp->start;
    dllp->start = np;
    np->next = temp;
    np->prev = NULL;
    dllp->length += 1;
    if (dllp->end == NULL)
    {
        dllp->end = np;
    }
    else
    {
        temp->prev = np;
    }
}

void dll_insert_end(DLL *dllp, NODE *np)
{
    NODE *temp = dllp->end;
    dllp->end = np;
    np->prev = temp;
    np->next = NULL;
    dllp->length += 1;
    if (dllp->start == NULL)
    {
        dllp->start = np;
    }
    else
    {
        temp->next = np;
    }
}

void dll_delete_start(DLL *dllp)
{
    NODE *temp = dllp->start;
    dllp->start = dllp->start->next;
    dllp->start->prev = NULL;
    free(temp);
    dllp->length -= 1;
}

void dll_delete_end(DLL *dllp)
{
    NODE *temp = dllp->end;
    dllp->end = dllp->end->prev;
    dllp->end->next = NULL;
    free(temp);
    dllp->length -= 1;
}

void dll_clean(DLL *dllp)
{
    NODE *curr = dllp->start;
    NODE *prev = NULL;

    while (curr != NULL)
    {

        prev = curr;
        curr = curr->next;
        free(prev);
    }

    dllp->start = NULL;
    dllp->end = NULL;
    dllp->length = 0;
}