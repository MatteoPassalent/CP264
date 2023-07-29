/*
 * your program signature
 */

#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "algorithm.h"

EDGELIST *mst_prim(GRAPH *g, int start)
{
    // your implementation
    if (g == NULL)
        return NULL;

    int i, heapindex, u, n = g->order, T[n], parent[n];
    HNODE hn;
    HEAP *h = new_heap(4);
    EDGELIST *mst = new_edgelist();

    for (i = 0; i < n; i++)
    {
        T[i] = 0;
        parent[i] = -1;
    }

    T[start] = 1;
    ADJNODE *temp = g->nodes[start]->neighbor;
    while (temp)
    {
        hn.key = temp->weight;
        hn.data = temp->nid;
        insert(h, hn);
        parent[temp->nid] = start;
        temp = temp->next;
    }

    while (h->size > 0)
    {
        hn = extract_min(h);
        i = hn.data;
        T[i] = 1;
        add_edge_end(mst, parent[i], i, hn.key);

        temp = g->nodes[i]->neighbor;
        while (temp)
        {
            heapindex = find_data_index(h, temp->nid);
            if (heapindex >= 0)
            {
                if (T[temp->nid] == 0 && temp->weight < h->hna[heapindex].key)
                {
                    change_key(h, heapindex, temp->weight);
                    parent[temp->nid] = i;
                }
            }
            else
            {
                if (T[temp->nid] == 0)
                {
                    hn.key = temp->weight;
                    hn.data = temp->nid;
                    insert(h, hn);
                    parent[temp->nid] = i;
                }
            }
            temp = temp->next;
        }
    }
    return mst;
}

EDGELIST *spt_dijkstra(GRAPH *g, int start)
{
    // your implementation
    if (!g)
        return NULL;

    int i, heapindex, n = g->order, T[n], label[n], parent[n];
    EDGELIST *spt = new_edgelist();
    HEAP *h = new_heap(4);
    HNODE hn;

    for (i = 0; i < n; i++)
    {
        T[i] = 0;
        label[i] = 9999;
        parent[i] = -1;
    }

    ADJNODE *temp = g->nodes[start]->neighbor;
    label[start] = 0;
    T[start] = 1;

    while (temp)
    {
        hn.key = temp->weight + label[start];
        hn.data = temp->nid;
        insert(h, hn);
        parent[temp->nid] = start;
        temp = temp->next;
    }

    while (h->size > 0)
    {
        hn = extract_min(h);
        i = hn.data;
        T[i] = 1;
        label[i] = hn.key;
        add_edge_end(spt, parent[i], i, label[i] - label[parent[i]]);

        temp = g->nodes[i]->neighbor;
        while (temp)
        {
            heapindex = find_data_index(h, temp->nid);
            if (heapindex >= 0)
            {
                if (T[temp->nid] == 0 && temp->weight + label[i] < h->hna[heapindex].key)
                {
                    change_key(h, heapindex, temp->weight + label[i]);
                    parent[temp->nid] = i;
                }
            }
            else
            {
                if (T[temp->nid] == 0)
                {
                    hn.key = temp->weight + label[i];
                    hn.data = temp->nid;
                    insert(h, hn);
                    parent[temp->nid] = i;
                }
            }
            temp = temp->next;
        }
    }
    return spt;
}

EDGELIST *sp_dijkstra(GRAPH *g, int start, int end)
{
    // your implementation
}