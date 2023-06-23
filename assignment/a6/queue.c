#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "queue.h"

void enqueue(QUEUE *qp, NODE *np)
{
    if (qp->front == NULL)
    {
        qp->front = np;
        qp->rear = np;
    }
    else
    {
        qp->rear->next = np;
        qp->rear = np;
        qp->rear->next = NULL;
    }
    qp->length += 1;
}

NODE *dequeue(QUEUE *qp)
{
    NODE *temp = qp->front;
    qp->front = qp->front->next;
    temp->next = NULL;
    qp->length -= 1;

    if (qp->front == NULL)
    {
        qp->rear = NULL;
    }

    return temp;
}

void queue_clean(QUEUE *qp)
{
    clean(&qp->front);
    qp->length = 0;
}