#include <stdio.h>
#include "stack.h"

void push(STACK *sp, NODE *np)
{
    np->next = sp->top;
    sp->top = np;
    sp->height += 1;
}

NODE *pop(STACK *sp)
{
    NODE *temp = sp->top;
    sp->top = sp->top->next;
    temp->next = NULL;
    sp->height -= 1;

    return temp;
}

void stack_clean(STACK *sp)
{
    clean(&sp->top);
    sp->height = 0;
}