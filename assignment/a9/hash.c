/*
 * your program signature
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

extern int htsize;

int hash(char *word)
{
    unsigned int hash = 0, i;
    for (i = 0; word[i] != '\0'; i++)
    {
        hash = 31 * hash + word[i];
    }
    return hash % htsize;
}

HSNODE *new_hashnode(char *key, int value)
{
    // your implementation
    HSNODE *new_node = (HSNODE *)malloc(sizeof(HSNODE));
    strcpy(new_node->key, key);
    new_node->value = value;
    return new_node;
}

HASHTABLE *new_hashtable(int size)
{
    // your implementation
    HASHTABLE *ht = (HASHTABLE *)malloc(sizeof(HASHTABLE));
    ht->hna = (HSNODE **)malloc(sizeof(HSNODE **) * size);
    int i;
    for (i = 0; i < size; i++)
    {
        *(ht->hna + i) = NULL;
    }
    ht->size = size;
    ht->count = 0;
    return ht;
}

HSNODE *search(HASHTABLE *ht, char *key)
{
    // your implementation
    int i = hash(key);
    HSNODE *p = ht->hna[i];

    while (p)
    {
        if (strcmp(p->key, key) == 0)
        {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

int insert(HASHTABLE *ht, HSNODE *np)
{
    // your implementation
    int i = hash(np->key);
    if (ht->hna[i])
    {
        HSNODE *p = ht->hna[i];
        HSNODE *prev = NULL;
        while (p)
        {
            if (strcmp(p->key, np->key) == 0)
            {
                p->value = np->value;
                return 0;
            }
            prev = p;
            p = p->next;
        }
        prev->next = np;
        np->next = NULL;
    }
    else
    {
        ht->hna[i] = np;
        np->next = NULL;
    }
    ht->count += 1;
    return 1;
}

int delete(HASHTABLE *ht, char *key)
{
    // your implementation
    int i = hash(key);
    if (ht->hna[i])
    {
        HSNODE *prev = NULL;
        HSNODE *curr = ht->hna[i];
        while (curr)
        {
            if (strcmp(curr->key, key) == 0)
            {
                if (prev)
                {
                    prev->next = curr->next;
                }
                else
                {
                    ht->hna[i] = curr->next;
                }
                free(curr);
                ht->count -= 1;
                return 1;
            }
            prev = curr;
            curr = curr->next;
        }
    }
    return 0;
}

void clean_hash(HASHTABLE **htp)
{
    if (*htp == NULL)
        return;
    HASHTABLE *ht = *htp;
    HSNODE *sp = ht->hna[0], *p, *temp;
    int i;
    for (i = 0; i < ht->size; i++)
    {
        p = ht->hna[i];
        while (p)
        {
            temp = p;
            p = p->next;
            free(temp);
        }
        ht->hna[i] = NULL;
    }
    free(ht->hna);
    ht->hna = NULL;
    *htp = NULL;
}