/*
 * your program signature
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"

int heapify_up(HEAP *heap, int index);
int heapify_down(HEAP *heap, int index);

HEAP *new_heap(int capacity)
{
    // your implementation
    HEAP *new = (HEAP *)malloc(sizeof(HEAP));
    new->capacity = capacity;
    new->size = 0;
    new->hna = (HNODE *)malloc(sizeof(HNODE) * capacity);
    return new;
}

void insert(HEAP *heap, HNODE new_node)
{
    // your implementation
    if (heap->size == heap->capacity)
    {
        heap->capacity *= 2;
        void *temp = realloc(heap->hna, sizeof(HNODE) * heap->capacity);
        if (temp)
        {
            heap->hna = temp;
        }
        else
        {
            temp = malloc(sizeof(HNODE) * heap->capacity);
            if (temp)
            {
                memcpy(temp, heap->hna, sizeof(HNODE) * heap->size);
                free(heap->hna);
                heap->hna = temp;
            }
            else
            {
                printf("array resize failed\n");
                return;
            }
        }
    }
    heap->hna[heap->size] = new_node;
    heapify_up(heap, heap->size);
    heap->size += 1;
}

int heapify_up(HEAP *heap, int index)
{
    int pi;
    HNODE val = heap->hna[index];

    while (index > 0)
    {
        pi = (index - 1) / 2;
        if (cmp(heap->hna[pi].key, val.key) <= 0)
        {
            break;
        }
        else
        {
            heap->hna[index] = heap->hna[pi];
            index = pi;
        }
    }
    heap->hna[index] = val;
    return index;
}

int heapify_down(HEAP *heap, int index)
{
    HNODE val = heap->hna[index];
    int ci = index * 2 + 1;

    while (ci <= heap->size)
    {
        if ((ci < heap->size) && (heap->hna[ci].key > heap->hna[ci + 1].key))
        {
            ci++;
        }

        if (heap->hna[ci].key >= val.key)
        {
            break;
        }
        else
        {
            heap->hna[index] = heap->hna[ci];
            index = ci;
            ci = index * 2 + 1;
        }
    }
    heap->hna[index] = val;
    return index;
}

HNODE extract_min(HEAP *heap)
{
    // your implementation
    HNODE min = heap->hna[0];
    heap->hna[0] = heap->hna[heap->size - 1];
    heap->size--;
    heapify_down(heap, 0);

    if (heap->size <= heap->capacity * 0.25)
    {
        heap->capacity /= 2;
        void *temp = realloc(heap->hna, sizeof(HNODE) * heap->capacity);
        if (temp)
        {
            heap->hna = temp;
        }
        else
        {
            temp = malloc(sizeof(HNODE) * heap->capacity);
            if (temp)
            {
                memcpy(temp, heap->hna, sizeof(HNODE) * heap->size);
                free(heap->hna);
                heap->hna = temp;
            }
            else
            {
                printf("array resize failed\n");
            }
        }
    }
    return min;
}

int change_key(HEAP *heap, int index, KEYTYPE new_key)
{
    // your implementation
    int i = -1;
    if (heap->hna[index].key < new_key)
    {
        heap->hna[index].key = new_key;
        i = heapify_down(heap, index);
    }
    else if (heap->hna[index].key > new_key)
    {
        heap->hna[index].key = new_key;
        i = heapify_up(heap, index);
    }
    else
    {
        heap->hna[index].key = new_key;
    }
    return i;
}

int find_data_index(HEAP *heap, DATA data)
{
    // your implementation
    for (int i = 0; i < heap->size; i++)
    {
        if (heap->hna[i].data == data)
            return i;
    }
    return -1;
}

int cmp(KEYTYPE a, KEYTYPE b)
{
    // your implementation
    if (a < b)
        return -1;
    else if (a > b)
        return 1;
    else
        return 0;
}