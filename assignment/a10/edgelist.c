/*
 * your program signature
 */

#include <stdio.h>
#include <stdlib.h>
#include "edgelist.h"

EDGELIST *new_edgelist()
{
    // your implementation
    EDGELIST *newEdgeList = (EDGELIST *)malloc(sizeof(EDGELIST));
    newEdgeList->size = 0;
    newEdgeList->start = NULL;
    newEdgeList->end = NULL;

    return newEdgeList;
}

void add_edge_end(EDGELIST *g, int from, int to, int weight)
{
    // your implementation
    EDGE *endEdge = (EDGE *)malloc(sizeof(EDGE));
    endEdge->to = to;
    endEdge->from = from;
    endEdge->weight = weight;

    if (g->end)
    {
        g->end->next = endEdge;
    }
    else
    {
        g->start = endEdge;
    }
    g->end = endEdge;
    endEdge->next = NULL;
    g->size += 1;
}

void add_edge_start(EDGELIST *g, int from, int to, int weight)
{
    // your implementation
    EDGE *startEdge = (EDGE *)malloc(sizeof(EDGE));
    startEdge->to = to;
    startEdge->from = from;
    startEdge->weight = weight;

    if (g->start)
    {
        startEdge->next = g->start;
    }
    else
    {
        g->end = startEdge;
        startEdge->next = NULL;
    }

    g->start = startEdge;
    g->size += 1;
}

int weight_edgelist(EDGELIST *g)
{
    // your implementation
    EDGE *temp = g->start;
    int weight = 0;
    while (temp)
    {
        weight += temp->weight;
        temp = temp->next;
    }
    return weight;
}

void clean_edgelist(EDGELIST **gp)
{
    EDGELIST *g = *gp;
    EDGE *temp, *p = g->start;
    while (p)
    {
        temp = p;
        p = p->next;
        free(temp);
    }
    free(g);
    *gp = NULL;
}

void display_edgelist(EDGELIST *g)
{
    if (g == NULL)
        return;
    printf("size:%d\n", g->size);
    printf("(from to weight):");
    EDGE *p = g->start;
    while (p)
    {
        printf("(%d %d %d) ", p->from, p->to, p->weight);
        p = p->next;
    }
}