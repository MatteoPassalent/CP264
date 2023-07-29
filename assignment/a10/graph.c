/*
 * your program signature
 */

#include <stdio.h>
#include <stdlib.h>
#include "queue_stack.h"
#include "graph.h"

GRAPH *new_graph(int order)
{
    // your implementation
    GRAPH *new = (GRAPH *)malloc(sizeof(GRAPH));
    new->order = order;
    new->size = 0;
    new->nodes = (GNODE **)malloc(sizeof(GNODE *) * order);

    for (int i = 0; i < order; i++)
    {
        GNODE *node = (GNODE *)malloc(sizeof(GNODE));
        node->neighbor = NULL;
        node->nid = i;
        new->nodes[i] = node;
    }
    return new;
}

void add_edge(GRAPH *g, int from, int to, int weight)
{
    // your implementation
    int i;
    for (i = 0; i < g->order; i++)
    {
        if (g->nodes[i]->nid == from)
        {
            break;
        }
    }

    // could do better
    int found = 0;
    ADJNODE *temp = g->nodes[i]->neighbor;
    if (temp)
    {
        while (temp->next)
        {
            if (temp->nid == to)
            {
                temp->weight = weight;
                found = 1;
                break;
            }
            temp = temp->next;
        }
        if (!found)
        {
            ADJNODE *new = (ADJNODE *)malloc(sizeof(ADJNODE));
            new->nid = to;
            new->weight = weight;
            new->next = NULL;
            temp->next = new;
        }
    }
    else
    {
        ADJNODE *new = (ADJNODE *)malloc(sizeof(ADJNODE));
        new->nid = to;
        new->weight = weight;
        new->next = NULL;
        g->nodes[i]->neighbor = new;
    }
    g->size += 1;
}

void display_bforder(GRAPH *g, int start)
{
    // your implementation
    if (g == NULL)
    {
        return;
    }
    int n = g->order;
    int visited[n];

    int i;
    for (i = 0; i < n; i++)
    {
        visited[i] = 0;
    }

    QUEUE *q = new_queue();
    GNODE *gnp = NULL;
    ADJNODE *anp = NULL;

    enqueue(q, g->nodes[start]);
    visited[start] = 1;

    while (q->front)
    {
        gnp = (GNODE *)dequeue(q);
        printf("%d ", gnp->nid);

        anp = gnp->neighbor;
        while (anp)
        {
            if (visited[anp->nid] == 0)
            {
                enqueue(q, g->nodes[anp->nid]);
                visited[anp->nid] = 1;
            }
            anp = anp->next;
        }
    }
    clean_queue(q);
}

void display_dforder(GRAPH *g, int start)
{
    // your implementation
    STACK *s = new_stack();
    int visited[g->order];

    for (int i = 0; i < g->order; i++)
    {
        visited[i] = 0;
    }

    push(s, g->nodes[start]);
    visited[start] = 1;

    while (s->top)
    {
        GNODE *node = pop(s);
        printf("%d ", node->nid);

        ADJNODE *temp = node->neighbor;

        while (temp)
        {
            if (visited[temp->nid] == 0)
            {
                push(s, g->nodes[temp->nid]);
                visited[temp->nid] = 1;
            }
            temp = temp->next;
        }
    }
}

int get_weight(GRAPH *g, int from, int to)
{
    ADJNODE *p = g->nodes[from]->neighbor;
    int result = INFINITY;
    while (p)
    {
        if (p->nid == to)
        {
            result = p->weight;
            break;
        }
        p = p->next;
    }
    return result;
}

void clean_graph(GRAPH **gp)
{
    int i;
    GRAPH *g = *gp;
    ADJNODE *temp, *ptr;
    for (i = 0; i < g->order; i++)
    {
        ptr = g->nodes[i]->neighbor;
        while (ptr != NULL)
        {
            temp = ptr;
            ptr = ptr->next;
            free(temp);
        }
        free(g->nodes[i]);
    }
    free(g->nodes);
    free(g);
    *gp = NULL;
}

void display_graph(GRAPH *g)
{
    if (g == NULL)
        return;
    printf("order:%d\n", g->order);
    printf("size:%d\n", g->size);
    printf("from:(to weight)");
    int i;
    ADJNODE *ptr;
    for (i = 0; i < g->order; i++)
    {
        printf("\n%d:", g->nodes[i]->nid);
        ptr = g->nodes[i]->neighbor;
        while (ptr != NULL)
        {
            printf("(%d %d) ", ptr->nid, ptr->weight);
            ptr = ptr->next;
        }
    }
}